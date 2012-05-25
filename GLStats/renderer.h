
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

#ifndef GLSTATS_RENDERER_H
#define GLSTATS_RENDERER_H

#include <GLStats/api.h>
#include <GLStats/types.h>

namespace GLStats
{
namespace detail { class Renderer; }

    /** The default renderer. */
    class Renderer
    {
    public:
        /** Construct a new renderer. */
        GLSTATS_API Renderer();
        
        /** Destruct this renderer. */
        GLSTATS_API virtual ~Renderer();

        /** Set the size of the rendering area in pixels. */
        GLSTATS_API void setViewport( const uint32_t width,
                                      const uint32_t height );

        /** Remove unneeded items from the data set. */
        GLSTATS_API void obsolete( Data& data );

        /**
         * Render the data set.
         *
         * The OpenGL state has to be set up to ...
         * @param data the statistics data
         */
        GLSTATS_API void draw( const Data& data );

    protected:
        virtual void drawText( const std::string& text ) = 0;

    private:
        detail::Renderer* const impl_;
        friend class detail::Renderer;
    };
}

#endif //GLSTATS_RENDERER_H
