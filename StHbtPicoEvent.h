/**
 * Description:
 * StHbtPicoEvent stores collections of particles for the further processing
 */

#ifndef StHbtPicoEvent_h
#define StHbtPicoEvent_h

/// StHbtMaker headers
#include "StHbtParticleCollection.h"

//_________________
class StHbtPicoEvent {
  
 public:
  /// Default constructor
  StHbtPicoEvent();
  /// Copy constructor
  StHbtPicoEvent(const StHbtPicoEvent& copy);
  /// Copy constructor
  StHbtPicoEvent& operator=(const StHbtPicoEvent& copy);
  /// Default destructor
  ~StHbtPicoEvent();

  /**
   * Getters
   **/
  StHbtParticleCollection* firstParticleCollection()   { return mFirstParticleCollection; }
  StHbtParticleCollection* secondParticleCollection()  { return mSecondParticleCollection; }
  StHbtParticleCollection* thirdParticleCollection()   { return mThirdParticleCollection; }

 private:
  /// Collections
  StHbtParticleCollection* mFirstParticleCollection;
  StHbtParticleCollection* mSecondParticleCollection;
  StHbtParticleCollection* mThirdParticleCollection;
};

#endif // #define StHbtPicoEvent_h
