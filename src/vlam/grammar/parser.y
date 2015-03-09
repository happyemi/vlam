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

%polymorphic STRING: std::string; 
             VCT_STR: std::shared_ptr<std::vector<std::string>>

%type <STRING> text
%type <STRING> concatenated_text
%type <VCT_STR> element_list

%token TEXT

%%

output:                                               {}
         | output text                                { out << $2; };

text:                                   
         TEXT                                         { $$ = d_scanner.matched(); }
         | '{' element_list '}'                       { $$ = Util::get_random_element(*$2, rng); };

concatenated_text: 
		 text                                         { $$ = $1; }
		 | concatenated_text text                     { $$ = $1 + $2; };

element_list:                                         { $$ = std::make_shared<std::vector<std::string>>(); }
         | concatenated_text                          { $$ = std::make_shared<std::vector<std::string>>(); $$->push_back($1); }
         | element_list '|' concatenated_text         { $1->push_back($3); $$ = $1; };

