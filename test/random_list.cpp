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

BOOST_FIXTURE_TEST_SUITE(random_list, RandomListFixture)

BOOST_AUTO_TEST_CASE(test_empty_list)
{
	std::string text = "<{}>";
	std::stringstream in(text);
	Vlam::ParseResult target = Vlam::parse(in, Vlam::VariablesMap());
	BOOST_REQUIRE_EQUAL(target.text, "");
}

BOOST_AUTO_TEST_CASE(test_list_with_one_element)
{
	std::string text = "<{test}>";
	std::stringstream in(text);
	Vlam::ParseResult target = Vlam::parse(in, Vlam::VariablesMap());
	BOOST_REQUIRE_EQUAL(target.text, "test");
}

BOOST_AUTO_TEST_CASE(test_list_with_two_elements_can_select_first_element)
{
	std::string text = "<{first|second}>";
	std::stringstream in(text);
	fake_rng->value = 0;
	Parser parser(in, Vlam::VariablesMap(), fake_rng);
	parser.parse();
	Vlam::ParseResult target = parser.get_result();
	BOOST_REQUIRE_EQUAL(target.text, "first");
}

BOOST_AUTO_TEST_CASE(test_list_with_two_elements_can_select_second_element)
{
	std::string text = "<{first|second}>";
	std::stringstream in(text);
	fake_rng->value = 1;
	Parser parser(in, Vlam::VariablesMap(), fake_rng);
	parser.parse();
	Vlam::ParseResult target = parser.get_result();
	BOOST_REQUIRE_EQUAL(target.text, "second");
}

BOOST_AUTO_TEST_CASE(test_can_have_list_in_text)
{
	std::string text = "<Hello {first|second} world>";
	std::stringstream in(text);
	fake_rng->value = 1;
	Parser parser(in, Vlam::VariablesMap(), fake_rng);
	parser.parse();
	Vlam::ParseResult target = parser.get_result();
	BOOST_REQUIRE_EQUAL(target.text, "Hello second world");
}

BOOST_AUTO_TEST_CASE(test_can_nest_empty_lists)
{
	std::string text = "<{{}}>";
	std::stringstream in(text);
	fake_rng->value = 0;
	Parser parser(in, Vlam::VariablesMap(), fake_rng);
	parser.parse();
	Vlam::ParseResult target = parser.get_result();
	BOOST_REQUIRE_EQUAL(target.text, "");
}

BOOST_AUTO_TEST_CASE(test_can_nest_lists)
{
	std::string text = "<Hello {first|{second|third}} world>";
	std::stringstream in(text);
	fake_rng->value = 1;
	Parser parser(in, Vlam::VariablesMap(), fake_rng);
	parser.parse();
	Vlam::ParseResult target = parser.get_result();
	BOOST_REQUIRE_EQUAL(target.text, "Hello third world");
}

BOOST_AUTO_TEST_CASE(test_can_nest_lists_concatenated_to_text)
{
	std::string text = "<Hello {first|my {second|third} lovely} world>";
	std::stringstream in(text);
	fake_rng->value = 1;
	Parser parser(in, Vlam::VariablesMap(), fake_rng);
	parser.parse();
	Vlam::ParseResult target = parser.get_result();
	BOOST_REQUIRE_EQUAL(target.text, "Hello my third lovely world");
}

BOOST_AUTO_TEST_CASE(test_can_nest_optional_text)
{
	std::string text = "<Hello {first|my [second]} world>";
	std::stringstream in(text);
	fake_rng->value = 1;
	Parser parser(in, Vlam::VariablesMap(), fake_rng);
	parser.parse();
	Vlam::ParseResult target = parser.get_result();
	BOOST_REQUIRE_EQUAL(target.text, "Hello my second world");
}

BOOST_AUTO_TEST_SUITE_END()
