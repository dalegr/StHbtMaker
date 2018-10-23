/**
 * Description: The pure virtual base class for the pair cut
 *
 * All pair cuts must inherit from this one
 */

#ifndef StHbtPairCut_h
#define StHbtPairCut_h

/// C++ headers
#include <string>

/// Forward declaration
class StHbtBaseAnalysis;

/// StHbtMaker headers
#include "StHbtString.h"
#include "StHbtEvent.h"
#include "StHbtPair.h"
#include "StHbtCutMonitorHandler.h"

/// ROOT headers
#include "TList.h"
#include "TObjString.h"

//_________________
class StHbtPairCut : public StHbtCutMonitorHandler {

 public:
  /// Default constructor
  StHbtPairCut();
  /// Copy constructor
  StHbtPairCut(const StHbtPairCut& c);
  /// Assignment operator
  StHbtPairCut& operator=(const StHbtPairCut& c);
  /// Default destructor
  virtual ~StHbtPairCut()                    { /* no-op */ }

  /// Returns true in pair passed the cut and false if not
  virtual bool pass(const StHbtPair* pair) = 0;

  /// User-written method to return string describing cuts
  virtual StHbtString report() = 0;
  /// Returns a TList with settings
  virtual TList *listSettings() = 0;
  
  virtual void eventBegin(const StHbtEvent*) { /* no-op */ }
  virtual void eventEnd(const StHbtEvent*)   { /* no-op */ }
  virtual StHbtPairCut* clone()              { return nullptr; }

  /// The following allows "back-pointing" from the CorrFctn
  /// to the "parent" Analysis
  friend class StHbtBaseAnalysis;
  StHbtBaseAnalysis* hbtAnalysis()           { return mBaseAnalysis; }
  void setAnalysis(StHbtBaseAnalysis* ana)   { mBaseAnalysis = ana; }

 protected:
  StHbtBaseAnalysis* mBaseAnalysis;

#ifdef __ROOT__
  ClassDef(StHbtPairCut, 0)
#endif
};

inline StHbtPairCut::StHbtPairCut() : StHbtCutMonitorHandler(), mBaseAnalysis(nullptr) { /* empty */ }
inline StHbtPairCut::StHbtPairCut(const StHbtPairCut& c) : StHbtCutMonitorHandler(), mBaseAnalysis(nullptr)
{ /* empty */ }
inline StHbtPairCut& StHbtPairCut::operator=(const StHbtPairCut& c)
{ if ( this != &c ) { mBaseAnalysis = c.mBaseAnalysis; } return *this; }

#endif // #define StHbtPairCut_h
