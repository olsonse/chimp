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
 * Test file for the Or class.
 * */
#define BOOST_TEST_MODULE  Or


#include <chimp/default_data.h>
#include <chimp/interaction/filter/EqIO.h>
#include <chimp/interaction/filter/Or.h>

#include <boost/test/unit_test.hpp>

#include <sstream>

BOOST_AUTO_TEST_SUITE( Or_tests ); // {

  BOOST_AUTO_TEST_CASE( input_filter ) {
    using chimp::interaction::filter::EqIO;
    using chimp::interaction::filter::Or;
    using boost::shared_ptr;
    Or f( shared_ptr<EqIO>(new EqIO(EqIO::IN,  "e^-", "Hg")),
          shared_ptr<EqIO>(new EqIO(EqIO::OUT, "e^-", "Kr")) );

    namespace xml = xylose::xml;
    xml::Doc xmlDb( chimp::default_data::particledb() );

    typedef xml::Context::set set;
    xml::Context::list xl = xmlDb.eval("//Interaction");
    set xset(xl.begin(), xl.end());

    set ans = f.filter(xset);

    const char * filter_ans = 
      "e^- + Kr  -->  e^- + Kr\n"
      "e^- + Hg  -->  e^- + Hg\n"
      "e^- + Hg  -->  e^- + Hg(6-3P0)\n"
      "e^- + Hg  -->  e^- + Hg(6-3P1)\n"
      "e^- + Hg  -->  e^- + Hg(6-3P2)\n"
      "e^- + Hg  -->  e^- + Hg(7-3S1)\n"
      "e^- + Hg  -->  2 e^- + Hg^+\n";
     
    std::ostringstream af;
    for ( set::iterator i = ans.begin(); i != ans.end(); ++i ) {
      af << i->query<std::string>("Eq") << '\n';
    }

    BOOST_CHECK_EQUAL( af.str(), filter_ans );
  }

BOOST_AUTO_TEST_SUITE_END(); // }
