/**
 * Description: The pure virtual base class for the V0 cut
 *
 * All V0 cuts must inherit from this one.
 */

#ifndef StHbtV0Cut_h
#define StHbtV0Cut_h

/// StHbtMaker headers
#include "StHbtTypes.h"
#include "StHbtV0.h"
#include "StHbtParticleCut.h"

//_________________
class StHbtV0Cut : public StHbtParticleCut {

 public:
  /// Default constructor
  StHbtV0Cut();
  /// Copy constructor
  StHbtV0Cut(const StHbtV0Cut& copy);
  /// Assignment operator
  StHbtV0Cut& operator=(const StHbtV0Cut& c);
  /// Default destructor
  virtual ~StHbtV0Cut()                {/* no-op */}

  /// Returns true if cut has been passed and false if not
  virtual bool pass(const StHbtV0* ) = 0;

  virtual StHbtParticleType type()     { return hbtV0; }
  virtual StHbtV0Cut* clone()          { return nullptr; }

#ifdef __ROOT__
  ClassDef(StHbtV0Cut, 0)
#endif
};

inline StHbtV0Cut::StHbtV0Cut() : StHbtParticleCut() { /* no-op */ }
inline StHbtV0Cut::StHbtV0Cut(const StHbtV0Cut& c) : StHbtParticleCut(c) { /* no-op */ }
inline StHbtV0Cut& StHbtV0Cut::operator=(const StHbtV0Cut& c) {
  if( this != &c ) {
    StHbtParticleCut::operator=(c);
  }
  return *this;
}

#endif // #define StHbtV0Cut_h
