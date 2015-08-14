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
#include <vlam/grammar/parser.h>
#include <vlam/util/random.h>
#include <istream>

// Global variables and definitions shared between this file, the parser and the lexer
// Hopefully everything can be cleaned up when switching to a reentrant parser
namespace
{
std::istream* input_stream; // The current input stream
const int max_buffer = 4096; 
char data[max_buffer];      // buffer used to feed data to the lexer
}

namespace Vlam
{

// Used by the parser, these three variables hold data about current parsing execution
ParseResult current_result;
Util::RNG::Ptr current_rng;
std::string error_msg;

// Invoked by the lexer to fetch more data
void fetch_bytes(char*& buffer, int& bytes_read)
{
	buffer = data;
	input_stream->read(buffer, max_buffer - 2);
	bytes_read = input_stream->gcount();
	buffer[bytes_read] = 0;
}

}

// Used to initialize/invoke/get info from the lexer
extern void yylex_destroy();
extern "C" int yywrap();
	

namespace Vlam
{

ParseResult parse(std::istream& istream, const VariablesMap& variables, Util::RNG::Ptr rng)
{
	// Initialize global variables
	input_stream = &istream;
	current_result = ParseResult();
	current_result.variables = variables;
	current_rng = rng;
	current_result.seed = rng->get_seed();
	int parsing_result = 0;

	// Initialize the lexer and start parsing
	if(yywrap() == 0)
	{
		parsing_result = yyparse();
	}

	// Clean up lexer data
	yylex_destroy();

	// Throw an error if necessary
	if(parsing_result != 0)
	{
		throw ParseError(error_msg);
	}

	return current_result;
}

ParseResult parse(std::istream& istream, const VariablesMap& variables, unsigned int seed)
{
	return parse(istream, variables, Util::create_RNG(seed));
}

ParseResult parse(std::istream& istream, const VariablesMap& variables)
{
	return parse(istream, variables, Util::create_RNG());
}

ParseError::ParseError(const std::string& message) : msg(message)
{
}

}
