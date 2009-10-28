/** \file Simple test of chimp::property mechanics. */

#include <chimp/RuntimeDB.h>
#include <iostream>

int main() {
  const char * Pname = "Ar";

  typedef chimp::RuntimeDB<> DB;
  DB db;
  db.addParticleType(Pname);

  std::cout << "Accessed with string index, each property individually:\n";
  std::cout << "\tp.name:  "   << db[Pname].name::value << std::endl;
  std::cout << "\tp.size:  "   << db[Pname].size::value << std::endl;
  std::cout << "\tp.mass:  "   << db[Pname].mass::value << std::endl;
  std::cout << "\tp.charge:  " << db[Pname].charge::value << std::endl;

  int i = db.findParticleIndx(Pname);
  std::cout << "Accessed with integer index, each property individually:\n";
  std::cout << "\tp.name:  "   << db[i].name::value << std::endl;
  std::cout << "\tp.size:  "   << db[i].size::value << std::endl;
  std::cout << "\tp.mass:  "   << db[i].mass::value << std::endl;
  std::cout << "\tp.charge:  " << db[i].charge::value << std::endl;

  std::cout << "Accessed with const reference:\n";
  const DB::Properties & p = db[Pname];
  std::cout << "Printing all properties by using stream insertion:\n";
  std::cout << "\t{" << p << '}' << std::endl;

  return 0;
}