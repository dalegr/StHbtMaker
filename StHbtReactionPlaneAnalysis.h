/**
 * Description:
 * Analysis with respect to the z position of the primary vertex and event 
 * total multiplicity and uses only events in certain reaction plane angle bin
 */

#ifndef StHbtReactionPlaneAnalysis_h
#define StHbtReactionPlaneAnalysis_h

/// StHbtMaker headers
#include "StHbtAnalysis.h"

/// ROOT headers
#include "TList.h"

/// Forward declaration
class StHbtPicoEventCollectionVectorHideAway;

//_________________
class StHbtReactionPlaneAnalysis : public StHbtAnalysis {

 public:
  /// Default constructor
  StHbtReactionPlaneAnalysis( unsigned int binsVertex=10, double minVertex=-100., double maxVertex=+100.,
			      unsigned int binsMult=10, double minMult=-1.e9, double maxMult=+1.e9,
			      unsigned short binsRP=10 );
  /// Copy constructor
  StHbtReactionPlaneAnalysis(const StHbtReactionPlaneAnalysis& copy);
  /// Assignment operator
  StHbtReactionPlaneAnalysis& operator=(const StHbtReactionPlaneAnalysis& copy);
  /// Destructor
  virtual ~StHbtReactionPlaneAnalysis();

  virtual void processEvent(const StHbtEvent* thisEvent);
  /// returns reports of all cuts applied and correlation functions being done
  virtual StHbtString report();
  virtual unsigned int overflowVertexZ() const  { return mOverFlowVertexZ; }
  virtual unsigned int underflowVertexZ() const { return mUnderFlowVertexZ; }
  virtual unsigned int overflowMult() const     { return mOverFlowMult; }
  virtual unsigned int underflowMult() const    { return mUnderFlowMult; }
  double getCurrentReactionPlane()  const       { return mCurrentRP; }

  /// Return a TList of analysis settings.
  ///
  /// The TList comprises TObjStrings describing the settings provided by the
  /// StHbtAnalysis::ListSettings class followed by all event-mixing
  /// binning parameters.
  virtual TList *listSettings();
  /// Obtain number of objects to be written as an output
  virtual TList *getOutputList();

protected:

  /// min/max z-vertex position allowed to be processed
  double mVertexZ[2];
  /// Number of VERTEX mixing bins in z-vertex in EventMixing Buffer
  unsigned int mVertexZBins;
  /// Number of events encountered which had too large z-vertex
  unsigned int mOverFlowVertexZ;
  /// Number of events encountered which had too small z-vertex
  unsigned int mUnderFlowVertexZ;

  /// min/max multiplicity allowed for event to be processed
  double mMult[2];
  /// Number of MULTIPLICITY mixing bins in z-vertex in EventMixing Buffer
  unsigned int mMultBins;
  /// Number of events encountered which had too large multiplicity
  unsigned int mOverFlowMult;
  /// Number of events encountered which had too small multiplicity
  unsigned int mUnderFlowMult;

  /// Number of reaction plane angle orientation bins
  unsigned short mRPBins;
  /// Reaction plane angle of the current event
  double mCurrentRP;
  
#ifdef __ROOT__
  ClassDef(StHbtReactionPlaneAnalysis, 0)
#endif
};

#endif // #define StHbtReactionPlaneAnalysis_h
