/**
 * Description: A pure virtual base class for the hidden (Monte Carlo) data.
 *
 * Hidden info stores additional information, which is not in a standard track.
 */

#ifndef StHbtHiddenInfo_h
#define StHbtHiddenInfo_h

/// StHbtMaker headers
#include "StHbtTypes.h"

//_________________
class StHbtHiddenInfo {

 public:
  /// Default constructor
  StHbtHiddenInfo()            { /* no-op */ }
  /// Default destructor
  virtual ~StHbtHiddenInfo()   { /* no-op */ }

  /// !!! MANDATORY !!!
  /// --- Copy the hidden info from StHbtTrack to StHbtParticle
  virtual StHbtHiddenInfo* getParticleHiddenInfo() const = 0;
  virtual StHbtHiddenInfo* clone() const;
};

//_________________
inline StHbtHiddenInfo* StHbtHiddenInfo::clone() const {
  return getParticleHiddenInfo();
}

#endif // #define StHbtHiddenInfo_h
