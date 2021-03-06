/*==============================================================================
 * Public Domain Contributions 2009 United States Government                   *
 * as represented by the U.S. Air Force Research Laboratory.                   *
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
 * Declaration of interaction::model::InElastic class.
 */

#ifndef chimp_interaction_model_InElastic_h
#define chimp_interaction_model_InElastic_h

#include <chimp/property/charge.h>
#include <chimp/interaction/Equation.h>
#include <chimp/interaction/ReducedMass.h>
#include <chimp/interaction/model/Base.h>
#include <chimp/interaction/model/InElastic_2X2.h>
#include <chimp/interaction/model/InElastic_2X3.h>
#include <chimp/interaction/model/detail/inelastic_helpers.h>

#include <xylose/logger.h>

#include <string>
#include <stdexcept>

namespace chimp {
  namespace interaction {
    namespace model {

      /** Implementation of an <b>in</b>elastic interaction model. */
      template < typename options >
      struct InElastic : Base<options> {
        /* TYPEDEFS */
        typedef Base<options> super;
        typedef typename options::Particle Particle;


        /* STATIC STORAGE */
        static const std::string label;


        /* MEMBER STORAGE */
        /** Reduced mass related ratios for INPUT particles (reactants). */
        ReducedMass mu;

        /** Reduced charge related ratios for INPUT particles (reactants). */
        ReducedMass muQ;

        /** Index of source particles for each of the (two) reactants. */
        std::vector< detail::ParticleFactory > factories;

        /** A list of lists of expressions for each output species. */
        std::vector<
          runtime::physical::calc::Driver::ExpressionVector
        > expressions;

        /** A constant pointer to the database. */
        const RuntimeDB<options> * db_ptr;

        /** Boolean to indicate that the center of mass should be calculated and
         * stashed for use in 'ops' expressions. */
        bool force_cm_calc;

        /** Boolean to indicate that the center of charge should be calculated and
         * stashed for use in 'ops' expressions. */
        bool force_cq_calc;


        /* MEMBER FUNCTIONS */
        /** Default constructor sets bogus values--mostly useful for loading
         * with InElastic::load. */
        InElastic() : db_ptr(NULL) { }

        /** Constructor to set up factories and expressions. */
        InElastic( const xml::Context & x,
                   const interaction::Equation<options> & eq,
                   const RuntimeDB<options> & db )
          : mu( eq.reducedMass ),
            muQ( db[eq.A.species].chimp::property::charge::value,
                 db[eq.B.species].chimp::property::charge::value ),
            db_ptr(&db) {
          detail::setFactories( factories, expressions, x, eq, db );
          force_cm_calc = detail::hasToken( "CM()", expressions );
          force_cq_calc = detail::hasToken( "CQ()", expressions );
        }

        /** Virtual NO-OP destructor. */
        virtual ~InElastic() { }

        /** Obtain the label of the model. */
        virtual std::string getLabel() const {
          return label;
        }

        /** load a new instance of the Interaction. */
        virtual InElastic * new_load( const xml::Context & x,
                                      const interaction::Equation<options> & eq,
                                      const RuntimeDB<options> & db ) const {

          double dE = 0.0;
          if ( ! detail::loadKineticEnergyChange( x, dE ) )
            /* if sigma( E < e0 ) = 0 for e0 > 0 && data does not specify:
             *   This indicates an interaction that requires binding energy
             *   that must be overcome for the interaction to take place.
             *   Such an interaction requires the binding energy to be
             *   overcome by the kinetic energy of the incident particles.
             */
            dE = -eq.cs->getThresholdEnergy();

          // TODO:  When chimp reactants are stored in a list someday, then we
          //        will need to count the number of reactants as well.

          const unsigned int n_products = eq.numberProducts();
          const bool has_expressions = hasExpressions( eq.products );
          switch ( n_products ) {
            case 2u : {
              if ( dE == 0.0 ) {
                if ( has_expressions )
                  return new InElastic_2X2<options,false,true>( x, eq, db );
                else
                  return new InElastic_2X2<options,false,false>( x, eq, db );
              } else {
                /* dE comes to this point in SI units.
                 * dE/mu _MUST_ be in the same units as velocity as passed
                 * into model::interact(...).  For now, everything in chimp is
                 * done in SI units.  At some time in the future, it may
                 * become desirable to use energy instead of velocity.
                 */
                if ( has_expressions )
                  return new InElastic_2X2<options,true,true>( x, eq, db, dE );
                else
                  return new InElastic_2X2<options,true,false>( x, eq, db, dE );
              }
            }

            case 3u : {
              if ( dE == 0.0 ) {
                if ( has_expressions )
                  return new InElastic_2X3<options,false,true>( x, eq, db );
                else
                  return new InElastic_2X3<options,false,false>( x, eq, db );
              } else {
                /* dE comes to this point in SI units.
                 * dE/mu _MUST_ be in the same units as velocity as passed
                 * into model::interact(...).  For now, everything in chimp is
                 * done in SI units.  At some time in the future, it may
                 * become desirable to use energy instead of velocity.
                 */
                if ( has_expressions )
                  return new InElastic_2X3<options,true,true>( x, eq, db, dE );
                else
                  return new InElastic_2X3<options,true,false>( x, eq, db, dE );
              }
            }

            default :
              break;
          }/* switch */

          std::ostringstream ostr;
          eq.print(
            ostr << "InElastic (2X" << n_products << ") "
                    "collision not yet support: ",
            db
          );
          xylose::logger::log_severe( ostr.str().c_str() );
          return new InElastic;
        }
      };

      template < typename options >
      const std::string InElastic<options>::label = "inelastic";

    } /* namespace chimp::interaction::model */
  } /* namespace chimp::interaction */
} /* namespace chimp */

#endif // chimp_interaction_model_InElastic_h
