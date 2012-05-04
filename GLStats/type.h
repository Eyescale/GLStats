
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

#ifndef GLSTATS_TYPE_H
#define GLSTATS_TYPE_H

#include <GLStats/api.h>

namespace GLStats
{
    /** One statistics type. */
    struct Type
    {
        Type()
            {
                color[0] = 1.f;
                color[1] = 1.f;
                color[2] = 1.f; 
                color[3] = .6f;
            }

        std::string name;     //!< Description of the event type
        std::string group;    //!< Name of the entity/group
        std::string subgroup; //!< Name of the thread/subgroup
        float color[4];       //!< Base color of the event
    };
}

#endif // GLSTATS_TYPE_H
