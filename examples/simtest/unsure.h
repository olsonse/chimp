

  const int N_part = 10;


using olson_tools::IteratorRange;
using olson_tools::nsort::NSort;
namespace map = olson_tools::nsort::map;

  /* ***** BEGIN MAKE PARTICLES AND CELL ***** */
  Particle::list particles;
  initPVector(particles, N_part, db.getProps().size());

  typedef cell_info<Particle::list::iterator> cell_t;
  cell_t cell(db.getProps().size());

  /* initialize single-species velocity data */
  cell.data[db.findParticleIndx("87Rb")] = cell_t::data_t(0, stddev_v_rel(100*uK, 0.5*db["87Rb"].mass::value));
  cell.data[db.findParticleIndx("Ar"  )] = cell_t::data_t(0, stddev_v_rel(100*uK, 0.5*db["Ar"  ].mass::value));
  cell.data[db.findParticleIndx("e^-" )] = cell_t::data_t(0, stddev_v_rel(100*uK, 0.5*db["e^-" ].mass::value));
  cell.data[db.findParticleIndx("Hg"  )] = cell_t::data_t(0, stddev_v_rel(100*uK, 0.5*db["Hg"  ].mass::value));
  cell.data[db.findParticleIndx("Hg^+")] = cell_t::data_t(0, stddev_v_rel(100*uK, 0.5*db["Hg^+"].mass::value));


  /* initialize cross-species data */
  using chimp::interaction::Set;
  typedef cell_t::InteractionDataTable::iterator idIter;
  typedef DB::InteractionTable::const_iterator CIter;
  
  CIter di = db.getInteractions().begin();
  for ( idIter ii  = cell.interaction_info.begin();
               ii != cell.interaction_info.end(); ++ii, ++di ) {
      double stddev_v = sqrt(  cell.data[di->lhs.A].v2
                             + cell.data[di->lhs.B].v2
                        );
      /* loop over all possible outputs and obtain the aggregate max. */
      ii->max_sigma_v_rel = di->find_max_sigma_v_rel_from_stddev_v(stddev_v);
  }



  /* add particles and sort by type */
  cell.particles = IteratorRange<Particle::list::iterator>(particles.begin(), particles.end());
  cell.sort_types(db.getProps().size());
  std::cout << "\nsorted by nsort(type):\n";
  std::copy(cell.particles.begin(), cell.particles.end(), std::ostream_iterator<Particle>(std::cout, "\n"));
  std::cout << std::endl;


  std::cout << "\tall particles of type(2):\n";
  std::copy(cell.types[2].begin(), cell.types[2].end(), std::ostream_iterator<Particle>(std::cout, "\n"));
  std::cout << std::endl;


  /* ***** END MAKE PARTICLES AND CELL ***** */