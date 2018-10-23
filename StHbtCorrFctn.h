/**
 * Description: The pure-virtual base class for correlation functions
 *
 * All correlation function classes must inherit from this one.
 * This class has a optional pointers to the "parent" analysis and
 * a pair cut
 */

#ifndef StHbtCorrFctn_h
#define StHbtCorrFctn_h

/// C++ headers
#include <iostream>

/// StHbtMaker headers
#include "StHbtBaseAnalysis.h"
#include "StHbtPairCut.h"
#include "StHbtEvent.h"
#include "StHbtPair.h"
#include "StHbtTriplet.h"

/// ROOT headers
#include "TList.h"

//_________________
class StHbtCorrFctn {
  
 public:
  /// Default constuctor
  StHbtCorrFctn();
  /// Copy constructor
  StHbtCorrFctn(const StHbtCorrFctn& copy);
  /// Assignment operator
  StHbtCorrFctn& operator=(const StHbtCorrFctn& copy);
  /// Default destructor
  virtual ~StHbtCorrFctn() {/* no-op */}

  /// Report
  virtual StHbtString report() = 0;

  /// Add real and mixed pair
  virtual void addRealPair(const StHbtPair*);
  virtual void addMixedPair(const StHbtPair*);

  /// Add real and mixed triplet
  virtual void addRealTriplet(const StHbtTriplet*);
  virtual void addMixedTriplet(const StHbtTriplet*);

  /// Not Implemented - Add pair with optional
  virtual void addFirstParticle(StHbtParticle *particle, bool mixing);
  virtual void addSecondParticle(StHbtParticle *particle);
  
  /// Event start
  virtual void eventBegin(const StHbtEvent*)      { /* no-op */ }
  virtual void eventEnd(const StHbtEvent*)        { /* no-op */ }
  virtual void finish() = 0;

  virtual TList* getOutputList() = 0;
  
  virtual StHbtCorrFctn* clone()                  { return nullptr; }
  virtual StHbtPairCut* getPairCut()              { return mPairCut; }

  // The following allows "back-pointing" from the CorrFctn to the "parent" Analysis
  friend class StHbtBaseAnalysis;
  StHbtBaseAnalysis* hbtAnalysis()                { return mBaseAnalysis; }
  void setAnalysis(StHbtBaseAnalysis* ana)        { mBaseAnalysis = ana; }
  void setPairSelectionCut(StHbtPairCut *cut)     { mPairCut = cut; }

 protected:
  StHbtBaseAnalysis* mBaseAnalysis;
  StHbtPairCut* mPairCut;

 private:

#ifdef __ROOT__
  ClassDef(StHbtCorrFctn, 0)
#endif  
};



#endif
