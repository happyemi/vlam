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

#include "random.h"
#include <random>
#include <chrono>

namespace Util
{

// Concrete implementation of the RNG interface
class ConcreteRNG : public RNG
{
public:
	ConcreteRNG(unsigned int seed);

	int get_int(int min, int max) override;
	unsigned int get_uint(unsigned int min, unsigned int max) override;
	unsigned int get_seed() const override;
private:
	unsigned int seed;
	std::minstd_rand rand_engine;
};

ConcreteRNG::ConcreteRNG(unsigned int seed) : seed(seed), rand_engine(seed) 
{
}

int ConcreteRNG::get_int(int min, int max)
{
	std::uniform_int_distribution<int> rand(min, max);
	return rand(rand_engine);
}

unsigned int ConcreteRNG::get_uint(unsigned int min, unsigned int max)
{
	std::uniform_int_distribution<unsigned int> rand(min, max);
	return rand(rand_engine);
}

unsigned int ConcreteRNG::get_seed() const
{
	return seed;
}

RNG::Ptr create_RNG(unsigned int seed)
{
	return std::make_shared<ConcreteRNG>(seed);
}

RNG::Ptr create_RNG()
{
	return std::make_shared<ConcreteRNG>(std::chrono::system_clock::now().time_since_epoch().count());
}

}
