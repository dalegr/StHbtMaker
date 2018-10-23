#ifndef StHbtLikeSignAnalysis_h
#define StHbtLikeSignAnalysis_h

/// StHbtMaker headers
// Base
#include "StHbtBaseAnalysis.h"
#include "StHbtEventCut.h"
#include "StHbtParticleCut.h"
#include "StHbtPairCut.h"
#include "StHbtLikeSignCorrFctn.h"
// Infrastructure
#include "StHbtTypes.h"
#include "StHbtAnalysis.h"
#include "StHbtCorrFctnCollection.h"

//_________________
class StHbtLikeSignAnalysis : public StHbtAnalysis {

 public: 
  /// Constructor
  StHbtLikeSignAnalysis(unsigned int bins=20, double min=-100., double max=100.);
  /// Copy constructor
  StHbtLikeSignAnalysis(const StHbtLikeSignAnalysis& copy);
  /// Copy constructor
  StHbtLikeSignAnalysis& operator=(const StHbtLikeSignAnalysis& copy);
  /// Default destructor
  virtual ~StHbtLikeSignAnalysis();
  
  virtual void processEvent(const StHbtEvent*);
  virtual StHbtString report();
  virtual unsigned int overflow() { return mOverFlow;}
  virtual unsigned int underflow() { return mUnderFlow;}

 protected:
  /// Min/Max z-vertex position allowed to be processed 
  double mVertexZ[2];
  /// Number of mixing bins in z-vertex in EventMixing Buffer
  unsigned int mVertexBins;
  /// Number of events encountered which had too large z-vertex
  unsigned int mOverFlow;
  /// Number of events encountered which had too small z-vertex
  unsigned int mUnderFlow;

#ifdef __ROOT__
  ClassDef(StHbtLikeSignAnalysis, 0)
#endif
};

#endif // #define StHbtLikeSignAnalysis_h
