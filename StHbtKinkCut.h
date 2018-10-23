/**
 * Description: StHbtKinkCut - the pure virtual base class for the kink cut
 *
 * All kink cuts must inherit from this one
 */

#ifndef StHbtKinkCut_h
#define StHbtKinkCut_h

/// StHbtMaker headers
#include "StHbtTypes.h"
#include "StHbtKink.h"
#include "StHbtParticleCut.h"

//_________________
class StHbtKinkCut : public StHbtParticleCut {

 public:
  /// Default constructor
  StHbtKinkCut()                          { /* no-op */ }
  /// Copy constructor
  StHbtKinkCut(const StHbtKinkCut& copy);
  /// Assignment operator
  StHbtKinkCut& operator=(const StHbtKinkCut& copy);
  /// Default destructor
  virtual ~StHbtKinkCut()                 { /* no-op */ }

  /// Returns true is cut has been passed, and false if not
  virtual bool pass(const StHbtKink* ) = 0;

  virtual StHbtParticleType type()        { return hbtKink; }
  virtual StHbtKinkCut* clone()           { return nullptr; }

#ifdef __ROOT__
  ClassDef(StHbtKinkCut, 0)
#endif
};

inline StHbtKinkCut::StHbtKinkCut(const StHbtKinkCut& c) : StHbtParticleCut(c) { /* no-op */ }
inline StHbtKinkCut& StHbtKinkCut::operator=(const StHbtKinkCut& c) {
  if( this != &c ) {
    StHbtParticleCut::operator=(c);
  }
  return *this;
}

#endif // #define StHbtKinkCut_h
