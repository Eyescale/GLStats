
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

#ifndef GLSTATS_ITEM_H
#define GLSTATS_ITEM_H

#include <GLStats/api.h>
#include <iostream>

namespace GLStats
{
    /** One statistics item. */
    struct Item
    {
        Item() : start( -1 ), end( -1 ), type( 0 ), entity( 0 ), thread( 0 )
               , frame( 0 ), layer( 0 )
            {}

        uint64_t start;   //!< Beginning of the event
        uint64_t end;     //!< End of the event
        uint32_t type;    //!< Event type
        uint32_t entity;  //!< Identifier of the reporting entity
        uint32_t thread;  //!< Identifier of the reporting thread
        uint32_t frame;   //!< The rendering frame number
        uint32_t layer;   //!< Depth of a (sub-)event
        std::string text; //!< Optional string at the end of the item
    };

    inline std::ostream& operator << ( std::ostream& os, const Item& item )
    {
        return os << item.entity << '.' << item.thread << "@ " << item.frame
                  << "(" << item.start << '-' << item.end << "):" << item.type ;
    }
}

#endif //GLSTATS_ITEM_H
