/**
* Descritpion: The base class for cut monitors
*
* A cut monitor saves attributes of the entities that have passed or failed
* the given cut. This class is the base class which is present to
* provide a common interface for storing data.
*
* Cut monitors are to be used in conjunction with cut monitor handlers
* (StHbtCutMonitorHandler) - of which all standard cuts (e.g.
* StHbtEventCut) inherit from. Your cut monitor objects get added to the
* monitorhandlers via their addCutMonitor methods, and the Fill commands get
* called by the handler upon their fillCutMonitor method, with the particular
* entity type.
*
* The default behavior of this base class is to do nothing with the
* incoming data, as no data members are provided. It is up to the user to use
* (or write) a subclass with relevant histograms.
*
* To implement a custom cut monitor, subclass this class and overload the
* Fill method(s) corresponding to the entity type(s) you wish to monitor.
* All other 'fill' methods should be implemented to avoid 'member hiding'
* compiler warnings.
*
* All methods of this class are empty except report which returns an empty
* string and getOutputList which returns a pointer to an empty list.
*/

#ifndef StHbtCutMonitor_h
#define StHbtCutMonitor_h

/// Forward declarations
class StHbtEvent;
class StHbtTrack;
class StHbtV0;
class StHbtXi;
class StHbtKink;
class StHbtPair;

/// C++ headers
#include <iostream>

/// StHbtMaker headers
#include "StHbtString.h"
#include "StHbtParticleCollection.h"

/// ROOT headers
#include "TList.h"

//_________________
class StHbtCutMonitor {
  
 public:
  /// Default constructor
  StHbtCutMonitor()            { /* no-op */ };
  /// Default destructor
  virtual ~StHbtCutMonitor()   {/* no-op */};

  /// Report details
  virtual StHbtString report();
  
  virtual void eventBegin(const StHbtEvent*) { /* no-op */ }
  virtual void eventEnd(const StHbtEvent*)   { /* no-op */ }

  /// Returns pointer to empty list
  virtual TList* getOutputList();

  /// Various fill() methods: event, track, v0, kink, pair, particle collection
  virtual void fill(const StHbtEvent*);
  virtual void fill(const StHbtTrack*);
  virtual void fill(const StHbtV0*);
  virtual void fill(const StHbtXi*);
  virtual void fill(const StHbtKink*);
  virtual void fill(const StHbtPair*);
  virtual void fill(const StHbtParticleCollection*);
  virtual void fill(const StHbtEvent*,const StHbtParticleCollection*);
  virtual void fill(const StHbtParticleCollection*, const StHbtParticleCollection*);

  virtual void finish();
  virtual void init();
};

inline TList* StHbtCutMonitor::getOutputList() {
  TList *mOutputList = new TList();
  return mOutputList;
}

inline StHbtString StHbtCutMonitor::report() { 
  StHbtString defReport("*** no user defined fill(const StHbtEvent*), take from base class");
  return defReport; 
}

#endif //#define StHbtCutMonitor_h
