
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
#include "thread.h"

#include <lunchbox/stdExt.h>

namespace GLStats
{
typedef stde::hash_map< uint32_t, Entity > EntityMap;
typedef stde::hash_map< uint32_t, Thread > ThreadMap;

namespace detail
{
class Data
{
public:
    EntityMap entities;
    ThreadMap threads;
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

void Data::addThread( const uint32_t identifier, const Thread& thread )
{
    impl_->threads[ identifier ] = thread;
}

void Data::addItem( const Item& item )
{
    
}

}
