
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

#include <lunchbox/debug.h>
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
static const uint32_t nFrames = 3;
static const uint32_t space = 2; // pixel
static const uint32_t barHeight = 12; // pixel

typedef std::set< uint32_t > ThreadSet;
typedef ThreadSet::const_iterator ThreadSetCIter;
typedef std::map< uint32_t, ThreadSet > EntityMap;
typedef EntityMap::const_iterator EntityMapCIter;
typedef stde::hash_map< uint32_t, uint32_t > EntityPos;

typedef std::set< uint32_t > LayerSet;
typedef LayerSet::const_iterator LayerSetCIter;

namespace detail
{
class Renderer
{
public:
    Renderer() : width( 0 ), height( 0 ) {}

    void draw( ::GLStats::Data& data )
    {
        const Items& items = data.getItems();
        if( width == 0 || height == 0 || items.empty( ))
            return;

        // Scale factor
        uint128_t x = data.computeMinMax( nFrames );
        const uint64_t time = x.high() - x.low();
        uint32_t scale = 1;

        while( time / scale > width )
            scale = scale << 1;

        x.high() /= scale;
        x.low() = x.high() - width + space;

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

        uint32_t nextY = height - space; // start at top
        EntityPos yPos;
        for( EntityMapCIter i = entities.begin(); i != entities.end(); ++i )
        {
            const ThreadSet& threads = i->second;
            yPos[ i->first ] = nextY;
            nextY -= threads.size() * (barHeight + space);
        }

        //----- statistics
        float dim = 0.0f;
        uint32_t inset = 0;

        const Item* last = &items.front();
        uint128_t frameTime( x.high(), 0 );
        for( ItemsCIter i = items.begin(); i != items.end(); ++i )
        {
            const Item& item = *i;
            if( item.frame != last->frame )
            {
                frameTime.low() -= x.low();
                frameTime.high() -= x.low();

                const float x1 = static_cast< float >( frameTime.low( ));
                const float x2 = static_cast< float >( frameTime.high( ));
                const float y1 = static_cast< float >( nextY );
                const float y2 = static_cast< float >( height );

                glBegin( GL_LINES ); {
                    glColor3f( .5f-dim, 1.0f-dim, .5f-dim );
                    glVertex3f( x1, y1, 0.3f );
                    glVertex3f( x1, y2, 0.3f );

                    glColor3f( .5f-dim, .5f-dim, .5f-dim );
                    glVertex3f( x2, y1, 0.3f );
                    glVertex3f( x2, y2, 0.3f );
                } glEnd();

                dim += .1f;
                inset = 0;
                frameTime = uint128_t( x.high(), 0 );
                if( item.frame < startFrame )
                    break;
            }
            else if( item.entity != last->entity )
                inset = 0;
            else if( item.layer != last->layer )
                inset += space;

            const uint64_t startTime = item.start / scale;
            const uint64_t endTime   = item.end   / scale;
            const float x1 = static_cast< float >( startTime - x.low( ));
            const float x2 = static_cast< float >( endTime   - x.low( ));

            frameTime.low() = LB_MIN( frameTime.low(), startTime );
            frameTime.high() = LB_MAX( frameTime.high(), endTime   );

            const ThreadSet& threads = entities[ item.entity ];
            const ThreadSetCIter j = threads.find( item.thread );
            const uint32_t y = yPos[ item.entity ] - 
                std::distance( threads.begin(), j ) * (barHeight + space);

            float y1 = static_cast< float >( y - inset );
            float y2 = static_cast< float >( y - barHeight + inset );
            LBASSERTINFO( y2 < y1, y2 << " >= " << y1 );

            glColor3fv( item.color );
            glBegin( GL_QUADS ); {
                glVertex3f( x2, y1, 0.f );
                glVertex3f( x1, y1, 0.f );
                glVertex3f( x1, y2, 0.f);
                glVertex3f( x2, y2, 0.f );
            } glEnd();

#if 0
            if( !text.str().empty( ))
            {
                glColor3f( 1.f, 1.f, 1.f );
                glRasterPos3f( x1+1, y2, 0.f );
                font->draw( text.str( ));
            }
#endif
            last = &item;
        }
    }

#if 0
    glLogicOp( GL_XOR );
    glEnable( GL_COLOR_LOGIC_OP );

    //----- Entitity names
    for( std::map< uint32_t, EntityData >::const_iterator i = entities.begin();
         i != entities.end(); ++i )
    {
        const EntityData& data = i->second;

        glColor3f( 1.f, 1.f, 1.f );
        glRasterPos3f( 60.f, data.yPos - (barHeight + space), 0.99f );
        font->draw( data.name );

        std::stringstream downloaders;
        for( std::set<uint32_t>::const_iterator j = data.downloaders.begin();
             j != data.downloaders.end(); ++j )
        {
            downloaders << " 0x" << std::hex << *j << std::dec;
        }
        if( !downloaders.str().empty( ))
        {
            if( data.threads[THREAD_ASYNC1] )
            {
                glRasterPos3f( 80.f, data.yPos - 2 * (barHeight + space), 0.99f );
                font->draw( "read" );
            }
            else
                font->draw( std::string( ", r" ) + downloaders.str( ));

            font->draw( downloaders.str( ));
        }

        std::stringstream compressors;
        for( std::set<uint32_t>::const_iterator j = data.compressors.begin();
             j != data.compressors.end(); ++j )
        {
            compressors << " 0x" << std::hex << *j << std::dec;
        }
        if( !compressors.str().empty( ))
        {
            const float y = data.yPos - data.threads.count() * (barHeight + space);
            glRasterPos3f( 80.f, y, 0.99f );
            font->draw( std::string( "compress" ) + compressors.str( ));
        }
    }

    //----- Global stats (scale, GPU idle)
    glColor3f( 1.f, 1.f, 1.f );
    nextY -= (barHeight + space);
    glRasterPos3f( 60.f, static_cast< float >( nextY ), 0.99f );
    std::ostringstream text;
    text << scale << "ms/pixel";

    if( !idles.empty( ))
        text << ", Idle:";

    for( std::map< uint32_t, IdleData >::const_iterator i = idles.begin();
         i != idles.end(); ++i )
    {
        const IdleData& data = i->second;
        LBASSERT( data.nIdle > 0 );

        text << " " << data.name << ":" << data.idle / data.nIdle << "%";
    }

    font->draw( text.str( ));
    
    //----- Legend
    nextY -= space;
    float x = 0.f;

    glRasterPos3f( x+1.f, nextY-12.f, 0.f );
    glColor3f( 1.f, 1.f, 1.f );
    font->draw( "channel" );
    glDisable( GL_COLOR_LOGIC_OP );

    for( size_t i = 1; i < Statistic::CONFIG_START_FRAME; ++i )
    {
        const Statistic::Type type = static_cast< Statistic::Type >( i );
        if( type == Statistic::CHANNEL_DRAW_FINISH ||
            type == Statistic::PIPE_IDLE || type == Statistic::WINDOW_FPS ||
            type == Statistic::CHANNEL_ASYNC_READBACK )
        {
            continue;
        }

        switch( type )
        {
          case Statistic::CHANNEL_FRAME_TRANSMIT:
            x = 0.f;
            nextY -= (barHeight + space);

            glColor3f( 1.f, 1.f, 1.f );
            glRasterPos3f( x+1.f, nextY-12.f, 0.f );
            break;

          case Statistic::WINDOW_FINISH:
            x = 0.f;
            nextY -= (barHeight + space);

            glColor3f( 1.f, 1.f, 1.f );
            glRasterPos3f( x+1.f, nextY-12.f, 0.f );
            glEnable( GL_COLOR_LOGIC_OP );
            font->draw( "window" );
            glDisable( GL_COLOR_LOGIC_OP );
            break;

          case Statistic::NODE_FRAME_DECOMPRESS:
            x = 0.f;
            nextY -= (barHeight + space);

            glColor3f( 1.f, 1.f, 1.f );
            glRasterPos3f( x+1.f, nextY-12.f, 0.f );
            glEnable( GL_COLOR_LOGIC_OP );
            font->draw( "node" );
            glDisable( GL_COLOR_LOGIC_OP );
            break;

          default:
            break;
        }

        x += 60.f;
        const float x2 = x + 60.f - space; 
        const float y1 = static_cast< float >( nextY );
        const float y2 = static_cast< float >( nextY - barHeight );

        glColor3fv( Statistic::getColor( type ).array );
        glBegin( GL_QUADS );
            glVertex3f( x2, y1, 0.f );
            glVertex3f( x,  y1, 0.f );
            glVertex3f( x,  y2, 0.f );
            glVertex3f( x2, y2, 0.f );
        glEnd();

        glColor3f( 0.f, 0.f, 0.f );
        glRasterPos3f( x+1.f, nextY-12.f, 0.f );
        font->draw( Statistic::getName( type ));
    }
    
    glColor3f( 1.f, 1.f, 1.f );
    window->drawFPS();
    EQ_GL_CALL( resetAssemblyState( ));
#endif

    uint32_t width;
    uint32_t height;
};
}

Renderer::Renderer()
        : impl_( new detail::Renderer )
{}

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

void Renderer::draw( Data& data )
{
    impl_->draw( data );
}

}
