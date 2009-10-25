/** \file
 * Declaration of filter::Add template meta function. 
 */

#ifndef chimp_interaction_filter_And_h
#define chimp_interaction_filter_And_h

#include <chimp/interaction/filter/Base.h>

#include <boost/shared_ptr.hpp>

#include <algorithm>

namespace chimp {
  namespace interaction {
    namespace filter {

      using boost::shared_ptr;

      /** Filter intersection operation. */
      struct And : filter::Base {
        /* MEMBER STORAGE */
        shared_ptr<filter::Base> l, r;

        /* MEMBER FUNCTIONS */
        /** Constructor */
        And( const shared_ptr<filter::Base> & l,
             const shared_ptr<filter::Base> & r ) : l(l), r(r) { }

        /** Virtual NO-OP destructor. */
        virtual ~And() {}

        /** Virtual filter operation. */
        virtual set filter(const set & in) {
          set lset = l->filter(in);
          set rset = r->filter(in);

          set retval;
          std::set_intersection( lset.begin(), lset.end(),
                                 rset.begin(), rset.end(),
                                 inserter(retval, retval.begin()) );
          return retval;
        }
      };

    }/* namespace particldb::interaction::filter */
  }/* namespace particldb::interaction */
}/* namespace particldb */

#endif // chimp_interaction_filter_And_h
