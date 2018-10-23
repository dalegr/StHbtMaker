/**
 * Description: A handler for cut monitors
 *
 * You add cut monitors to the collection which are stored in two separate
 * collections - one which stores characteristics of the entities (tracks,
 * particles, pairs, events) that pass the respective cuts and the other for
 * the ones that fail the cut.
 */

/// C++ headers
#include <iterator>

/// StHbtMaker headers
#include "StHbtCutMonitorHandler.h"

#ifdef __ROOT__
ClassImp(StHbtCutMonitorHandler)
#endif

//_________________
StHbtCutMonitorHandler::StHbtCutMonitorHandler() :
  mCollectionsEmpty(true),
  mPassColl(nullptr),
  mFailColl(nullptr) {

  /// Default constructor
  mPassColl = new StHbtCutMonitorCollection();
  mFailColl = new StHbtCutMonitorCollection();
}

//_________________
StHbtCutMonitorHandler::StHbtCutMonitorHandler(const StHbtCutMonitorHandler& copy) :
  mCollectionsEmpty( copy.mCollectionsEmpty ),
  mPassColl( nullptr ),
  mFailColl( nullptr ) {

  /// Copy constructor
  mPassColl = new StHbtCutMonitorCollection( copy.mPassColl->begin(), copy.mPassColl->end() );
  mFailColl = new StHbtCutMonitorCollection( copy.mFailColl->begin(), copy.mFailColl->end() );
}

//_________________
StHbtCutMonitorHandler& StHbtCutMonitorHandler::operator=(const StHbtCutMonitorHandler& copy) {

  /// Assignment operator
  if ( this != &copy ) {

    if (mPassColl) {
      mPassColl->clear();
      mPassColl->insert( mPassColl->begin(), copy.mPassColl->begin(), copy.mPassColl->end() );
    }
    else {
      mPassColl = new StHbtCutMonitorCollection( copy.mPassColl->begin(), copy.mPassColl->end() );
    }

    if (mFailColl) {
      mFailColl->clear();
      mFailColl->insert( mFailColl->begin(), copy.mFailColl->begin(), copy.mFailColl->end() );
    }
    else {
      mFailColl = new StHbtCutMonitorCollection( copy.mFailColl->begin(), copy.mFailColl->end() );
    }
  } // if ( this != &copy )

  return *this;
}

//_________________
StHbtCutMonitorHandler::~StHbtCutMonitorHandler() {

  /// Default destructor
  delete mPassColl;
  delete mFailColl;
}

//_________________
void StHbtCutMonitorHandler::fillCutMonitor(const StHbtEvent* event, bool pass) {
  
  /// Fill event cut monitors
  if (mCollectionsEmpty) return;
  
  StHbtCutMonitorIterator iter;
  StHbtCutMonitor* CM;
  
  if ( pass) {
    for (iter=mPassColl->begin(); iter!=mPassColl->end(); iter++) {
      CM = *iter;
      CM->fill( event );
    }
  } //if ( pass)
  else {
    for (iter=mFailColl->begin(); iter!=mFailColl->end(); iter++){
      CM = *iter;
      CM->fill( event );
    }
  } //else
}

//_________________
void StHbtCutMonitorHandler::fillCutMonitor(const StHbtTrack* track, bool pass) {

  /// Fill track cut monitors
  if (mCollectionsEmpty) return;
  
  StHbtCutMonitorIterator iter;
  StHbtCutMonitor* CM;
  
  if ( pass) {
    for (iter=mPassColl->begin(); iter!=mPassColl->end(); iter++){
      CM = *iter;
      CM->fill( track );
    }
  }
  else {
    for (iter=mFailColl->begin(); iter!=mFailColl->end(); iter++){
      CM = *iter;
      CM->fill( track );
    }
  }
}

//_________________
void StHbtCutMonitorHandler::fillCutMonitor(const StHbtV0* v0, bool pass) {

  /// Fill V0 cut monitors
  if (mCollectionsEmpty) return;
  
  StHbtCutMonitorIterator iter;
  StHbtCutMonitor* CM;
  if ( pass) {
    for (iter=mPassColl->begin(); iter!=mPassColl->end(); iter++){
      CM = *iter;
      CM->fill( v0 );
    }
  }
  else {
    for (iter=mFailColl->begin(); iter!=mFailColl->end(); iter++){
      CM = *iter;
      CM->fill( v0 );
    }
  }
}

//_________________
void StHbtCutMonitorHandler::fillCutMonitor(const StHbtKink* kink, bool pass) {
  
  if (mCollectionsEmpty) return;
  
  StHbtCutMonitorIterator iter;
  StHbtCutMonitor* CM;
  
  if ( pass) {
    for (iter=mPassColl->begin(); iter!=mPassColl->end(); iter++){
      CM = *iter;
      CM->fill( kink );
    }
  }
  else {
    for (iter=mFailColl->begin(); iter!=mFailColl->end(); iter++){
      CM = *iter;
      CM->fill( kink );
    }
  }
}

//_________________
void StHbtCutMonitorHandler::fillCutMonitor(const StHbtXi* xi, bool pass) {
  
  if (mCollectionsEmpty) return;
  
  StHbtCutMonitorIterator iter;
  StHbtCutMonitor* CM;
  
  if ( pass) {
    for (iter=mPassColl->begin(); iter!=mPassColl->end(); iter++){
      CM = *iter;
      CM->fill( xi );
    }
  }
  else {
    for (iter=mFailColl->begin(); iter!=mFailColl->end(); iter++){
      CM = *iter;
      CM->fill( xi );
    }
  }
}

//_________________
void StHbtCutMonitorHandler::fillCutMonitor(const StHbtPair* pair, bool pass) {
  
  if (mCollectionsEmpty) return;
  
  StHbtCutMonitorIterator iter;
  StHbtCutMonitor* CM;
  
  if ( pass) {
    for (iter=mPassColl->begin(); iter!=mPassColl->end(); iter++){
      CM = *iter;
      CM->fill( pair );
    }
  }
  else {
    for (iter=mFailColl->begin(); iter!=mFailColl->end(); iter++){
      CM = *iter;
      CM->fill( pair );
    }
  }
}

//_________________
void StHbtCutMonitorHandler::fillCutMonitor(const StHbtParticleCollection* partColl) {
  
  if (mCollectionsEmpty) return;
  
  StHbtCutMonitorIterator iter;
  StHbtCutMonitor* CM;
  
  for (iter=mPassColl->begin(); iter!=mPassColl->end(); iter++){
    CM = *iter;
    CM->fill( partColl );
  }
}

//_________________
void StHbtCutMonitorHandler::fillCutMonitor(const StHbtEvent* event, const StHbtParticleCollection* partColl) {

  // Fill event particle collection
  if (mCollectionsEmpty) return;
  
  StHbtCutMonitorIterator iter;
  StHbtCutMonitor* CM;
  
  for (iter=mPassColl->begin(); iter!=mPassColl->end(); iter++){
    CM = *iter;
    CM->fill( event, partColl );
  }
}

//_________________
void StHbtCutMonitorHandler::fillCutMonitor(const StHbtParticleCollection *partColl1,
					    const StHbtParticleCollection *partColl2) {
  // Fill event particle collection
  if (mCollectionsEmpty) return;
  
  StHbtCutMonitorIterator iter;
  StHbtCutMonitor* CM;

  for (iter=mPassColl->begin(); iter!=mPassColl->end(); iter++) {
    CM = *iter;
    CM->fill( partColl1, partColl2 );
  }
}

//_________________
void StHbtCutMonitorHandler::finish() {
  
  StHbtCutMonitorIterator iter;
  for (iter=mPassColl->begin(); iter!=mPassColl->end(); iter++){
    (*iter)->finish();
  }
  for (iter=mFailColl->begin(); iter!=mFailColl->end(); iter++){
    (*iter)->finish();
  }
}

//_________________
void StHbtCutMonitorHandler::addCutMonitor(StHbtCutMonitor* cutMoni1, StHbtCutMonitor* cutMoni2) { 
  mPassColl->push_back(cutMoni1);
  mFailColl->push_back(cutMoni2);
  mCollectionsEmpty = false;
}

//_________________
void StHbtCutMonitorHandler::addCutMonitor(StHbtCutMonitor* cutMoni) { 
  //cout << " make a copy of the cutmonitor and push both into the collections " << endl;
  //cout << " not yet implemented" << endl;
  mPassColl->push_back( cutMoni );
  //cout << " only pass collection pushed" << endl;
  mCollectionsEmpty = false;
}

//_________________
void StHbtCutMonitorHandler::addCutMonitorPass(StHbtCutMonitor* cutMoni) { 
  mPassColl->push_back(cutMoni);
  mCollectionsEmpty = false;
}

//_________________
void StHbtCutMonitorHandler::addCutMonitorFail(StHbtCutMonitor* cutMoni) { 
  mFailColl->push_back(cutMoni);
  mCollectionsEmpty=false;
}

//_________________
StHbtCutMonitor* StHbtCutMonitorHandler::passMonitor(int n) {
  
  if ( static_cast<int>( mPassColl->size() ) <= n ) {
    return nullptr;
  }

  StHbtCutMonitorIterator iter = mPassColl->begin();
  for ( int i=0; i<n; i++) {
    iter++;
  }
  return *iter;
}

//_________________
StHbtCutMonitor* StHbtCutMonitorHandler::failMonitor(int n) { 
  
  if ( static_cast<int>( mFailColl->size() ) <= n ) {
    return nullptr;
  }

  StHbtCutMonitorIterator iter = mFailColl->begin();
  for ( int i=0; i<n; i++) {
    iter++;
  }
  return *iter;
}

//_____________________________________________________________________________
TList *StHbtCutMonitorHandler::getOutputList() {
  
  TList *tOutputList = new TList();

  for (auto &cut_monitor : *mPassColl) {
    TList *tLp = cut_monitor->getOutputList();

    TIter nextLp(tLp);
    while (TObject *obj = nextLp()) {
      tOutputList->Add(obj);
    }

    delete tLp;
  }

  for (auto &cut_monitor : *mFailColl) {
    TList *tLf = cut_monitor->getOutputList();

    TIter nextLf(tLf);
    while (TObject *obj = nextLf()) {
      tOutputList->Add(obj);
    }

    delete tLf;
  }

  return tOutputList;
}

//_________________
void StHbtCutMonitorHandler::eventBegin(const StHbtEvent* aEvent) {
  
  for (auto &cut_monitor : *mPassColl) {
    cut_monitor->eventBegin(aEvent);
  }

  for (auto &cut_monitor : *mFailColl) {
    cut_monitor->eventBegin(aEvent);
  }
}

//_________________
void StHbtCutMonitorHandler::eventEnd(const StHbtEvent* aEvent) {
  for (auto &cut_monitor : *mPassColl) {
    cut_monitor->eventEnd(aEvent);
  }

  for (auto &cut_monitor : *mFailColl) {
    cut_monitor->eventEnd(aEvent);
  }
}
