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

%x content

%%

\=                                     return matched()[0];
\<                                     begin(StartCondition__::content); return matched()[0];
[\n \t]
.                                      return Parser::TEXT;

<content>[\[\]{}|]                     return matched()[0];
<content>\>                            begin(StartCondition__::INITIAL); return matched()[0];
<*>\$[a-zA-Z0-9]*                      return Parser::IDENTIFIER;
<content>[\n()a-zA-Z0-9 ,.;:'?!"]*     return Parser::TEXT;
<content>.
<<EOF>>                                return 0;
