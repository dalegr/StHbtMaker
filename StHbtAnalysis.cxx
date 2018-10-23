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

/// C++ headers
#include <string>
#include <iostream>
#include <iterator>

/// StHbtMaker headers
// Base
#include "StHbtAnalysis.h"
#include "StHbtTrackCut.h"
#include "StHbtV0Cut.h"
#include "StHbtXiCut.h"
#include "StHbtKinkCut.h"

/// ROOT headers
#include "TObject.h"
#include "TString.h"

#ifdef __ROOT__ 
ClassImp(StHbtAnalysis)
#endif

StHbtEventCut*    copyTheCut(StHbtEventCut*);
StHbtParticleCut* copyTheCut(StHbtParticleCut*);
StHbtPairCut*     copyTheCut(StHbtPairCut*);
StHbtCorrFctn*    copyTheCorrFctn(StHbtCorrFctn*);

/// Generalized particle collection filler function - called by
/// FillParticleCollection()
///
/// This function loops over the track_collection, calling the cut's Pass
/// method on each track. If it passes, a new StHbtParticle is constructed
/// from the track's pointer (or more generally, the item returned by
/// dereferencing the container's iterator) and the cut's expected mass.
///
/// This templated function accepts a track cut, track collection, and an
/// AliFemtoParticleCollection (which points to the output) as input. The types
/// of the tracks are determined by the template paramters, which should be
/// automatically detected by argument inspection (you don't need to specify).
///
/// The original function also specified the iterator type, but since all
/// containers are standard STL containers, it now infers the type as
/// TrackCollectionType::iterator. If the track collections change to some
/// other type, it is recommended to add TrackCollectionIterType to the
/// template list, and add the appropriate type to the function calls in
/// FillParticleCollection.
template <class TrackCollectionType, class TrackCutType>
void doFillParticleCollection(TrackCutType *cut,
                              TrackCollectionType *track_collection,
                              StHbtParticleCollection *output) {
  
  for (const auto &track : *track_collection) {
    
    const Bool_t track_passes = cut->pass(track);
    cut->fillCutMonitor(track, track_passes);
    
    if (track_passes) {
      output->push_back( new StHbtParticle(track, cut->mass() ) );
    } //if (track_passes)
  } //for (const auto &track : *track_collection)
}

// This little function is used to apply ParticleCuts (TrackCuts or V0Cuts) and
// fill ParticleCollections from tacks in picoEvent. It is called from
// StHbtAnalysis::processEvent().
//
// The actual loop implementation has been moved to the collection-generic
// doFillParticleCollection() function
void fillHbtParticleCollection(StHbtParticleCut*         partCut,
			       StHbtEvent*               hbtEvent,
			       StHbtParticleCollection*  partCollection) {

  /// Selection of the particle types: Track, V0, Kink
  switch ( partCut->type() ) {
    
  case hbtTrack:
    {
      /// Cut is cutting on Tracks
      doFillParticleCollection( (StHbtTrackCut*)partCut,
				hbtEvent->trackCollection(),
				partCollection );
    }
    break;
    
  case hbtV0:
    {
      /// Cut is cutting on V0s
      doFillParticleCollection( (StHbtV0Cut*)partCut,
				hbtEvent->v0Collection(),
				partCollection );
    }
    break;
    
  case hbtXi:
    {
      /// Cut is cutting on Xis
      doFillParticleCollection( (StHbtXiCut*)partCut,
				hbtEvent->xiCollection(),
				partCollection );
    }
    break;
    
  case hbtKink:
    {
      /// Cut is cutting on Kinks
      doFillParticleCollection( (StHbtKinkCut*)partCut,
				hbtEvent->kinkCollection(),
				partCollection );
    }
    break;
  default:
    std::cout << "fillHbtParticleCollection function (in StHbtAnalysis.cxx): " 
	      << "Undefined Particle Cut type!!!" << partCut->type() << std::endl;
  } //switch (partCut->Type())

  partCut->fillCutMonitor( hbtEvent, partCollection );
}

//_________________
StHbtAnalysis::StHbtAnalysis() : mPicoEventCollectionVectorHideAway(nullptr),
				 mPairCut(nullptr), mCorrFctnCollection(nullptr),
				 mEventCut(nullptr), mFirstParticleCut(nullptr),
				 mSecondParticleCut(nullptr), mMixingBuffer(nullptr),
				 mPicoEvent(nullptr), mNumEventsToMix(0),mNeventsProcessed(0),
				 mMinSizePartCollection(0), mVerbose(true) {
  mCorrFctnCollection = new StHbtCorrFctnCollection;
  mMixingBuffer = new StHbtPicoEventCollection;
}

//_________________
StHbtAnalysis::StHbtAnalysis(const StHbtAnalysis& a) : StHbtBaseAnalysis(),
						       mPicoEventCollectionVectorHideAway(nullptr),
						       mPairCut(nullptr),
						       mCorrFctnCollection(nullptr),
						       mEventCut(nullptr),
						       mFirstParticleCut(nullptr),
						       mSecondParticleCut(nullptr),
						       mMixingBuffer(nullptr),
						       mPicoEvent(nullptr),
						       mNumEventsToMix(a.mNumEventsToMix),
						       mNeventsProcessed(0),
						       mMinSizePartCollection(a.mMinSizePartCollection),
						       mVerbose(a.mVerbose) {

  const char msg_template[] = " StHbtAnalysis::StHbtAnalysis(const StHbtAnalysis& a) - %s";
  const char warn_template[] = " [WARNING] StHbtAnalysis::StHbtAnalysis(const StHbtAnalysis& a)] %s";
  
  mCorrFctnCollection = new StHbtCorrFctnCollection;
  mMixingBuffer = new StHbtPicoEventCollection;

  /// Clone the event cut
  mEventCut = a.mEventCut->clone();
  if( mEventCut ) {
    setEventCut( mEventCut );
    if( mVerbose ) {
      std::cout << TString::Format( msg_template, "Event cut set") << std::endl;
    } // if( mVerbose )
  }
  else {
    std::cerr << Form( warn_template, "Cannot clone event cut!" ) << std::endl;
  }
  
  /// Clone the first particle cut
  mFirstParticleCut = a.mFirstParticleCut->clone();
  if( mFirstParticleCut ) {
    setFirstParticleCut( mFirstParticleCut );
    if ( mVerbose ) {
      std::cout << TString::Format( msg_template, "First particle cut set") << std::endl;
    } // if( mVerbose )
  }
  else {
    std::cerr << TString::Format( warn_template, "Cannot clone first particle cut!" ) << std::endl;    
  }
  
  /// Clone the second particle cut (if it exists)
  mSecondParticleCut = ( ( a.mFirstParticleCut == a.mSecondParticleCut ) ?
			 mFirstParticleCut : a.mSecondParticleCut );
  if( mSecondParticleCut ) {
    setSecondParticleCut( mSecondParticleCut );
    if( mVerbose ) {
      std::cout << TString::Format( msg_template, "Second particle cut set" ) << std::endl;
    } // if( mVerbose )
  }
  else {
    std::cerr << TString::Format( warn_template, "Cannot clone second particle cut!" ) << std::endl;   
  }

  /// Clone the pair cut
  mPairCut = a.mPairCut->clone();
  if( mPairCut ) {
    setPairCut( mPairCut );
    if( mVerbose ) {
      std::cout << TString::Format( msg_template, "Pair cut set" ) << std::endl;
    } // if( mVerbose )
  }
  else {
    std::cerr << TString::Format( warn_template, "Cannot clone pair cut!" ) << std::endl;       
  }

  StHbtCorrFctnIterator iter;
  for (iter=a.mCorrFctnCollection->begin();
       iter!=a.mCorrFctnCollection->end(); iter++) {

    if( mVerbose ) {
      std::cout << TString::Format( msg_template, "looking for correlation functions" ) << std::endl;
    } // if( mVerbose )
    StHbtCorrFctn* fctn = (*iter)->clone();
    if (fctn) {
      addCorrFctn(fctn);
    }
    else {
      std::cout << TString::Format( msg_template, "correlation function not found" ) << std::endl;
    }
  }

  if (mVerbose) {
    std::cout << TString::Format( msg_template, "Analysis copied" ) << std::endl;
  }
}

//_________________
StHbtAnalysis& StHbtAnalysis::operator=(const StHbtAnalysis& ana) {

  /// Assignment operator
  
  if ( this != &ana ) {

    const char warn_template[] = "StHbtAnalysis& StHbtAnalysis::operator=(const StHbtAnalysis& ana) : %s";
    
    /// Clear second particle cut to avoid double delete
    if( mFirstParticleCut == mSecondParticleCut ) {
      mSecondParticleCut = nullptr;
    }
    if (mEventCut) delete mEventCut;
    if (mPairCut) delete mPairCut;
    if (mFirstParticleCut) delete mFirstParticleCut;
    if (mSecondParticleCut) delete mSecondParticleCut;

    /// Clear correlation functions
    if (mCorrFctnCollection) {
      for (StHbtCorrFctnIterator iIter=mCorrFctnCollection->begin();
	   iIter!=mCorrFctnCollection->end(); iIter++) {
	delete *iIter;
      }
      mCorrFctnCollection->clear();
    } //if (mCorrFctnCollection)
    else {
      std::cerr << TString::Format( warn_template, "mCorrFctnCollection is a nullptr" ) << std::endl;
      mCorrFctnCollection =  new StHbtCorrFctnCollection;
    }

    /// Clear mixing buffer
    if (mMixingBuffer) {
      for (StHbtPicoEventIterator iIter=mMixingBuffer->begin();
	   iIter!=mMixingBuffer->end(); iIter++ ) {
	delete *iIter;
      }
      mMixingBuffer->clear();
    } //if (mMixingBuffer)
    else {
      std::cerr << TString::Format( warn_template, "mMixingBuffer is a nullptr" ) << std::endl;
      mMixingBuffer = new StHbtPicoEventCollection;
    }

    /// Copy objects
    mPairCut = ana.mPairCut->clone();
    mEventCut = ana.mEventCut->clone();
    mFirstParticleCut = ana.mFirstParticleCut->clone();
    mSecondParticleCut = ( ( ana.mFirstParticleCut == ana.mSecondParticleCut ) ?
			   mFirstParticleCut : ana.mSecondParticleCut->clone() );

    /// Check that cuts have just been coppied
    if (mEventCut) {
      setEventCut( mEventCut );
    }
    else {
      std::cerr << TString::Format( warn_template, "Could not copy the event cut" ) << std::endl;
    }
    
    if (mPairCut) {
      setPairCut( mPairCut );
    }
    else {
      std::cerr << TString::Format( warn_template, "Could not copy the pair cut" ) << std::endl;
    }

    if (mFirstParticleCut) {
      setFirstParticleCut( mFirstParticleCut );
    }
    else {
      std::cerr << TString::Format( warn_template, "Could not copy the first particle cut" ) << std::endl;
    }

    if (mSecondParticleCut) {
      setSecondParticleCut( mSecondParticleCut );
    }
    else {
      std::cerr << TString::Format( warn_template, "Could not copy the second particle cut" ) << std::endl;
    }

    /// Copy correlation functions
    for ( auto &cf : *ana.mCorrFctnCollection ) {
      StHbtCorrFctn *fctn = cf->clone();
      if ( fctn ) {
	addCorrFctn( fctn );
      }
    }

    /// Copy some numbers
    mNumEventsToMix = ana.mNumEventsToMix;
    mMinSizePartCollection = ana.mMinSizePartCollection;
    mVerbose = ana.mVerbose;
  } //if ( this != &ana )

  return *this;
}

//_________________
StHbtAnalysis::~StHbtAnalysis() {
  
  std::cout << "StHbtAnalysis::~StHbtAnalysis()" << std::endl;

  /// Delete event cut
  if (mEventCut) delete mEventCut; mEventCut = nullptr;
  /// Double-delete protection
  if( mFirstParticleCut == mSecondParticleCut ) {
    mSecondParticleCut = nullptr;
  }
  if (mFirstParticleCut)  delete mFirstParticleCut; mFirstParticleCut = nullptr;
  if (mSecondParticleCut) delete mSecondParticleCut; mSecondParticleCut = nullptr;
  if (mPairCut) delete mPairCut; mPairCut = nullptr;
  
  /// Now delete every CorrFunction in the Collection, and then the Collection itself
  if( mCorrFctnCollection ) {
    StHbtCorrFctnIterator iter;
    for ( iter=mCorrFctnCollection->begin();
	  iter!=mCorrFctnCollection->end(); iter++) {
      delete *iter;
    }
    delete mCorrFctnCollection;
  } //if( mCorrFctnCollection )
  
  /// Now delete every PicoEvent in the EventMixingBuffer and then the Buffer itself
  if (mMixingBuffer) {
    StHbtPicoEventIterator piter;
    for ( piter=mMixingBuffer->begin();
	  piter!=mMixingBuffer->end(); piter++){
      delete *piter;
    }
    delete mMixingBuffer;
  } //if (mMixingBuffer)
}

//_________________
StHbtCorrFctn* StHbtAnalysis::corrFctn(int n) { // return pointer to n-th correlation function
  
  if ( (n < 0) || ( static_cast<size_t>(n) > mCorrFctnCollection->size() ) ) {
    return nullptr;
  }
  StHbtCorrFctnIterator iter = mCorrFctnCollection->begin();
  for (int i=0; i<n ;i++) {
    iter++;
  }
  return *iter;
}

//_________________
StHbtString StHbtAnalysis::report() {

  /// Create a simple report from the analysis execution
  std::cout << "StHbtAnalysis - constructing Report..." 
	    << std::endl;
  string temp = "-----------\nHbt Analysis Report:\n";
  temp += "\nEvent Cuts:\n";
  temp += mEventCut->report();
  temp += "\nParticle Cuts - First Particle:\n";
  temp += mFirstParticleCut->report();
  temp += "\nParticle Cuts - Second Particle:\n";
  temp += mSecondParticleCut->report();
  temp += "\nPair Cuts:\n";
  temp += mPairCut->report();
  temp += "\nCorrelation Functions:\n";
  StHbtCorrFctnIterator iter;
  if ( mCorrFctnCollection->size()==0 ) {
    std::cout << "StHbtAnalysis-Warning : no correlations functions in this analysis " 
	      << std::endl;
  }
  for (iter=mCorrFctnCollection->begin(); iter!=mCorrFctnCollection->end();iter++){
    temp += (*iter)->report();
    temp += "\n";
  }
  temp += "-------------\n";
  StHbtString returnThis=temp;
  return returnThis;
}

//_________________
void StHbtAnalysis::processEvent(const StHbtEvent* hbtEvent) {

  /// Add event to processed events

  /// We will get a new pico event, if not prevent corr. fctn to access old pico event
  mPicoEvent = nullptr; 
  addEventProcessed();

  /// Startup for EbyE 
  eventBegin(hbtEvent);  

  //Event cut and event cut monitor
  bool tmpPassEvent = mEventCut->pass( hbtEvent );
  if( !tmpPassEvent ) {
    mEventCut->fillCutMonitor( hbtEvent, tmpPassEvent );
    /// Cleanup for EbyE
    eventEnd( hbtEvent );
    return; 
  }

  /// Analysis likes the event -- build a pico event from it, using tracks the
  /// analysis likes. This is what we will make pairs from and put in Mixing
  /// Buffer.
  /// No memory leak. We will delete picoevent when they come out
  /// of the mixing buffer
  mPicoEvent = new StHbtPicoEvent;

  StHbtParticleCollection *collection1 = mPicoEvent->firstParticleCollection();
  StHbtParticleCollection *collection2 = mPicoEvent->secondParticleCollection();

  /// Sanity check that both collections exist
  if (collection1 == nullptr || collection2 == nullptr) {
    std::cout << "StHbtAnalysis::processEvent - new PicoEvent is missing particle collections!"
	      << std::endl;
    eventEnd( hbtEvent );
    delete mPicoEvent;
    return;
  }

  /// Subroutine fills fPicoEvent'a FirstParticleCollection with tracks from
  /// hbtEvent which pass mFirstParticleCut. Uses cut's "type()" to determine
  /// which track collection to pull from hbtEvent.
  fillHbtParticleCollection( mFirstParticleCut,
			     (StHbtEvent*)hbtEvent,
			     mPicoEvent->firstParticleCollection() );

  /// In case of non-identical particles
  if ( !( analyzeIdenticalParticles() ) ) {
    fillHbtParticleCollection( mSecondParticleCut,
			       (StHbtEvent*)hbtEvent,
			       mPicoEvent->secondParticleCollection() );
  }
  
  if ( mVerbose ) {
    std::cout << " StHbtAnalysis::processEvent - #particles in First, Second Collections: "
	      << mPicoEvent->firstParticleCollection()->size() << " "
	      << mPicoEvent->secondParticleCollection()->size() << std::endl;
  } // if ( mVerbose )

  const unsigned int coll_1_size = collection1->size();
  const unsigned int coll_2_size = collection2->size();
  const bool coll_1_size_passes = coll_1_size >= mMinSizePartCollection;
  const bool coll_2_size_passes = analyzeIdenticalParticles() || (coll_2_size >= mMinSizePartCollection);

  tmpPassEvent = ( tmpPassEvent && coll_1_size_passes && coll_2_size_passes );

  /// Fill event cut monitor
  mEventCut->fillCutMonitor( hbtEvent, tmpPassEvent );

  /// Stop here if event did not pass cuts
  if( !tmpPassEvent ) {
    eventEnd( hbtEvent );
    delete mPicoEvent;
    return;
  }
  
  ///------ Make real pairs. If identical, make pairs for one collection ------///

  if ( analyzeIdenticalParticles() ) {
    makePairs("real", mPicoEvent->firstParticleCollection() );
  }
  else {
    makePairs("real", mPicoEvent->firstParticleCollection(),
	      mPicoEvent->secondParticleCollection() );
  }
  
  if (mVerbose) {
    std::cout << "StHbtAnalysis::processEvent() - reals done ";
  }
  
  ///---- Make pairs for mixed events, looping over events in mixingBuffer ----///

  StHbtPicoEvent* storedEvent;
  StHbtPicoEventIterator mPicoEventIter;

  for ( mPicoEventIter = mixingBuffer()->begin();
	mPicoEventIter != mixingBuffer()->end(); mPicoEventIter++ ) {
    
    storedEvent = *mPicoEventIter;
    
    if ( analyzeIdenticalParticles() ) {
      makePairs("mixed", mPicoEvent->firstParticleCollection(),
		storedEvent->firstParticleCollection() );
    }
    else {
      makePairs("mixed", mPicoEvent->firstParticleCollection(),
		storedEvent->secondParticleCollection() );
      
      makePairs("mixed", storedEvent->firstParticleCollection(),
		mPicoEvent->secondParticleCollection() );
    }
  } //for ( mPicoEventIter=MixingBuffer()->begin();	mPicoEventIter!=MixingBuffer()->end(); mPicoEventIter++)
  
  if (mVerbose) {
    std::cout << " - mixed done   " << std::endl;
  } // if (mVerbose)

  ///--------- If mixing buffer is full, delete oldest event ---------///
  if ( mixingBufferFull() ) {
    delete mixingBuffer()->back();
    mixingBuffer()->pop_back();
  }

  ///-------- Add current event (mPicoEvent) to mixing buffer --------//.
  mixingBuffer()->push_front(mPicoEvent);

  /// Cleanup for EbyE 
  eventEnd(hbtEvent);  
  //std::cout << "StHbtAnalysis::ProcessEvent() - return to caller ... " << std::endl;
}

//_________________________
void StHbtAnalysis::makePairs(const char* typeIn, 
			      StHbtParticleCollection *partCollection1,
			      StHbtParticleCollection *partCollection2) {

  /// Build pairs, check pair cuts, and call CFs' AddRealPair() or
  /// AddMixedPair() methods. If no second particle collection is
  /// specfied, make pairs within first particle collection.
  const string type = typeIn;

  /// Used to swap particle 1 & 2 in identical-particle analysis
  /// to avoid any implicit ordering in the event collection
  /// "Seed" this here.
  bool swpart = mNeventsProcessed % 2;


  /// Create the pair outside  the loop
  StHbtPair* ThePair = new StHbtPair;

  StHbtCorrFctnIterator CorrFctnIter;
  StHbtParticleIterator PartIter1, PartIter2;

  /// Setup iterator ranges
  ///
  /// The outer loop alway starts at beginning of particle collection 1.
  /// * If we are iterating over both particle collections, then the loop simply
  /// runs through both from beginning to end.
  /// * If we are only iterating over one particle collection, the inner loop
  /// loops over all particles between the outer iterator and the end of the
  /// collection. The outer loop must skip the last entry of the list.
  StHbtParticleIterator StartOuterLoop = partCollection1->begin();
  StHbtParticleIterator EndOuterLoop   = partCollection1->end();
  StHbtParticleIterator StartInnerLoop;
  StHbtParticleIterator EndInnerLoop;

  if (partCollection2) {                        // Two collections:
    StartInnerLoop = partCollection2->begin();  //   Full inner & outer loops
    EndInnerLoop   = partCollection2->end();    //
  }
  else {                                        // One collection:
    EndOuterLoop--;                             //   Outer loop goes to next-to-last particle
    EndInnerLoop = partCollection1->end() ;     //   Inner loop goes to last particle
  }

  /// Start the outer loop
  for ( PartIter1 = StartOuterLoop; PartIter1 != EndOuterLoop; PartIter1++) {

    /// If analyzing identical particles, start inner loop at the particle
    /// after the current outer loop position, (loops until end)
    if (!partCollection2){
      StartInnerLoop = PartIter1;
      StartInnerLoop++;
    }

    /// If we have two collections - set the first track
    if (partCollection2 != nullptr ) {
      ThePair->setTrack1( *PartIter1 );
    }

    /// Start the inner loop
    for (PartIter2 = StartInnerLoop; PartIter2 != EndInnerLoop; PartIter2++) {

      /// If we have two collections - only set the second track
      if ( partCollection2 != nullptr ) {
	ThePair->setTrack2( *PartIter2 );
      }
      else { /// Swap between first and second particles to avoid biased ordering
	ThePair->setTrack1( swpart ? *PartIter2 : *PartIter1 );
	ThePair->setTrack2( swpart ? *PartIter1 : *PartIter2 );
	swpart = !swpart;
      }

      /// Check if the pair passes the cut
      bool tmpPassPair = mPairCut->pass( ThePair );
      mPairCut->fillCutMonitor(ThePair, tmpPassPair);

      /// If pair passes cut, loop over CF's and add pair to real/mixed
      if( tmpPassPair ) {
	
	/// Iterate over correlation functions
	for( CorrFctnIter = mCorrFctnCollection->begin();
	     CorrFctnIter != mCorrFctnCollection->end(); CorrFctnIter++) {
	  
	  StHbtCorrFctn* CorrFctn = *CorrFctnIter;
	  if(type == "real") {
	    CorrFctn->addRealPair( ThePair );
	  }
	  else if(type == "mixed") {
	    CorrFctn->addMixedPair( ThePair );
	  }
	  else {
	    std::cout << "Problem with pair type, type = " << type.c_str() << std::endl;
	  }
	  
	} //for (CorrFctnIter=mCorrFctnCollection->begin() ...
      } //if (mPairCut->Pass(ThePair))
    } //for (PartIter2 = StartInnerLoop; PartIter2 != EndInnerLoop; PartIter2++)
  } //for ( PartIter1 = StartOuterLoop; PartIter1 != EndOuterLoop; PartIter1++)

  /// We are done with the pair
  delete ThePair;

}

//_________________
void StHbtAnalysis::eventBegin(const StHbtEvent* ev) {
  
  /// Perform initialization operations at the beginning of the event processing
  //std::cout << " StHbtAnalysis::EventBegin(const StHbtEvent* ev) " << std::endl;
  mFirstParticleCut->eventBegin(ev);
  mSecondParticleCut->eventBegin(ev);
  mPairCut->eventBegin(ev);
  for (StHbtCorrFctnIterator iter = mCorrFctnCollection->begin(); 
       iter != mCorrFctnCollection->end(); iter++) {
    (*iter)->eventBegin(ev);
  }
}

//_________________
void StHbtAnalysis::eventEnd(const StHbtEvent* ev) {

  /// Finish operations at the end of event processing
  mFirstParticleCut->eventEnd(ev);
  mSecondParticleCut->eventEnd(ev);
  mPairCut->eventEnd(ev);
  for (StHbtCorrFctnIterator iter = mCorrFctnCollection->begin(); 
       iter != mCorrFctnCollection->end();iter++) {
    (*iter)->eventEnd(ev);
  }
}

//_________________
void StHbtAnalysis::finish() {
  StHbtCorrFctnIterator iter;
  for ( iter = mCorrFctnCollection->begin();
	iter != mCorrFctnCollection->end(); iter++ ) {
    (*iter)->finish();
  }
}

//_________________
void StHbtAnalysis::addEventProcessed() {
  mNeventsProcessed++;
}

//_________________
TList* StHbtAnalysis::listSettings() {

  /// Collect settings list
  const TString setting_prefix = "StHbtAnalysis.";

  TList *tListSettings = new TList();

  TList *event_cut_settings = mEventCut->listSettings();
  if (event_cut_settings != nullptr) {
    TListIter next_event_setting( event_cut_settings );
    while (TObject *obj = next_event_setting()) {
      tListSettings->Add( new TObjString( setting_prefix + obj->GetName() ) );
    }
    delete event_cut_settings;
  } //if (event_cut_settings != nullptr)

  TList *p1_cut_settings = mFirstParticleCut->listSettings();
  if (p1_cut_settings != nullptr) {
    TListIter next_p1_setting(p1_cut_settings);
    while (TObject *obj = next_p1_setting()) {
      tListSettings->Add(new TObjString( setting_prefix + obj->GetName() ) );
    }
    delete p1_cut_settings;
  } //if (p1_cut_settings != nullptr)
  
  if (mSecondParticleCut != mFirstParticleCut) {
    TList *p2_cut_settings = mSecondParticleCut->listSettings();
    if (p2_cut_settings != nullptr) {
      TListIter next_p2_setting(p2_cut_settings);
      while (TObject *obj = next_p2_setting()) {
        tListSettings->Add(new TObjString( setting_prefix + obj->GetName() ) );
      }
      delete p2_cut_settings;
    }
  } //if (fSecondParticleCut != fFirstParticleCut)

  TList *pair_cut_settings = mPairCut->listSettings();
  if (pair_cut_settings != nullptr) {
    TListIter next_pair_setting(pair_cut_settings);
    while (TObject *obj = next_pair_setting()) {
      tListSettings->Add(new TObjString( setting_prefix + obj->GetName() ) );
    }
    delete pair_cut_settings;
  } //if (pair_cut_settings != nullptr)

  return tListSettings;
}

//_________________________
TList* StHbtAnalysis::getOutputList() {
  
  /// Collect the list of output objects to be written
  TList *tOutputList = new TList();

  TList *p1Cut = mFirstParticleCut->getOutputList();
  TListIter nextp1(p1Cut);
  while (TObject *obj = nextp1.Next()) {
    tOutputList->Add(obj);
  }
  delete p1Cut;

  if (mSecondParticleCut != mFirstParticleCut) {
    TList *p2Cut = mSecondParticleCut->getOutputList();

    TIter nextp2(p2Cut);
    while (TObject *obj = nextp2()) {
      tOutputList->Add(obj);
    }
    delete p2Cut;
  } //if (fSecondParticleCut != fFirstParticleCut)

  TList *pairCut = mPairCut->getOutputList();
  TIter nextpair(pairCut);
  while (TObject *obj = nextpair()) {
    tOutputList->Add(obj);
  }
  delete pairCut;

  TList *eventCut = mEventCut->getOutputList();
  TIter nextevent(eventCut);
  while (TObject *obj = nextevent()) {
    tOutputList->Add(obj);
  }
  delete eventCut;

  for (auto &cf : *mCorrFctnCollection) {
    TList *tListCf = cf->getOutputList();

    TIter nextListCf(tListCf);
    while (TObject *obj = nextListCf()) {
      tOutputList->Add(obj);
    }
    delete tListCf;
  }

  return tOutputList;
}
