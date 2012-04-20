
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

#ifndef GLSTATS_THREAD_H
#define GLSTATS_THREAD_H

#include <GLStats/api.h>

namespace GLStats
{
    /** One statistics thread. */
    struct Thread
    {
        Thread() : identifier( 0 ) {}

        uint32_t identifier; //!< Thread identifier used in item
        std::string name; //!< Name printed in statistics
    };
}

#endif //GLSTATS_THREAD_H
