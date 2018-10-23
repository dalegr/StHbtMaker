/**
 * Description: The Maker that runs StHbtMaker maker subclasses.
 *
 * One uses the maker to instantiate and add analysis into it.
 * To work in the STAR environment, sl73_gcc485 global variable
 * must be defined at the compilation and a the run time.
 */

#ifndef StHbtMaker_h
#define StHbtMaker_h

#ifdef sl73_gcc485
/// STAR headers
#include "StMaker.h"
#endif

/// StHbtMaker headers
#include "StHbtManager.h"

//_________________
class StHbtMaker
#ifdef sl73_gcc485
: public StMaker 
#endif
{

 public:
  /// Constructor
  StHbtMaker(const char* name = "StHbt", const char* title = "StHbtTitle");
  /// Destructor
  virtual ~StHbtMaker();

  /// Standard StChain (STAR) options that can be used
  /// in a standalone mode.
  virtual void  Clear(const char* opt="");
  virtual Int_t Init();    //!
  virtual Int_t Make();
  virtual Int_t Finish();  //!

  StHbtManager* hbtManager()  { return mHbtManager; }
  int debug() const           { return mDebug; }
  void setDebug(int debug)    { mDebug = debug; }

#ifdef sl73_gcc485
  StMaker* currentChain;
#endif

 private:
  
  StHbtManager* mHbtManager;  //! tells cint to skip it
  int mDebug;

#ifdef __ROOT__
  ClassDef(StHbtMaker,0)
#endif
};

#endif
