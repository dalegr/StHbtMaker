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

/// StHbtMaker headers
#include "StHbtCutMonitor.h"

//_________________
void StHbtCutMonitor::fill(const StHbtEvent* /* event */) {
  /* empty */
}

//_________________
void StHbtCutMonitor::fill(const StHbtTrack* /* track */) {
  /* empty */
}

//_________________
void StHbtCutMonitor::fill(const StHbtV0* /* v0 */) {
  /* empty */
}

//_________________
void StHbtCutMonitor::fill(const StHbtXi* /* xi */) {
  /* empty */
}

//_________________
void StHbtCutMonitor::fill(const StHbtKink* /* kink*/) {
  /* empty */
}

//_________________
void StHbtCutMonitor::fill(const StHbtPair* /* pair */) {
  /* empty */
}

//_________________
void StHbtCutMonitor::fill(const StHbtParticleCollection* /* collection */) {
  /* empty */
}

//_________________
void StHbtCutMonitor::fill(const StHbtParticleCollection*,
			   const StHbtParticleCollection*) {
  /* empty */
}

//_________________
void StHbtCutMonitor::fill(const StHbtEvent*,const StHbtParticleCollection*) {
  /* empty */
}

//_________________
void StHbtCutMonitor::finish() { 
  /* empty */
}

//_________________
void StHbtCutMonitor::init() { 
  /* empty */
}
