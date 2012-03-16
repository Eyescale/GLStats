
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

/** Basic type definitions not provided by the operating system. */

#ifndef GLSTATS_TYPES_H
#define GLSTATS_TYPES_H

#include <lunchbox/types.h>
#include <deque>

namespace GLStats
{
class Data;
class Renderer;
struct Entity;
struct Item;
struct Thread;

using lunchbox::uint128_t;
using lunchbox::Strings;
using lunchbox::StringsCIter;

typedef std::deque< Item > Items;
}

#endif //GLSTATS_TYPES_H
