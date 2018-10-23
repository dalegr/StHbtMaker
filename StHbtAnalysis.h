/**
 * Description: The most basic (concrete) analysis there is.
 *
 * Most other analyses (e.g. StHbtVertexAnalysis) inherit from this one.
 * Provides basic functionality for the analysis. To properly set up the
 * analysis the following steps should be taken:
 *
 * - create particle cuts and add them via setFirstParticleCut and
 *  setSecondParticleCut. If one analyzes identical particle
 *  correlations, the first particle cut must be also the second
 *  particle cut.
 *
 * - create pair cuts and add them via setPairCut
 *
 * - create one or many correlation functions and add them via
 *  addCorrFctn method.
 *
 * - specify how many events are to be strored in the mixing buffer for
 *  background construction
 *
 * Then, when the analysis is run, for each event, the eventBegin is
 * called before any processing is done, then the ProcessEvent is called
 * which takes care of creating real and mixed pairs and sending them
 * to all the registered correlation functions. At the end of each event,
 * after all pairs are processed, eventEnd is called. After the whole
 * analysis finishes (there is no more events to process) finish() is
 * called.
 */

#ifndef StHbtAnalysis_h
#define StHbtAnalysis_h

/// StHbtMaker headers
// Base classes
#include "StHbtBaseAnalysis.h"
#include "StHbtPairCut.h"     
#include "StHbtEventCut.h"
#include "StHbtParticleCut.h"
#include "StHbtCorrFctn.h"
// Infrustructure classes
#include "StHbtCorrFctnCollection.h"
#include "StHbtPicoEventCollection.h"
#include "StHbtParticleCollection.h"
#include "StHbtPicoEvent.h"

/// ROOT headers
#include "TList.h"

/// Forward declaration
class StHbtPicoEventCollectionVectorHideAway;

//_________________
class StHbtAnalysis : public StHbtBaseAnalysis {

 public:
  /// Construct with default parameters
  ///
  /// All pointer members are initialized to NULL except for the correlation
  /// function collection (mCorrFctnCollection) and the mixing buffer
  /// (mMixingBuffer) which are created with default parameters.
  StHbtAnalysis();
  
  /// Copy parameters from another analysis.
  ///
  /// All parameters are copied and cuts & correlation functions are cloned.
  /// A new (empty) mixing buffer is created and the number of events processed
  /// (mNeventsProcessed) is set to 0. The EventCollectionHideAway is NOT
  /// copied, and it's up to the subclass to clone if neccessary.
  StHbtAnalysis(const StHbtAnalysis&);
  /// Copy constructor
  StHbtAnalysis& operator=(const StHbtAnalysis&);
  /// Default destructor
  virtual ~StHbtAnalysis();

  /**
   * Setters and getters
   **/
  virtual StHbtPairCut*       pairCut();
  virtual StHbtEventCut*      eventCut();
  virtual StHbtParticleCut*   firstParticleCut();
  virtual StHbtParticleCut*   secondParticleCut();

  /// Return pointer to the correlation function collection
  StHbtCorrFctnCollection*    corrFctnCollection();
  /// Access to CFs within the collection
  virtual StHbtCorrFctn*      corrFctn(int n);
  /// Add correlation function to the analysis
  void addCorrFctn(StHbtCorrFctn* cf)
  { mCorrFctnCollection->push_back(cf); cf->setAnalysis( (StHbtBaseAnalysis*)this ); }

  /// Set cuts
  void setPairCut(StHbtPairCut* x)
  { mPairCut = x; x->setAnalysis( (StHbtBaseAnalysis*)this ); }
  void setEventCut(StHbtEventCut* x)
  { mEventCut = x; x->setAnalysis( (StHbtBaseAnalysis*)this ); }
  void setFirstParticleCut(StHbtParticleCut* x)
  { mFirstParticleCut = x; x->setAnalysis( (StHbtBaseAnalysis*)this ); }
  void setSecondParticleCut(StHbtParticleCut* x)
  { mSecondParticleCut = x; x->setAnalysis( (StHbtBaseAnalysis*)this ); }

  void setMinSizePartCollection(unsigned int& minSize) { mMinSizePartCollection = minSize; }
  void setVerboseMode(bool isVerbose);

  /// Event mixing buffer size
  unsigned int numEventsToMix()                        { return mNumEventsToMix; }
  void setNumEventsToMix(const unsigned int& nmix)     { mNumEventsToMix = nmix; }
  StHbtPicoEvent* currentPicoEvent()                   { return mPicoEvent; }
  StHbtPicoEventCollection* mixingBuffer()             { return mMixingBuffer; }
  bool mixingBufferFull()
  { return ( mMixingBuffer->size() >= mNumEventsToMix ); }
  bool analyzeIdenticalParticles()
  { return (mFirstParticleCut == mSecondParticleCut); }
  
  /// Returns reports of all cuts applied and correlation functions being done
  virtual StHbtString report();
  /// Return list of cut settings for the analysis
  virtual TList* listSettings();
  /// Return a TList of objects to be written as output
  virtual TList* getOutputList();

  /// Initialization code run at the beginning of processing an event
  ///
  /// This is implemented by calling EventBegin for each member cut
  /// and correlation function
  virtual void eventBegin(const StHbtEvent*);

  /// Bulk of analysis code
  ///
  /// This functions begins by calling EventBegin. If the event passes the
  /// event cut, pairs are made from the particles passing their respective
  /// cuts. The pairs are passed to each correlation function's AddRealPair
  /// method. Pairs made between particles in this event and events in the
  /// mixing buffer, are passed to the correlation functions' AddMixedPair
  /// method. The event is then added to the mixing buffer. The EventEnd() is
  /// called exactly once upon exiting this function.
  virtual void processEvent(const StHbtEvent*);
  
  /// Cleanup code after processing each event
  ///
  /// Calls EventEnd for each member cut and correlation function.
  virtual void eventEnd(const StHbtEvent*);

  /// Returns number of events which have been passed to processEvent.
  int nEventsProcessed()                                { return mNeventsProcessed; }

  virtual void finish();
  
  friend class StHbtLikeSignAnalysis;

protected:

  /// Increment fNeventsProcessed - is this method neccessary?
  void addEventProcessed();

  /// Build pairs, check pair cuts, and call CFs' AddRealPair() or
  /// AddMixedPair() methods. If no second particle collection is
  /// specfied, make pairs within first particle collection.
  ///
  /// \param type Either the string "real" or "mixed", specifying which method
  ///             to call (AddRealPair or AddMixedPair)
  void makePairs(const char* type, StHbtParticleCollection*, StHbtParticleCollection* p2=0);

  /// Mixing Buffer used for Analyses which wrap this one
  StHbtPicoEventCollectionVectorHideAway* mPicoEventCollectionVectorHideAway;

  /// Pointers to the cuts and collections
  StHbtPairCut*             mPairCut;
  StHbtCorrFctnCollection*  mCorrFctnCollection;
  StHbtEventCut*            mEventCut;
  StHbtParticleCut*         mFirstParticleCut;
  StHbtParticleCut*         mSecondParticleCut;
  StHbtPicoEventCollection* mMixingBuffer;
  StHbtPicoEvent*           mPicoEvent;
  
  /// How many "previous" events get mixed with this one, to make background
  unsigned int mNumEventsToMix;
  /// Don't use event if it has fewer than this many particles passing ParticleCuts default 0
  unsigned int mNeventsProcessed;
  /// Minimum # particles in ParticleCollection
  unsigned int mMinSizePartCollection;
  /// Print info
  bool mVerbose;

#ifdef __ROOT__
  ClassDef(StHbtAnalysis, 0)
#endif
};

/**
 * Getters
 **/
inline StHbtPairCut*             StHbtAnalysis::pairCut() {return mPairCut;}
inline StHbtEventCut*            StHbtAnalysis::eventCut() {return mEventCut;}
inline StHbtParticleCut*         StHbtAnalysis::firstParticleCut() {return mFirstParticleCut;}
inline StHbtParticleCut*         StHbtAnalysis::secondParticleCut() {return mSecondParticleCut;}
inline StHbtCorrFctnCollection*  StHbtAnalysis::corrFctnCollection() {return mCorrFctnCollection;}

#endif // #define StHbtAnalysis_h
