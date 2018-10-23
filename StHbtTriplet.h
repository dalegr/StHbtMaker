#ifndef StHbtTriplet_h
#define StHbtTriplet_h

/// C++ headers
#include <utility>

/// StHbtMaker headers
#include "StHbtParticle.h"
#include "StHbtTypes.h"

/// ROOT headers
#include "TLorentzVector.h"

//_________________
class StHbtTriplet {
  
 public:
  /// Default constructor
  StHbtTriplet();
  /// Constructor with three particles
  StHbtTriplet(StHbtParticle*, StHbtParticle*, StHbtParticle*);
  /// Copy constructor
  StHbtTriplet(const StHbtTriplet&);
  // Default destructor
  ~StHbtTriplet();

  // track Gets:
  StHbtParticle* track1() const                 { return mTrack1; }
  StHbtParticle* track2() const                 { return mTrack2; }
  StHbtParticle* track3() const                 { return mTrack3; }
  // track Sets:
  void setTrack1(const StHbtParticle* trkPtr)   { mTrack1 = (StHbtParticle*)trkPtr; }
  void setTrack2(const StHbtParticle* trkPtr)   { mTrack2=(StHbtParticle*)trkPtr; }
  void setTrack3(const StHbtParticle* trkPtr)   { mTrack3=(StHbtParticle*)trkPtr; }

  TLorentzVector fourMomentum() const;
  double qInv() const;
  double qInv12() const;
  double qInv23() const;
  double qInv31() const;
  double kT()   const;
  double mInv() const;

  double quality() const;
  
  // the following two methods calculate the "nominal" separation of the tracks 
  // at the inner field cage (EntranceSeparation) and when they exit the TPC,
  // which may be at the outer field cage, or at the endcaps.
  // "nominal" means that the tracks are assumed to start at (0,0,0).  Making this
  // assumption is important for the Event Mixing-- it is not a mistake. - MALisa
  double nominalTpcExitSeparation() const;
  double nominalTpcEntranceSeparation() const;
  double nominalTpcAverageSeparation() const;

 private:
  
  StHbtParticle* mTrack1;
  StHbtParticle* mTrack2;
  StHbtParticle* mTrack3;

};

#endif // StHbtTriplet_h
