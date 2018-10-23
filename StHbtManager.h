/// The Manager is the top-level object containing an EventReader
/// (the input), and collections of EventWriters and AliFemtoAnalyses
/// (the outputs).
///
/// A manager object is owned by an AliAnalysistaskFemto object which
/// calls the `ProcessEvent()` method, which reads an AliFemtoEvent
/// from the input files, and forwards it to the `ProcessEvent` method
/// in each output analysis, which is responsible for carrying out the
/// actual cuts & computation.
///
/// StHbtManager objects "own" the EventReader, Analyses, and
/// EventWriters added to them, and is responsible for deleting them
/// upon its own destruction.
///
/// StHbtManager objects are not copyable, as the StHbtAnalysis
/// objects they contain have no means of copying/cloning.
/// Denying copyability by making the copy constructor and assignment
/// operator private prevents potential dangling pointer (segfault)
/// errors.
///

#ifndef StHbtManager_h
#define StHbtManager_h

/// StHbtMaker headers
#include "StHbtTypes.h"
#include "StHbtAnalysisCollection.h"
#include "StHbtEventWriterCollection.h"
#include "StHbtEvent.h"
#include "StHbtBaseAnalysis.h"
#include "StHbtEventReader.h"
#include "StHbtEventWriter.h"

//_________________
class StHbtManager{

 public:
  /// Default constructor
  StHbtManager();
  /// Copy constructor
  StHbtManager(const StHbtManager& copy);
  /// Copy constructor
  StHbtManager& operator=(const StHbtManager& man);
  /// Default destructor
  virtual ~StHbtManager();

  /**
   * Setters and Getters
   **/
  /// Return pointer to the analysis collection
  StHbtAnalysisCollection *analysisCollection()        { return mAnalysisCollection; }
  /// Access to the n-th analysis within Collection
  StHbtBaseAnalysis       *analysis(int n);  
  void addAnalysis(StHbtBaseAnalysis *analysis)        { mAnalysisCollection->push_back(analysis); }

  /// Return pointer to the Collection of event writers
  StHbtEventWriterCollection* eventWriterCollection()  { return mEventWriterCollection; }
  /// Access to EventWriter within Collection
  StHbtEventWriter *EventWriter(int n);               
  void setEventWriter(StHbtEventWriter *writer)        { addEventWriter( writer ); }
  void addEventWriter(StHbtEventWriter* writer)        { mEventWriterCollection->push_back(writer); }

  StHbtEventReader* eventReader()                      { return mEventReader; }
  void setEventReader(StHbtEventReader* reader)        { mEventReader = reader; }

  /// Calls `init()` on all owned EventWriters
  ///
  /// Returns 0 for success, 1 for failure.
  ///
  int init();
  /// A "0" return value means success - otherwise quit
  int processEvent();
  /// Calls `Finish()` on the EventReader, EventWriters, and the Analyses.
  void finish();

  StHbtString report(); //!

 private:
  
  StHbtAnalysisCollection* mAnalysisCollection;
  StHbtEventReader*        mEventReader;
  StHbtEventWriterCollection* mEventWriterCollection;
  
#ifdef __ROOT__
  ClassDef(StHbtManager, 0)
#endif
};

#endif // StHbtManager_h

