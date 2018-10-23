/**
 * StHbtLikeSignCorrFctn - the pure virtual base class for the like sign
 * correlation function. All like sign correlation functions  must inherit
 * from this one
 */

#ifndef StHbtLikeSignCorrFctn_h
#define StHbtLikeSignCorrFctn_h

/// Forward declaration
class StHbtPair;

/// StHbtMaker headers
#include "StHbtCorrFctn.h"

/// ROOT headers
#include "TList.h"

//_________________
class StHbtLikeSignCorrFctn : public StHbtCorrFctn {

 public:
  /// Default constructor
  StHbtLikeSignCorrFctn()                                { /* no-op */ }
  /// Copy constructor
  StHbtLikeSignCorrFctn(const StHbtLikeSignCorrFctn& copy);
  /// Assignment operator
  StHbtLikeSignCorrFctn& operator=(const StHbtLikeSignCorrFctn& copy);
  /// Default destructor
  virtual ~StHbtLikeSignCorrFctn()                       { /* no-op */ }

  /// Add pair positive and negative pairs
  virtual void addLikeSignPositivePair(const StHbtPair*) = 0;
  virtual void addLikeSignNegativePair(const StHbtPair*) = 0;

  virtual StHbtLikeSignCorrFctn* clone()                 { return 0; }

  virtual TList* getOutputList() = 0;

  /// The following allows "back-pointing" from the CorrFctn
  /// to the "parent" Analysis
  friend class StHbtLikeSignAnalysis;
};

inline StHbtLikeSignCorrFctn::StHbtLikeSignCorrFctn(const StHbtLikeSignCorrFctn& c) : StHbtCorrFctn()
{ mBaseAnalysis = 0; }
inline StHbtLikeSignCorrFctn& StHbtLikeSignCorrFctn::operator=(const StHbtLikeSignCorrFctn& c)
{ if ( this != &c ) { StHbtCorrFctn::operator=(c); } return *this; }

#endif // #define StHbtLikeSignCorrFctn_h
