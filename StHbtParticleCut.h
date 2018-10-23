/**
 * Description: The pure virtual base class for the particle cut.
 *
 * All particle cuts must inherit from this one.
 */

#ifndef StHbtParticleCut_h
#define StHbtParticleCut_h

/// C++ headers
#include <iostream>

/// StHbtMaker headers
#include "StHbtTypes.h"
#include "StHbtCutMonitorHandler.h"

/// ROOT headers
#include "TList.h"
#include "TObjString.h"
#include "TString.h"

/// Forward declaration
class StHbtBaseAnalysis;

//_________________
class StHbtParticleCut : public StHbtCutMonitorHandler {

 public:
  /// Default constructor
  StHbtParticleCut();
  /// Copy constructor
  StHbtParticleCut(const StHbtParticleCut& copy);
  /// Assignment operator
  StHbtParticleCut& operator=(const StHbtParticleCut& c);
  /// Default destructor
  virtual ~StHbtParticleCut()                  { /* no-op */ }

  /// User-written method to return string describing cuts
  virtual StHbtString report() = 0;
  /// User-written list of settings which is stored in the result file
  virtual TList *listSettings();

  /// Mass of the particle being selected
  double mass()                                { return mMass; }
  virtual void setMass(const double& mass)     { mMass = mass; }

  virtual void eventBegin(const StHbtEvent*)   { /* no-op */ }
  virtual void eventEnd(const StHbtEvent*)     { /* no-op */ }
  virtual StHbtParticleCut* clone()            { return nullptr; }

  virtual StHbtParticleType type() = 0;

  /// The following allows "back-pointing" from the CorrFctn
  /// to the "parent" Analysis
  friend class StHbtBaseAnalysis;
  StHbtBaseAnalysis* hbtAnalysis()             { return mBaseAnalysis; }
  void setAnalysis(StHbtBaseAnalysis* ana)     { mBaseAnalysis = ana; }

 protected:
  double mMass;
  StHbtBaseAnalysis* mBaseAnalysis;

#ifdef __ROOT__
  ClassDef(StHbtParticleCut, 0)
#endif
};

inline StHbtParticleCut::StHbtParticleCut() : StHbtCutMonitorHandler(), mMass(0), mBaseAnalysis(nullptr)
{ /* empty */ }
inline StHbtParticleCut::StHbtParticleCut(const StHbtParticleCut& c) :
			StHbtCutMonitorHandler(c), mMass(0), mBaseAnalysis(c.mBaseAnalysis) { /* empty */ }
inline StHbtParticleCut& StHbtParticleCut::operator=(const StHbtParticleCut& c) {
  if( this != &c ) {
    StHbtCutMonitorHandler::operator=(c); mBaseAnalysis = c.mBaseAnalysis; mMass = c.mMass;
  }
  return *this;
}
inline TList *StHbtParticleCut::listSettings() {
  TList *listOfSettings = new TList();
  listOfSettings->Add( new TObjString( Form("StHbtParticleCut::mass = %5.3f",mMass) ) );
  return listOfSettings;
}

#endif // #define StHbtParticleCut_h
