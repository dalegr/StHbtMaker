/**
 * Description: The Maker that runs StHbtMaker maker subclasses.
 *
 * One uses the maker to instantiate and add analysis into it.
 * To work in the STAR environment, sl73_gcc485 global variable
 * must be defined at the compilation and a the run time.
 */


/// C++ headers
#include <iostream>
#include <stdio.h>
#include <string>

/// ROOT headers
#include "Riostream.h"

/// StHbtMaker headers
#include "StHbtMaker.h"

#ifdef __ROOT__
ClassImp(StHbtMaker)
#endif

//_________________
StHbtMaker::StHbtMaker(const char*name, const char * title) : 
#ifdef sl73_gcc485
  // STAR compiled library
  StMaker(name,title),
#endif
  mDebug(0) {
  
  /// Constructor
  mHbtManager = new StHbtManager;
  std::cout << string::npos << std::endl;
}

//_________________
StHbtMaker::~StHbtMaker() {
  
  /// Destructor
  std::cout << "Inside ReaderMaker Destructor" << std::endl;
#ifdef sl73_gcc485
    SafeDelete(mHbtManager);  //
#else
  delete mHbtManager;
#endif
}

//_________________
void StHbtMaker::Clear(const char*) {
  /* no-op - do not delete manager! */
#ifdef sl73_gcc485
  StMaker::Clear();
#endif
}

//_________________
Int_t StHbtMaker::Init() {
  
  if ( mHbtManager->init() ) {
    std::cout << "StHbtMaker::Init() - manager init failed " << std::endl;
    return (2);
  }
  
  std::cout << "StHbtMaker::Init() - requesting a report " << std::endl;
  
  StHbtString tempString = mHbtManager->report();
  std::cout << "Got the report, now let me try to put it to screen" << std::endl;
  std::cout << tempString.c_str() << std::endl; //!
  
#ifdef sl73_gcc485
  return StMaker::Init();
#else
  return 0;
#endif
}

//_________________
Int_t StHbtMaker::Finish() {  
  std::cout << mHbtManager->report().c_str() << std::endl; //!
  mHbtManager->finish();
#ifdef sl73_gcc485
  return StMaker::Finish();
#else
  return 0;
#endif
}

//_________________
Int_t StHbtMaker::Make() {
  if (mDebug>1) {
    std::cout << "\nStHbtMaker::Make -- processing event" << std::endl;
  }
#ifdef sl73_gcc485
  if (mHbtManager->processEvent()){
    return kStEOF;    // non-zero value returned --> end of file action
  }
  else{
    return kStOK;
  }
#else
  return  mHbtManager->processEvent();
#endif
}
