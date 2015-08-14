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

%{

// Lexer function
int yylex();

#include <string>
#include <boost/any.hpp>
#include <vlam/util/helpers.h>
#include <vlam/vlam.h>

#define STR(x) boost::any_cast<std::string>(x)
#define VSTR(x) boost::any_cast<std::vector<std::string>>(x)

// Globals used by bison for the current parsing
namespace Vlam
{

extern ParseResult current_result;
extern Util::RNG::Ptr current_rng;
extern std::string error_msg; //last error

}

void yyerror(char const* msg)
{
	Vlam::error_msg = msg;
}

%}

%define parse.error verbose

%define api.value.type {boost::any}

%token TEXT
%token IDENTIFIER

%%

output:
         | output definition;

definition:
         '<' concatenated_text '>'                    { Vlam::current_result.text = STR($2); }
         | identifier '=' '<' concatenated_text '>'   { Vlam::current_result.variables[STR($1)] = STR($4); };

text:                                   
         TEXT                                         { $$ = STR($1); }
         | identifier                                 { $$ = Vlam::current_result.variables[STR($1)]; }
         | '{' element_list '}'                       { $$ = Vlam::Util::get_random_element(VSTR($2), Vlam::current_rng); }
         | '[' concatenated_text ']'                  { $$ = Vlam::current_rng->get_uint(0, 1) ? STR($2) : std::string(); };

element_list:
         concatenated_text                            { auto v = std::vector<std::string>(); v.push_back(STR($1)); $$ = v; }
         | element_list '|' concatenated_text         { VSTR(&$1)->push_back(STR($3)); $$ = std::move(VSTR($1)); };

concatenated_text:                                    { $$ = std::string(); }
         | concatenated_text text                     { $$ = STR($1) + STR($2); };

identifier:
         IDENTIFIER                                   { auto m = STR($1); $$ = std::string(); STR(&$$)->assign(m.begin() + 1, m.end()); };

