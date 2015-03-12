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

struct OptionalTextFixture
{
	FakeRNG::Ptr fake_rng;
	OptionalTextFixture()
	{ 
		fake_rng = std::make_shared<FakeRNG>();
	}
};

BOOST_FIXTURE_TEST_SUITE(optional_text, OptionalTextFixture)

BOOST_AUTO_TEST_CASE(test_empty_text)
{
	std::string text = "<[]>";
	std::stringstream in(text);
	Vlam::ParseResult target = Vlam::parse(in, Vlam::VariablesMap());
	BOOST_REQUIRE_EQUAL(target.text, "");
}

BOOST_AUTO_TEST_CASE(test_test_is_not_selected)
{
	std::string text = "<[test]>";
	std::stringstream in(text);
	fake_rng->value = 0;
	Vlam::Parser parser(in, Vlam::VariablesMap(), fake_rng);
	parser.parse();
	Vlam::ParseResult target = parser.get_result();
	BOOST_REQUIRE_EQUAL(target.text, "");
}

BOOST_AUTO_TEST_CASE(test_test_is_selected)
{
	std::string text = "<[test]>";
	std::stringstream in(text);
	fake_rng->value = 1;
	Vlam::Parser parser(in, Vlam::VariablesMap(), fake_rng);
	parser.parse();
	Vlam::ParseResult target = parser.get_result();
	BOOST_REQUIRE_EQUAL(target.text, "test");
}

BOOST_AUTO_TEST_CASE(test_can_nest_random_lists)
{
	std::string text = "<[Test {a|b}]>";
	std::stringstream in(text);
	fake_rng->value = 1;
	Vlam::Parser parser(in, Vlam::VariablesMap(), fake_rng);
	parser.parse();
	Vlam::ParseResult target = parser.get_result();
	BOOST_REQUIRE_EQUAL(target.text, "Test b");
}

BOOST_AUTO_TEST_SUITE_END()

