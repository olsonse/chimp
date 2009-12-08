/** \file
 * The main documentation page for doxygen. 
 */

/** \mainpage CHIMP API Documentation

<h2>Chemical Interactions and Materials Properties Library</h2>


<h3>Introduction</h3>
Currently, it is very common for different simulations to use slightly, if not
drastically, different physical data for the same materials.  This creates both
confusion as to how to compare the results of different simulations, but also
questions the validity of any one simulation.  There is a current need in the
computational physics community for a common repository of physical data and a
means to deliver that data to simulation tools.  This work represents a
collaborative effort to develop a database and library to provide physical data
and associated model calculations in a consistent, simple yet flexible manner.

The scope of the data to be housed within the database is intended to be
necessarily wide, so as to create some uniformity of simulation results based on
the same data.  All data to be added to any released version of the library will
be required to be both publicly accessible and well documented as to its origin.
The success of this work will rely on heavily on all collaborators contributing
data in the correct format and helping thoroughly documenting this data. 

This manual constitutes the technical reference or application programming
interface (API) documentation for CHIMP.  This manual is automatically generated
using the doxygen code documentation tool.  Currently, we support HTML and
\f$\LaTeX\f$ output generation.  Please follow the appropriate links to
documentation for each function, class, and namespace of the API.


<h3>Additional Material</h3>
  Please refer to the following material for current status, future direction,
  and otherwise typical package information:
  - \subpage discussions
  - \subpage platforms
  - \subpage license
  - \subpage readme
  - \subpage install
  - \subpage changelog
  - \subpage authors
  .
*/



//-----------------------------------------------------------
/** \page license Licence
    \verbinclude COPYING
*/



//-----------------------------------------------------------
/** \page readme README
    \verbinclude README
*/



//-----------------------------------------------------------
/** \page install INSTALL
    \verbinclude INSTALL
*/



//-----------------------------------------------------------
/** \page changelog ChangeLog
    \verbinclude ChangeLog
*/



//-----------------------------------------------------------
/** \page authors AUTHORS
    \verbinclude AUTHORS
*/


//-----------------------------------------------------------
/** \page discussions Direction and Discussions

If appropriate public information exists (e.g. in journals or databases such as
from NIST), the level of fidelity will also be documented.  
A recent discussion among AFRL/DOE collaborators brought out the following
idea for documenting fidelity of the data that we will be distributing.
  - Baked from thin air
  - Published
  - Published works cited
  - Experimental data claimed to have compared favorably
  - etc.
  .
*/


//-----------------------------------------------------------
/** \page platforms Supported Platforms
  <table border=0>
    <tr><th>Platform</th><th>Compiler</th><th>Version</th><th>Status</th></tr>
    <tr><td>Linux</td><td>GCC</td><td></td><td></td></tr>
    <tr><td></td>     <td></td>   <td>4.1.2 (RedHat/Centos 5.3)</td><td>Supported</td></tr>
    <tr><td></td>     <td></td>   <td>4.4.1 (Ubuntu 9.10)</td><td>Supported</td></tr>
    <tr><td>Cygwin</td><td>GCC</td><td></td><td></td></tr>
    <tr><td></td>     <td></td>   <td>3.5</td><td>Supported</td></tr>
    <tr><td></td>     <td></td>   <td>4.x</td><td>Not Supported</td></tr>
  </table>
*/
