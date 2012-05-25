
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

#include "data.h"

#include "entity.h"
#include "item.h"
#include "thread.h"
#include "type.h"

#include <lunchbox/stdExt.h>
#include <limits>

namespace GLStats
{
typedef stde::hash_map< uint32_t, Entity > EntityMap;
typedef EntityMap::const_iterator EntityMapCIter;
typedef stde::hash_map< uint32_t, Thread > ThreadMap;
typedef ThreadMap::const_iterator ThreadMapCIter;
typedef Items::const_iterator ItemsCIter;

namespace detail
{
Entity nullEntity_;
Thread nullThread_;
Type nullType_;

static bool _compare( const Item& i1, const Item& i2 )
{
    if( i1.entity != i2.entity )
        return i1.entity < i2.entity;
    if( i1.thread != i2.thread )
        return i1.thread < i2.thread;
    if( i1.frame != i2.frame )
        return i1.frame < i2.frame;
    return i1.layer < i2.layer;
}

class Data
{
public:
    uint128_t computeMinMax( const uint32_t nFrames ) const
    {
        uint64_t xMax = 0;
        uint64_t xMin = std::numeric_limits< uint64_t >::max();

        uint32_t startFrame = items.back().frame;
        startFrame = startFrame > nFrames ? startFrame - nFrames : 0;

        for( ItemsCIter i = items.begin(); i != items.end(); ++i )
        {
            const Item& item = *i;
            xMin = LB_MIN( xMin, item.start );
            xMax = LB_MAX( xMax, item.end );
        }
        return uint128_t( xMax, xMin );
    }

    void obsolete( const uint32_t nFrames )
    {
        sort();
        if( items.empty( ))
            return;

        uint32_t startFrame = items.back().frame;
        startFrame = startFrame > nFrames ? startFrame - nFrames : 0;

        while( items.front().frame < startFrame )
            items.pop_front();
    }

    void sort() { std::sort( items.begin(), items.end(), _compare ); }

    EntityMap entities;
    ThreadMap threads;
    TypeMap types;
    Items items;
    Strings text;
};
}

Data::Data()
        : impl_( new detail::Data )
{}

Data::~Data()
{
    delete impl_;
}

void Data::addEntity( const uint32_t identifier, const Entity& entity )
{
    impl_->entities[ identifier ] = entity;
}

const Entity& Data::getEntity( const uint32_t identifier ) const
{
    const EntityMapCIter i = impl_->entities.find( identifier );
    if( i == impl_->entities.end( ))
        return detail::nullEntity_;
    return i->second;
}

void Data::addThread( const uint32_t identifier, const Thread& thread )
{
    impl_->threads[ identifier ] = thread;
}

const Thread& Data::getThread( const uint32_t identifier ) const
{
    const ThreadMapCIter i = impl_->threads.find( identifier );
    if( i == impl_->threads.end( ))
        return detail::nullThread_;
    return i->second;
}

void Data::addType( const uint32_t identifier, const Type& type )
{
    impl_->types[ identifier ] = type;
}

const Type& Data::getType( const uint32_t identifier ) const
{
    const TypeMapCIter i = impl_->types.find( identifier );
    if( i == impl_->types.end( ))
        return detail::nullType_;
    return i->second;
}

const TypeMap& Data::getTypes() const
{
    return impl_->types;
}

void Data::addItem( const Item& item )
{
    impl_->items.push_back( item );
}

const Items& Data::getItems() const
{
    return impl_->items;
}

uint128_t Data::computeMinMax( const uint32_t nFrames ) const
{
    return impl_->computeMinMax( nFrames );
}

void Data::addText( const std::string& text )
{
    impl_->text.push_back( text );
}

void Data::clearText()
{
    impl_->text.clear();
}

const Strings& Data::getText() const
{
    return impl_->text;
}

}
