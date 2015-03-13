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

#include "vlam.h"
#include <vlam/grammar/Parser.h>
#include <vlam/util/random.h>

namespace Vlam
{

static ParseResult parse(std::istream& istream, const VariablesMap& variables, Util::RNG::Ptr rng)
{
	Parser parser(istream, variables, rng);
	parser.parse();
	return parser.get_result();
}

ParseResult parse(std::istream& istream, const VariablesMap& variables, unsigned int seed)
{
	return parse(istream, variables, Util::create_RNG(seed));
}

ParseResult parse(std::istream& istream, const VariablesMap& variables)
{
	return parse(istream, variables, Util::create_RNG());
}

ParseError::ParseError(int line_no) : line_no(line_no)
{
	std::stringstream ss;
	ss << "Parsing error on line " << line_no << std::endl;
	msg = ss.str();
}

}
