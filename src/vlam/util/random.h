/*
 *     Copyright 2014-2015 Emiliano Mennucci
 *
 *     This file is part of VLAM.
 *
 *     VLAM is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 *
 *     VLAM is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with VLAM.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef RANDOM_H_
#define RANDOM_H_

#include <memory>

namespace Vlam
{

namespace Util
{

// RNG is an interface that can be used to get random numbers. A concrete implementation can be
// got by calling create_RNG functions. Unit tests can use this interface to implement fakes.
class RNG
{
public:
	using Ptr = std::shared_ptr<RNG>;

	// Returns an integer X so that min <= X <= max
	virtual int get_int(int min, int max) = 0;

	// Returns an unsigned integer X so that min <= X <= max
	virtual unsigned int get_uint(unsigned int min, unsigned int max) = 0;
	
	// Returns the seed currently used by the engine
	virtual unsigned int get_seed() const = 0;

	virtual ~RNG() = default;
};

// Returns a concrete implementation of the RNG interface. The random engine is initialized with
// the given seed
RNG::Ptr create_RNG(unsigned int seed);

// Returns a concrete implementation of the RNG interface. The current system time will be used as 
// random seed
RNG::Ptr create_RNG();

}

}

#endif

