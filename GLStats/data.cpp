
/* Copyright (c) 2012-2017, Stefan Eilemann <eile@eyescale.ch>
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

#include "data.h"

#include "entity.h"
#include "item.h"
#include "thread.h"
#include "type.h"

#include <lunchbox/debug.h>
#include <servus/uint128_t.h>

#include <limits>
#include <unordered_map>

namespace GLStats
{
typedef std::unordered_map<uint32_t, Entity> EntityMap;
typedef EntityMap::const_iterator EntityMapCIter;
typedef std::unordered_map<uint32_t, Thread> ThreadMap;
typedef ThreadMap::const_iterator ThreadMapCIter;
typedef Items::const_iterator ItemsCIter;
typedef Items::iterator ItemsIter;

namespace detail
{
Entity nullEntity_;
Thread nullThread_;
Type nullType_;

class Data
{
public:
    uint128_t computeMinMax() const
    {
        uint64_t xMax = 0;
        uint64_t xMin = std::numeric_limits<uint64_t>::max();

        for (ItemsCIter i = items.begin(); i != items.end(); ++i)
        {
            const Item& item = *i;
            xMin = LB_MIN(xMin, item.start);
            xMax = LB_MAX(xMax, item.end);
        }
        return uint128_t(xMax, xMin);
    }

    void obsolete(const uint32_t nFrames)
    {
        if (items.empty())
            return;

        uint32_t startFrame = 0;
        for (ItemsCIter i = items.begin(); i != items.end(); ++i)
            if ((*i).frame > startFrame)
                startFrame = (*i).frame;

        startFrame = startFrame > nFrames ? startFrame - nFrames : 0;
        if (startFrame == 0)
            return;

        for (ItemsIter i = items.begin(); i != items.end();)
        {
            if ((*i).frame < startFrame)
                i = items.erase(i);
            else
                ++i;
        }
    }

    EntityMap entities;
    ThreadMap threads;
    TypeMap types;
    Items items;
    std::string text;
};
}

Data::Data()
    : impl_(new detail::Data)
{
}

Data::Data(const Data& from)
    : impl_(new detail::Data(*from.impl_))
{
}

Data::~Data()
{
    delete impl_;
}

void Data::setEntity(const uint32_t identifier, const Entity& entity)
{
    impl_->entities[identifier] = entity;
}

const Entity& Data::getEntity(const uint32_t identifier) const
{
    const EntityMapCIter i = impl_->entities.find(identifier);
    if (i == impl_->entities.end())
        return detail::nullEntity_;
    return i->second;
}

void Data::setThread(const uint32_t identifier, const Thread& thread)
{
    impl_->threads[identifier] = thread;
}

const Thread& Data::getThread(const uint32_t identifier) const
{
    const ThreadMapCIter i = impl_->threads.find(identifier);
    if (i == impl_->threads.end())
        return detail::nullThread_;
    return i->second;
}

void Data::setType(const uint32_t identifier, const Type& type)
{
    impl_->types[identifier] = type;
}

const Type& Data::getType(const uint32_t identifier) const
{
    const TypeMapCIter i = impl_->types.find(identifier);
    if (i == impl_->types.end())
        return detail::nullType_;
    return i->second;
}

const TypeMap& Data::getTypes() const
{
    return impl_->types;
}

void Data::addItem(const Item& item)
{
    LBASSERTINFO(item.start <= item.end, item);
    impl_->items.push_back(item);
}

const Items& Data::getItems() const
{
    return impl_->items;
}

uint128_t Data::computeMinMax() const
{
    return impl_->computeMinMax();
}

void Data::setText(const std::string& text)
{
    impl_->text = text;
}

const std::string& Data::getText() const
{
    return impl_->text;
}

void Data::obsolete(const uint32_t nFrames)
{
    impl_->obsolete(nFrames);
}

void Data::clear()
{
    impl_->entities.clear();
    impl_->threads.clear();
    impl_->types.clear();
    impl_->items.clear();
    impl_->text.clear();
}
}
