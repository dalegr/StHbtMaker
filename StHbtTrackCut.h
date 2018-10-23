/**
 * Description: The pure virtual base class for track cuts. All track cuts must
 * inherit from this one.
 */

#ifndef StHbtTrackCut_h
#define StHbtTrackCut_h

/// StHbtMaker headers
#include "StHbtTypes.h"
#include "StHbtTrack.h"
#include "StHbtParticleCut.h"

//_________________
class StHbtTrackCut : public StHbtParticleCut {

 public:
  /// Default constructor
  StHbtTrackCut();
  /// Copy constructor
  StHbtTrackCut(const StHbtTrackCut& copy);
  /// Assignment operator
  StHbtTrackCut& operator=(const StHbtTrackCut& copy);
  /// Default destructor
  virtual ~StHbtTrackCut()             {/* no-op */}

  /// Returns true if passed the cut and false if not
  virtual bool pass(const StHbtTrack* track) = 0;
  virtual StHbtParticleType type()     { return hbtTrack; }
  virtual StHbtTrackCut* clone()       { return nullptr; }

#ifdef __ROOT__
  ClassDef(StHbtTrackCut, 0)
#endif
};

inline StHbtTrackCut::StHbtTrackCut() : StHbtParticleCut() { /* empty */ }
inline StHbtTrackCut::StHbtTrackCut(const StHbtTrackCut& c) : StHbtParticleCut(c) { /* empty */ }
inline StHbtTrackCut& StHbtTrackCut::operator=(const StHbtTrackCut& c) {
  if (this != &c ) {
    StHbtParticleCut::operator=(c);
  }
  return *this;
}

#endif // #define StHbtTrackCut_h
