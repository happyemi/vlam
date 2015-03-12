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
#include <vlam/grammar/Parser.h>
#include <boost/test/unit_test.hpp>
#include "test_utils.h"

struct RandomListFixture
{
	FakeRNG::Ptr fake_rng;
	RandomListFixture()
	{ 
		fake_rng = std::make_shared<FakeRNG>();
	}
};

BOOST_FIXTURE_TEST_SUITE(variables, RandomListFixture)

BOOST_AUTO_TEST_CASE(test_can_reference_variable)
{
	std::string text = "$var = <My Variable> <This is $var>";
	std::stringstream in(text);
	Vlam::ParseResult target = Vlam::parse(in, Vlam::VariablesMap());
	BOOST_REQUIRE_EQUAL(target.text, "This is My Variable");
}

BOOST_AUTO_TEST_CASE(test_variables_can_be_referenced_after_parsing)
{
	std::string text = "$var = <My Variable> <This is $var>";
	std::stringstream in(text);
	Vlam::ParseResult target = Vlam::parse(in, Vlam::VariablesMap());
	BOOST_REQUIRE_EQUAL(target.variables["var"], "My Variable");
}

BOOST_AUTO_TEST_CASE(test_variables_can_be_injected_before_parsing)
{
	std::string text = "<This is $var>";
	std::stringstream in(text);
	Vlam::ParseResult target = Vlam::parse(in, Vlam::VariablesMap{{"var", "My Variable"}});
	BOOST_REQUIRE_EQUAL(target.text, "This is My Variable");
	BOOST_REQUIRE_EQUAL(target.variables["var"], "My Variable");
}


BOOST_AUTO_TEST_SUITE_END()

