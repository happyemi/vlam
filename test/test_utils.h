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

#ifndef TEST_UTILS_H_
#define TEST_UTILS_H_

#include <vlam/util/random.h>
#include <vlam/vlam.h>

class FakeRNG : public Vlam::Util::RNG
{
public:
	using Ptr = std::shared_ptr<FakeRNG>;

	int value;

	int get_int(int min, int max) override { return 0; }
	unsigned int get_uint(unsigned int min, unsigned int max) override { return value; }
	unsigned int get_seed() const override { return 0; }
};

namespace Vlam
{

extern ParseResult parse(std::istream& istream, const VariablesMap& variables, Util::RNG::Ptr rng);

}

#endif

