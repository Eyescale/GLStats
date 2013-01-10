
/* Copyright (c) 2012-2013, Stefan Eilemann <eile@eyescale.ch>
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

        /** Construct a copy of the data storage. */
        GLSTATS_API Data( const Data& from );

        /** Destruct this data storage. */
        GLSTATS_API virtual ~Data();

        /** Set an entity description. */
        GLSTATS_API void setEntity( const uint32_t identifier,
                                    const Entity& entity );

        /** @return the entity description for the given id. */
        const Entity& getEntity( const uint32_t identifier ) const;

        /** Set a thread description. */
        GLSTATS_API void setThread( const uint32_t identifier,
                                    const Thread& thread );

        /** @return the thread description for the given id. */
        const Thread& getThread( const uint32_t identifier ) const;

        /** Set an type description. */
        GLSTATS_API void setType( const uint32_t identifier, const Type& type );

        /** @return the type description for the given id. */
        const Type& getType( const uint32_t identifier ) const;

        /** @return the map of all types. */
        GLSTATS_API const TypeMap& getTypes() const;

        /** Add a statistics item. */
        GLSTATS_API void addItem( const Item& item );

        /** @return the vector of items for the frame of the given age. */
        GLSTATS_API const Items& getItems() const;

        /** @return the min and max time of the dataset. */
        GLSTATS_API uint128_t computeMinMax() const;

        /** Set additional text at the bottom. */
        GLSTATS_API void setText( const std::string& text );

        /** @return the additional text. */
        GLSTATS_API const std::string& getText() const;

        /** Obsolete all data older than the given number of frames. */
        GLSTATS_API void obsolete( const uint32_t nFrames );

    private:
        detail::Data* const impl_;
    };
}

#endif //GLSTATS_DATA_H
