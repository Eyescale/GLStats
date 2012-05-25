
/* Copyright (c) 2012, Stefan Eilemann <eile@eyescale.ch> 
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 2.1 as published
 * by the Free Software Foundation.
 *  
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "renderer.h"

#include "data.h"
#include "entity.h"
#include "item.h"
#include "thread.h"
#include "type.h"

#include <lunchbox/debug.h>
#include <lunchbox/os.h>
#include <lunchbox/stdExt.h>

#include <map>
#include <set>
#ifdef __APPLE__
#  include <OpenGL/gl.h>
#else
#  include <GL/gl.h>
#endif

namespace GLStats
{
static const uint32_t nFrames = 4;
static const uint32_t space = 2; // pixel
static const uint32_t gap = space<<1; // pixel
static const uint32_t barHeight = 10; // pixel
static const uint32_t rowHeight = barHeight + space;
static const float legendWidth = 60.f; // pixel

typedef std::set< uint32_t > ThreadSet;
typedef ThreadSet::const_iterator ThreadSetCIter;
typedef std::map< uint32_t, ThreadSet > EntityMap;
typedef EntityMap::const_iterator EntityMapCIter;
typedef stde::hash_map< uint32_t, uint32_t > EntityPos;

typedef std::set< uint32_t > LayerSet;
typedef LayerSet::const_iterator LayerSetCIter;
typedef Items::const_iterator ItemsCIter;

namespace detail
{
static bool _compare( const Type& t1, const Type& t2 )
{
    if( t1.group != t2.group )
        return t1.group<t2.group;
    if( t1.subgroup != t2.subgroup )
        return t1.subgroup<t2.subgroup;
    return t1.name<t2.name;
}

class Renderer
{
public:
    Renderer() : api( 0 ), width( 0 ), height( 0 ) {}

    void draw( const ::GLStats::Data& data )
    {
        const Items& items = data.getItems();
        if( width == 0 || height == 0 || items.empty( ))
            return;

        // Scale factor
        const uint128_t x = data.computeMinMax( nFrames );
        const uint64_t totalTime = x.high() - x.low();
        float scale = 1.f;

        while( totalTime / scale < width )
            scale *= .5f;
        while( totalTime / scale > width )
            scale *= 2.f;
        const uint64_t xOffset = x.low() - width * scale + totalTime;

        // y positions
        EntityMap entities;
        const uint32_t endFrame = items.back().frame;
        const uint32_t startFrame = endFrame > nFrames ? endFrame - nFrames : 0;

        for( ItemsCIter i = items.begin(); i != items.end(); ++i )
        {
            const Item& item = *i;
            if( item.frame < startFrame )
                break;

            ThreadSet& threads = entities[ item.entity ];
            threads.insert( item.thread );
        }

        uint32_t nextY = height - gap; // start at top
        EntityPos yPos;
        for( EntityMapCIter i = entities.begin(); i != entities.end(); ++i )
        {
            const ThreadSet& threads = i->second;
            yPos[ i->first ] = nextY;
            nextY -= threads.size() * rowHeight;
        }

        //----- alternating frame background, entity names
        const Item* last = &items.front();
        typedef std::pair< uint32_t, uint64_t > FrameTime;
        typedef std::vector< FrameTime > FrameTimes;
        typedef stde::hash_map< uint64_t, FrameTimes > FrameTimesMap;
        typedef stde::hash_map< uint32_t, uint64_t > FrameEndMap;
        typedef FrameTimes::const_iterator FrameTimesCIter;
        typedef FrameTimesMap::const_iterator FrameTimesMapCIter;
        typedef FrameEndMap::const_iterator FrameEndMapCIter;

        FrameTimesMap frameTimes;
        FrameEndMap endTimes;
        uint64_t startTime = last->start;
        uint64_t endTime = 0;

        for( ItemsCIter i = items.begin(); i != items.end(); ++i )
        {
            const Item& item = *i;
            if( item.frame < startFrame )
                continue;

            if( item.entity != last->entity || item.thread != last->thread ||
                item.frame != last->frame )
            {
                const uint64_t row = ( uint64_t( last->entity ) << 32 ) +
                                     last->thread;
                FrameTimes& times = frameTimes[ row ];
                times.push_back( std::make_pair( last->frame, startTime ));

                FrameEndMapCIter j = endTimes.find( last->frame );
                if( j == endTimes.end( ))
                    endTimes[ last->frame ] = endTime;
                else
                    endTimes[ last->frame ] = LB_MAX( endTimes[ last->frame ],
                                                      endTime );

                startTime = item.start;
                endTime = item.end;
            }
 
            startTime = LB_MIN( item.start, startTime );
            endTime = LB_MAX( item.end, endTime );
            last = &item;
        }

        for( FrameTimesMapCIter i = frameTimes.begin();
             i != frameTimes.end(); ++i )
        {
            const uint64_t row = i->first;
            const uint32_t entity = row >> 32;
            const uint32_t thread = row & 0xFFFFFFFFu;
            const FrameTimes& times = i->second;
            const ThreadSet& threads = entities[ entity ];
            const ThreadSetCIter threadPos = threads.find( thread );
            const uint32_t y = yPos[ entity ] -
                std::distance( threads.begin(), threadPos ) * rowHeight;
            const float y1 = float( y + space );
            const float y2 = float( y - barHeight -space );

            for( FrameTimesCIter j = times.begin(); j != times.end(); )
            {
                const uint32_t frame = j->first;
                const uint64_t start = j->second;

                ++j;
                uint64_t end = (j == times.end( )) ? x.high() : j->second;
                if( end > endTimes[ frame ] )
                    end = endTimes[ frame ];

                const float x1 = float(start - xOffset) / scale - gap;
                const float x2 = float(end - xOffset) / scale - gap;
     
                if( (endFrame - frame) & 0x1 )
                    glColor4f( .4f, .4f, .4f, .6f );
                else
                    glColor4f( .6f, .6f, .6f, .6f );
                glBegin( GL_QUADS ); {
                    glVertex3f( x2, y1, 0.f );
                    glVertex3f( x1, y1, 0.f );
                    glVertex3f( x1, y2, 0.f);
                    glVertex3f( x2, y2, 0.f );
                } glEnd();
            }

            if( thread == 0 )
            {
                const Entity& entityData = data.getEntity( entity );
                glColor3f( 1.f, 1.f, 1.f );
                glRasterPos3f( space, y2, 0.f );
                api->drawText( entityData.name );
            }
            else
            {
                const Thread& threadData = data.getThread( thread );
                glColor3f( 1.f, 1.f, 1.f );
                glRasterPos3f( space + barHeight, y2, 0.f );
                api->drawText( threadData.name );
            }
        }

        //----- statistic items
        uint32_t inset = 0;

        last = &items.front();
        for( ItemsCIter i = items.begin(); i != items.end(); ++i )
        {
            const Item& item = *i;
            if( item.frame < startFrame )
                continue;

            if( item.frame != last->frame || item.entity != last->entity )
                inset = 0;
            else if( item.layer != last->layer )
                inset += space;

            const Type& type = data.getType( item.type );
            const ThreadSet& threads = entities[ item.entity ];
            const ThreadSetCIter j = threads.find( item.thread );
            const uint32_t y = yPos[ item.entity ] - 
                std::distance( threads.begin(), j ) * rowHeight;

            const float x1 = float( item.start - xOffset ) / scale - gap;
            const float x2 = float( item.end   - xOffset ) / scale - gap;
            const float y1 = float( y - inset );
            const float y2 = float( y - barHeight + inset );
            LBASSERTINFO( y2 < y1, y2 << " >= " << y1 );

            glColor4fv( type.color );
            glBegin( GL_QUADS ); {
                glVertex3f( x2, y1, 0.f );
                glVertex3f( x1, y1, 0.f );
                glVertex3f( x1, y2, 0.f);
                glVertex3f( x2, y2, 0.f );
            } glEnd();

            if( !item.text.empty( ))
            {
                glColor4f( 1.f, 1.f, 1.f, 1.f );
                glRasterPos3f( x1+1, y2, 0.f );
                api->drawText( item.text );
            }
        }

        glLogicOp( GL_XOR );
        glEnable( GL_COLOR_LOGIC_OP );

        glColor4f( 1.f, 1.f, 1.f, 1.f );

        const Strings& text = data.getText();
        for( StringsCIter i = text.begin(); i != text.end(); ++i )
        {
            nextY -= rowHeight;
            glRasterPos3f( space, static_cast< float >( nextY ), 0.f );
            api->drawText( *i );
        }

        std::stringstream stream;
        if( scale >= 1.f )
            stream << uint32_t( scale ) << " ms := 1 pixel";
        else
            stream << "1 ms := " << uint32_t( 1.f / scale ) << " pixel";

        nextY -= rowHeight + space;
        glRasterPos3f( space, static_cast< float >( nextY ), 0.f );
        api->drawText( stream.str( ));

        _drawLegend( data, nextY );
    }

    GLStats::Renderer* api;
    uint32_t width;
    uint32_t height;

private:
    void _drawLegend( const ::GLStats::Data& data, const uint32_t y )
    {
        uint32_t nextY = y + barHeight - space;
        float x1 = float( space );
        const TypeMap& typeMap = data.getTypes();

        Types types;
        for( TypeMapCIter i = typeMap.begin(); i != typeMap.end(); ++i )
            types.push_back( i->second );
        std::sort( types.begin(), types.end(), _compare );

        const Type* last = &types.back();
        for( TypesCIter i = types.begin(); i != types.end(); ++i )
        {
            const Type& type = *i;
            if( type.group != last->group )
            {
                x1 = float( space );
                nextY -= rowHeight;
                glColor3f( 1.f, 1.f, 1.f );
                glRasterPos3f( x1, nextY - barHeight, 0.f );
                glEnable( GL_COLOR_LOGIC_OP );
                api->drawText( type.group );
                glDisable( GL_COLOR_LOGIC_OP );
            }
            else if( type.subgroup != last->subgroup )
            {
                x1 = float( space );
                nextY -= rowHeight;
                glColor3f( 1.f, 1.f, 1.f );
                glRasterPos3f( x1 + rowHeight, nextY - barHeight, 0.f );
                glEnable( GL_COLOR_LOGIC_OP );
                api->drawText( type.subgroup );
                glDisable( GL_COLOR_LOGIC_OP );
            }
            last = &type;

            x1 += legendWidth;
            const float x2 = x1 + legendWidth - space; 
            const float y1 = float( nextY );
            const float y2 = float( nextY - barHeight );

            glColor3fv( type.color );
            glBegin( GL_QUADS ); {
                glVertex3f( x2, y1, 0.f );
                glVertex3f( x1, y1, 0.f );
                glVertex3f( x1, y2, 0.f );
                glVertex3f( x2, y2, 0.f );
            } glEnd();

            glColor3f( 0.f, 0.f, 0.f );
            glRasterPos3f( x1+space, nextY-barHeight, 0.f );
            api->drawText( type.name );
        }
    }

};
}

Renderer::Renderer()
        : impl_( new detail::Renderer )
{
    impl_->api = this;
}

Renderer::~Renderer()
{
    delete impl_;
}

void Renderer::setViewport( const uint32_t width, const uint32_t height )
{
    impl_->width = width;
    impl_->height = height;
}

void Renderer::obsolete( Data& data )
{
}

void Renderer::draw( const Data& data )
{
    impl_->draw( data );
}

}
