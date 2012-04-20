
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

#ifndef GLSTATS_DATA_H
#define GLSTATS_DATA_H

#include <GLStats/api.h>

namespace GLStats
{
    /** The data storage. */
    class Data
    {
    public:
        /** Construct a new data storage. */
        GLSTATS_API Data();
        GLSTATS_API void addEntity( const Entity& entity );
        GLSTATS_API void addThread( const Thread& thread );
        GLSTATS_API void addItem( const Item& item );
    };
}

#endif //GLSTATS_DATA_H
