/**
 * Description: A handler for cut monitors
 *
 * You add cut monitors to the collection which are stored in two separate
 * collections - one which stores characteristics of the entities (tracks,
 * particles, pairs, events) that pass the respective cuts and the other for
 * the ones that fail the cut.
 */

#ifndef StHbtCutMonitorHandler_h
#define StHbtCutMonitorHandler_h

/// StHbtMaker headers
// Base
#include "StHbtCutMonitor.h"
// Infrastructure
#include "StHbtTypes.h"
#include "StHbtEvent.h"
#include "StHbtTrack.h"
#include "StHbtV0.h"
#include "StHbtKink.h"
#include "StHbtXi.h"
#include "StHbtPair.h"
#include "StHbtParticleCollection.h"
#include "StHbtCutMonitorCollection.h"

/// ROOT headers
#include "Rtypes.h"
#include "TList.h"

//_________________
class StHbtCutMonitorHandler {
  
 public:
  /// Default constructor
  StHbtCutMonitorHandler();
  /// Copy constructor
  StHbtCutMonitorHandler(const StHbtCutMonitorHandler& copy);
  /// Assignment operator
  StHbtCutMonitorHandler& operator=(const StHbtCutMonitorHandler& copy);
  /// Destructor
  virtual ~StHbtCutMonitorHandler();
  
  StHbtCutMonitorCollection* passMonitorColl()    { return mPassColl; }
  StHbtCutMonitorCollection* failMonitorColl()    { return mFailColl; }
  StHbtCutMonitor* passMonitor(int n);
  StHbtCutMonitor* failMonitor(int n);
  
  void addCutMonitor(StHbtCutMonitor* cutMoni1, StHbtCutMonitor* cutMoni2); 
  void addCutMonitor(StHbtCutMonitor* cutMoni); 
  void addCutMonitorPass(StHbtCutMonitor* cutMoni); 
  void addCutMonitorFail(StHbtCutMonitor* cutMoni);
  
  void fillCutMonitor(const StHbtEvent* event, bool pass); 
  void fillCutMonitor(const StHbtTrack* track, bool pass); 
  void fillCutMonitor(const StHbtV0* v0, bool pass); 
  void fillCutMonitor(const StHbtKink* kink, bool pass);
  void fillCutMonitor(const StHbtXi* xi, bool pass);
  void fillCutMonitor(const StHbtPair* pair, bool pass);
  void fillCutMonitor(const StHbtParticleCollection* partColl);
  void fillCutMonitor(const StHbtEvent* event, const StHbtParticleCollection* partColl);
  void fillCutMonitor(const StHbtParticleCollection* partColl1, const StHbtParticleCollection* partColl2);
  
  void finish();

  virtual TList *getOutputList();

  virtual void eventBegin(const StHbtEvent* event);
  virtual void eventEnd(const StHbtEvent* event);
  
 private:

  /// Are the collections empty?
  bool mCollectionsEmpty;
  /// Collection of cut monitors for passed entities
  StHbtCutMonitorCollection* mPassColl;
  /// Collection of cut monitors for failed entities
  StHbtCutMonitorCollection* mFailColl;
  
#ifdef __ROOT__  
  ClassDef(StHbtCutMonitorHandler, 0)
#endif  
};

#endif
