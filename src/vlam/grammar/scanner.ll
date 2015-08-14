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
#include <string>
#include "parser.h"
%}

%option nodefault
%option nounput

%x CONTENT

%%

\=                                     return yytext[0];
\<                                     BEGIN(CONTENT); return yytext[0];
[\n \t]
.                                      yylval = std::string(yytext); return TEXT;

<CONTENT>[\[\]{}|]                     return yytext[0];
<CONTENT>\>                            BEGIN(INITIAL); return yytext[0];
<*>\$[a-zA-Z0-9]+                      yylval = std::string(yytext); return IDENTIFIER;
<CONTENT>[^{}\[\]|\$\<\>]*             yylval = std::string(yytext); return TEXT;
<CONTENT>.                             return yytext[0];

<<EOF>>                                yyterminate();

%%

namespace Vlam
{

// Function called by the lexer to get input data
extern void fetch_bytes(char*& buffer, int& bytes_read);

}

int yywrap()
{
	// Fetch data from the input stream
	char* buffer;
	int bytes_read;
	Vlam::fetch_bytes(buffer, bytes_read);
	
	// If there is no more data to read, return immediatly
	if(bytes_read == 0)
	{
		return 1;
	}
	
	// Finish preparing the buffer and setup the lexer
	buffer[bytes_read] = 0;
	buffer[bytes_read + 1] = 0;
	yy_scan_buffer(buffer, bytes_read + 2);
	return 0;
}

