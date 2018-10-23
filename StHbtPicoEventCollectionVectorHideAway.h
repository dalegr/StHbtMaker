/**
 * Description:
 * StHbtPicoEventCollectionVectorHideAway: a helper class for
 * managing many mixing buffers with up to three variables used for
 * binning.
 */

#ifndef StHbtPicoEventCollectionVectorHideAway_h
#define StHbtPicoEventCollectionVectorHideAway_h

/// C++ headers
#include <vector>
#include <list>
#include <float.h>
#include <limits.h>
#if !defined(ST_NO_NAMESPACES)
using std::vector;
using std::list;
#endif

/// StHbtMaker headers
#include "StHbtPicoEvent.h"
#include "StHbtPicoEventCollection.h"
#include "StHbtPicoEventCollectionVector.h"

//_________________
class StHbtPicoEventCollectionVectorHideAway {
  
 public:
  /// Constructor
  StHbtPicoEventCollectionVectorHideAway(int bx=1, double lx=-FLT_MAX, double ux=FLT_MAX,
					 int by=1, double ly=-FLT_MAX, double uy=FLT_MAX,
					 int bz=1, double lz=-FLT_MAX, double uz=FLT_MAX);
  /// Copy constructor
  StHbtPicoEventCollectionVectorHideAway(const StHbtPicoEventCollectionVectorHideAway &copy);
  /// Copy constructor
  StHbtPicoEventCollectionVectorHideAway& operator=(const StHbtPicoEventCollectionVectorHideAway& copy);
  /// Default destructor
  ~StHbtPicoEventCollectionVectorHideAway();
  
  StHbtPicoEventCollection* picoEventCollection(int, int, int);
  StHbtPicoEventCollection* picoEventCollection(double x, double y=0, double z=0);

  unsigned int binXNumber(double x) const { return (int)floor( (x - mMinX) / mStepX ); }
  unsigned int binYNumber(double y) const { return (int)floor( (y - mMinY) / mStepY ); }
  unsigned int binZNumber(double z) const { return (int)floor( (z - mMinZ) / mStepZ ); }
  
 private:

  /// Total number of bins
  int mBinsTot;
  /// Number of bins on x, y and z axis
  int mBinsX;
  int mBinsY;
  int mBinsZ;
  /// Minimal values on x, y and z axis
  double mMinX;
  double mMinY;
  double mMinZ;
  /// Maximal values on x, y and z axis
  double mMaxX;
  double mMaxY;
  double mMaxZ;
  /// Steps on x, y and z axis
  double mStepX;
  double mStepY;
  double mStepZ;
  /// Pico event collection
  StHbtPicoEventCollection* mCollection;
  /// Collection vector
  StHbtPicoEventCollectionVector mCollectionVector;
};

#endif // #define StHbtPicoEventCollectionVectorHideAway_h
