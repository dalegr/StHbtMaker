/**
 * Description: The pure virtual base class for femto event readers.
 *
 * All event readers must inherit from this one.
 */

/// StHbtMaker headers
#include "StHbtEvent.h"
#include "StHbtEventCut.h"
#include "StHbtTrackCut.h"
#include "StHbtV0Cut.h"
#include "StHbtXiCut.h"
#include "StHbtKinkCut.h"
#include "StHbtEventReader.h"

#ifdef __ROOT__
ClassImp(StHbtEventReader)
#endif

//_________________
StHbtEventReader::StHbtEventReader() : mEventCut(nullptr),
  mTrackCut(nullptr),   mV0Cut(nullptr), mXiCut(nullptr), mKinkCut(nullptr),
  mReaderStatus(0), mDebug(1) {
  /* no-op */
}

//_________________
StHbtEventReader::StHbtEventReader(const StHbtEventReader &copy) :
  mEventCut( copy.mEventCut ), mTrackCut( copy.mTrackCut ),
  mV0Cut( copy.mV0Cut ), mXiCut( copy.mXiCut ), mKinkCut( copy.mKinkCut ),
  mReaderStatus( copy.mReaderStatus ), mDebug( copy.mDebug ) {
  /* no-op */
}

//_________________
StHbtEventReader& StHbtEventReader::operator=(const StHbtEventReader& aReader) {

  if ( this != &aReader) {
    mEventCut = aReader.mEventCut;
    mTrackCut = aReader.mTrackCut;
    mV0Cut    = aReader.mV0Cut;
    mXiCut    = aReader.mXiCut;
    mKinkCut  = aReader.mKinkCut;
    mReaderStatus = aReader.mReaderStatus;
    mDebug = aReader.mDebug;
  }

  return *this;
}

//_________________
StHbtString StHbtEventReader::report() {
  
  StHbtString temp = "\n This is the base class StHbtEventReader reporting";
  temp += "\n---> EventCuts in Reader: ";
  if (mEventCut) {
    temp += mEventCut->report();
  }
  else {
    temp += "NONE";
  }
  temp += "\n---> TrackCuts in Reader: ";
  if (mTrackCut) {
    temp += mTrackCut->report();
  }
  else {
    temp += "NONE";
  }
  temp += "\n---> V0Cuts in Reader: ";
  if (mV0Cut) {
    temp += mV0Cut->report();
  }
  else {
    temp += "NONE";
  }
  temp += "\n---> XiCuts in Reader: ";
  if (mXiCut) {
    temp += mXiCut->report();
  }
  else {
    temp += "NONE";
  }
  temp += "\n---> KinkCuts in Reader: ";
  if (mKinkCut) {
    temp += mKinkCut->report();
  }
  else {
    temp += "NONE";
  }
  temp += "\n";
  return temp;
}

//_________________
void StHbtEventReader::setEventCut(StHbtEventCut* ecut) {
  mEventCut = ecut;
}

//_________________
void StHbtEventReader::setTrackCut(StHbtTrackCut* pcut) {
  std::cout << pcut << std::endl;
  mTrackCut = pcut;
}

//_________________
void StHbtEventReader::setV0Cut(StHbtV0Cut* pcut) {
  mV0Cut = pcut;
}

//_________________
void StHbtEventReader::setXiCut(StHbtXiCut* pcut) {
  mXiCut = pcut;
}

//_________________
void StHbtEventReader::setKinkCut(StHbtKinkCut* pcut) {
  mKinkCut = pcut;
}

//_________________
StHbtEventCut* StHbtEventReader::eventCut() {
  return mEventCut;
}

//_________________
StHbtTrackCut* StHbtEventReader::trackCut() {
  return mTrackCut;
}

//_________________
StHbtV0Cut* StHbtEventReader::v0Cut() {
  return mV0Cut;
}

//_________________
StHbtXiCut* StHbtEventReader::xiCut() {
  return mXiCut;
}

//_________________
StHbtKinkCut* StHbtEventReader::kinkCut() {
  return mKinkCut;
}


