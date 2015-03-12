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
#include <string>
#include <map>

namespace Vlam
{

using VariablesMap = std::map<std::string, std::string>;

// Contains the parsing result.
struct ParseResult
{
	VariablesMap variables;
	unsigned int seed;
	std::string text;
};

// Parses an input stream and returns a ParseResult object. Uses the specified seed to initialize the random engine
ParseResult parse(std::istream& istream, const VariablesMap& variables, unsigned int seed);

// Parses an input stream and returns a ParseResult object. The random seed will be generated based on the current time
ParseResult parse(std::istream& istream, const VariablesMap& variables);

}

#endif

