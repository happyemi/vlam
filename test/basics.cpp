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

#include <vlam/vlam.h>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(basics)

BOOST_AUTO_TEST_CASE(test_basic_copy)
{
	std::string text = "<This is some basic text>";
	std::stringstream in(text), target;
	Vlam::parse(in, target);
	BOOST_REQUIRE_EQUAL(target.str(), "This is some basic text");
}

BOOST_AUTO_TEST_CASE(test_can_copy_newline)
{
	std::string text = "<This is some basic text\nAnd another line>";
	std::stringstream in(text), target;
	Vlam::parse(in, target);
	BOOST_REQUIRE_EQUAL(target.str(), "This is some basic text\nAnd another line");
}

BOOST_AUTO_TEST_CASE(test_can_copy_empty_text)
{
	std::string text = "";
	std::stringstream in(text), target;
	Vlam::parse(in, target);
	BOOST_REQUIRE_EQUAL(target.str(), text);
}

BOOST_AUTO_TEST_SUITE_END()
