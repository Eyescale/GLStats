
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
#include <GLStats/types.h>

namespace GLStats
{
namespace detail { class Data; }

    /** The data storage. */
    class Data
    {
    public:
        /** Construct a new data storage. */
        GLSTATS_API Data();

        /** Destruct this data storage. */
        GLSTATS_API virtual ~Data();

        /** Add an entity description. */
        GLSTATS_API void addEntity( const uint32_t identifier,
                                    const Entity& entity );

        /** @return the entity description for the given id. */
        const Entity& getEntity( const uint32_t identifier ) const;

        /** Add a thread description. */
        GLSTATS_API void addThread( const uint32_t identifier,
                                    const Thread& thread );

        /** @return the thread description for the given id. */
        const Thread& getThread( const uint32_t identifier ) const;

        /** Add a statistics item. */
        GLSTATS_API void addItem( const Item& item );

        /** @return the vector of items for the frame of the given age. */
        GLSTATS_API const Items& getItems() const;

        /** @return the min and max time for the last n frames. */
        GLSTATS_API uint128_t computeMinMax( const uint32_t nFrames );

        /** Add additional text at the bottom. */
        GLSTATS_API void addText( const std::string& text );

        /** Remove all additional text. */
        GLSTATS_API void clearText();

        /** @return all additional text. */
        GLSTATS_API const Strings& getText() const;

    private:
        detail::Data* const impl_;
    };
}

#endif //GLSTATS_DATA_H
