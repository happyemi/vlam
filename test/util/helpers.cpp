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

#include <vlam/util/helpers.h>
#include <boost/test/unit_test.hpp>
#include "../test_utils.h"

struct HelpersFixture
{
	FakeRNG::Ptr fake_rng;
	HelpersFixture()
	{ 
		fake_rng = std::make_shared<FakeRNG>();
	}
};

BOOST_FIXTURE_TEST_SUITE(helpers, HelpersFixture)

BOOST_AUTO_TEST_CASE(test_get_random_element)
{
	std::vector<std::string> v;
	v.push_back("test string 1");
	v.push_back("test string 2");

	fake_rng->value = 1;
	std::string target = Util::get_random_element(v, fake_rng);
	BOOST_REQUIRE_EQUAL(target, "test string 2");
}

BOOST_AUTO_TEST_CASE(test_get_random_element_empty)
{
	std::vector<std::string> v;

	fake_rng->value = 0;
	std::string target = Util::get_random_element(v, fake_rng);
	BOOST_REQUIRE_EQUAL(target, "");
}

BOOST_AUTO_TEST_SUITE_END()
