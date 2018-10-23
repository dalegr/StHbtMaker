/**
 * Description: The pure virtual base class for femto event readers.
 *
 * All event readers must inherit from this one.
 */

#ifndef StHbtEventReader_h
#define StHbtEventReader_h

/// C++ headers
#include <iostream>

/// Forward declarations
class StHbtEvent;
class StHbtEventCut;
class StHbtTrackCut;
class StHbtV0Cut;
class StHbtXiCut;
class StHbtKinkCut;

/// StHbtMaker headers
#include "StHbtString.h"

//_________________
class StHbtEventReader {

 public:
  /// Default constructor
  ///
  /// Even though it's only a base class and never constructed, if you don't
  /// have an implementation, you get "AliFemtoEventReader type_info node" upon
  /// dynamical loading
  ///
  /// All pointers are set to NULL, the status is set to 0 (good), and debug is
  /// set to 1 (print debug information in methods which run once)
  ///
  StHbtEventReader();
  
  /// Copy constructor
  ///
  /// This performs a shallow copy, so both the origial and new event readers
  /// point to the same cut objects.
  StHbtEventReader(const StHbtEventReader& copy);
  
  /// Assignment Operator
  /// Performs shallow copy of members
  StHbtEventReader& operator=(const StHbtEventReader& copy);
  
  /// Destructor
  ///
  /// No members are deleted - it is up to the entity creating the cuts to
  /// delete them after the event reader has run its course
  virtual ~StHbtEventReader()  { /* no-op */ }

  /// Concrete subclasses MUST implement this method, which creates the StHbtEvent
  virtual StHbtEvent* returnHbtEvent() =0;

  /// User-written method to return string describing reader
  /// including whatever "early" cuts are being done
  virtual StHbtString report();

  /// Next method does NOT need to be implemented, in which case the 
  /// "default" method below is executed
  virtual int writeHbtEvent(StHbtEvent*)
  { std::cout << "No WriteHbtEvent implemented" << std::endl; return 0; }

  // Next two are optional but would make sense for, e.g., opening and closing a file
  virtual int init(const char* ReadWrite, StHbtString& Message)
  { std::cout << "do-nothing StHbtEventReader::Init()" << std::endl; return 0; }
  
  virtual void finish()         { /*no-op*/ }

  /// StHbtManager looks at this for guidance if it gets null pointer from ReturnHbtEvent
  int status()                  { return mReaderStatus; } 

  virtual void setEventCut(StHbtEventCut* ecut);
  virtual void setTrackCut(StHbtTrackCut* pcut);
  virtual void setV0Cut(StHbtV0Cut* pcut);
  virtual void setXiCut(StHbtXiCut* pcut);
  virtual void setKinkCut(StHbtKinkCut* pcut);
  
  virtual StHbtEventCut* eventCut();
  virtual StHbtTrackCut* trackCut();
  virtual StHbtV0Cut*    v0Cut();
  virtual StHbtXiCut*    xiCut();
  virtual StHbtKinkCut*  kinkCut();

  /**
   * Controls the amount of debug information printed.
   * The code indicates which functions should print debug statements:
   *
   * 0: no output at all
   * 1: once (e.g. in constructor, finsh
   * 2: once per event
   * 3: once per track
   * 4: once per pair
   */
  int debug()             { return mDebug; } 
  void setDebug(int d)    { mDebug = d; }

 protected:
  /// Link to the front-loaded event cut
  StHbtEventCut *mEventCut;
  /// Link to the front-loaded track cut
  StHbtTrackCut *mTrackCut;
  /// Link to the front-loaded V0 cut
  StHbtV0Cut    *mV0Cut;
  /// Link to the front-loaded Xi cut
  StHbtXiCut    *mXiCut;
  /// Link to the front-loaded Kink cut
  StHbtKinkCut  *mKinkCut;
  /// status: 0 - good
  int mReaderStatus;
  int mDebug;

#ifdef __ROOT__
  ClassDef(StHbtEventReader,0)
#endif
};

#endif // #define StHbtEventReader_h
