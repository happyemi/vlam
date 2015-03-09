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

#ifndef VLAM_H_
#define VLAM_H_

#include <iosfwd>

namespace Vlam
{

// Parse an input stream and ouput the resulting text into ostream. Use the specified seed to initialize the random engine
void parse(std::istream& istream, std::ostream& ostream, unsigned int seed);

// Parse an input stream and ouput the resulting text into ostream. 
void parse(std::istream& istream, std::ostream& ostream);

}

#endif

