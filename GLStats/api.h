 
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

/** Defines export visibility macros for GLStats. */
#ifndef GLSTATS_API_H
#define GLSTATS_API_H

#if defined(_MSC_VER) || defined(__declspec)
#  define LB_DLLEXPORT __declspec(dllexport)
#  define LB_DLLIMPORT __declspec(dllimport)
#else // _MSC_VER
#  define LB_DLLEXPORT
#  define LB_DLLIMPORT
#endif // _MSC_VER

#if defined(GLSTATS_STATIC)
#  define GLSTATS_API
#elif defined(GLSTATS_SHARED)
#  define GLSTATS_API LB_DLLEXPORT
#else
#  define GLSTATS_API LB_DLLIMPORT
#endif

#endif //GLSTATS_API_H
