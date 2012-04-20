
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

namespace GLStats
{
    /** One statistics item. */
    struct Item
    {
        Item() : start( -1 ), end( -1 ), order( 0 ), entity( 0 ), thread( 0 )
               , frame( 0 ) {}

        int64_t start;  //!< Beginning of the event
        int64_t end;    //!< End of the event
        uint32_t order; //!< Depth of a (sub-)event
        uint32_t entity; //!< Identifier of the reporting entity
        uint32_t thread; //!< Identifier of the reporting thread
        uint32_t frame; //!< The rendering frame number
    };
}

#endif //GLSTATS_ITEM_H
