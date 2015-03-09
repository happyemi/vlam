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

#ifndef Parser_h_included
#define Parser_h_included

#include "Parserbase.h"
#include "Scanner.h"
#include <vlam/util/random.h>
#include <sstream>

#undef Parser
class Parser: public ParserBase
{

public:
	Parser(std::istream& istream, std::ostream& ostream, Util::RNG::Ptr rng) : 
		rng(rng), d_scanner(istream, scanner_output), out(ostream) {}
	int parse();

private:
	std::ostringstream scanner_output;
	Util::RNG::Ptr rng;
	Scanner d_scanner;
	std::ostream& out;

	void error(char const *msg);    // called on (syntax) errors
	int lex();                      // returns the next token from the
	// lexical scanner. 
	void print();                   // use, e.g., d_token, d_loc

	// support functions for parse():
	void executeAction(int ruleNr);
	void errorRecovery();
	int lookup(bool recovery);
	void nextToken();
	void print__();
	void exceptionHandler__(std::exception const &exc);
};


#endif
