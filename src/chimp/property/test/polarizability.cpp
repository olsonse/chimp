/*==============================================================================
 * Public Domain Contributions 2009 United States Government                   *
 * as represented by the U.S. Air Force Research Laboratory.                   *
 * Copyright (C) 2006, 2008 Spencer E. Olson                                   *
 *                                                                             *
 * This file is part of CHIMP                                                  *
 *                                                                             *
 * This program is free software: you can redistribute it and/or modify it     *
 * under the terms of the GNU Lesser General Public License as published by    *
 * the Free Software Foundation, either version 3 of the License, or (at your  *
 * option) any later version.                                                  *
 *                                                                             *
 * This program is distributed in the hope that it will be useful, but WITHOUT *
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or       *
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public        *
 * License for more details.                                                   *
 *                                                                             *
 * You should have received a copy of the GNU Lesser General Public License    *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.       *
 *                                                                             *
 -----------------------------------------------------------------------------*/


/** \file
 * Test file for the property::polarizability class.
 * */
#define BOOST_TEST_MODULE  polarizability

#include <chimp/property/polarizability.h>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( property_polarizability ); // {

  BOOST_AUTO_TEST_CASE( intantiation ) {
    using chimp::property::polarizability;
    {
      polarizability p;
      BOOST_CHECK_EQUAL(p.value,0);
      BOOST_CHECK_EQUAL(p.polarizability::value,0);
    }

    {
      polarizability p(10);
      BOOST_CHECK_EQUAL(p.value,10);
      BOOST_CHECK_EQUAL(p.polarizability::value,10);
    }
  }

BOOST_AUTO_TEST_SUITE_END(); // }
