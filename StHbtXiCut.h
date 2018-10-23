/**
 * Description: The pure virtual base class for the Xi cut
 *
 * All Xi cuts must inherit from this one.
 */

#ifndef StHbtXiCut_h
#define StHbtXiCut_h

/// StHbtMaker headers
#include "StHbtTypes.h"
#include "StHbtXi.h"
#include "StHbtParticleCut.h"

//_________________
class StHbtXiCut : public StHbtParticleCut {

 public:
  /// Default constructor
  StHbtXiCut();
  /// Copy constructor
  StHbtXiCut(const StHbtXiCut& copy);
  /// Assignment operator
  StHbtXiCut& operator=(const StHbtXiCut& copy);
  /// Default destructor
  virtual ~StHbtXiCut()                    { /* no-op */ }

  /// Returns true if cut has been passed and false if not
  virtual bool pass(const StHbtXi* ) = 0;
  virtual StHbtParticleType type()         { return hbtXi; }
  virtual StHbtXiCut* clone()              { return nullptr; }

#ifdef __ROOT__
  ClassDef(StHbtXiCut, 0)
#endif
};

inline StHbtXiCut::StHbtXiCut() : StHbtParticleCut() { /* no-op */ }
inline StHbtXiCut::StHbtXiCut(const StHbtXiCut& c) : StHbtParticleCut(c) { /* no-op */ }
inline StHbtXiCut& StHbtXiCut::operator=(const StHbtXiCut& c) {
  if (this != &c ) {
    StHbtParticleCut::operator=(c);
  }
  return *this;
}

#endif // #define StHbtXiCut_h
