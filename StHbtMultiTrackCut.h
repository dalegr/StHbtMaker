/**
 * This class allows to add many track cuts into the list
 */

#ifndef StHbtMultiTrackCut_h
#define StHbtMultiTrackCut_h

/// StHbtMaker headers
#include "StHbtTrackCut.h"
#include "StHbtTypes.h"
#include "StHbtTrack.h"
#include "StHbtV0.h"
#include "StHbtTrackCutCollection.h"

//_________________
class StHbtMultiTrackCut : public StHbtTrackCut {
 
 public:
  /// Default constructor
  StHbtMultiTrackCut();
  /// Copy constructor
  StHbtMultiTrackCut(const StHbtMultiTrackCut& copy);
  /// Assignment operator
  StHbtMultiTrackCut& operator=(const StHbtMultiTrackCut& copy);
  /// Destructor
  virtual ~StHbtMultiTrackCut();

  /// User-written method to return string describing cuts
  virtual StHbtString report();
  /// True if passes, false if not
  virtual bool pass(const StHbtTrack* track);

  virtual void addTrackCut(StHbtTrackCut*);
  virtual void eventBegin(const StHbtEvent*);
  virtual void eventEnd(const StHbtEvent*);

  StHbtParticleType type() { return hbtTrack; }

  virtual StHbtMultiTrackCut* clone();
    
 private:
  StHbtTrackCutCollection* mCutCollection;

#ifdef __ROOT__
  ClassDef(StHbtMultiTrackCut, 0)
#endif
};

#endif // #define StHbtMultiTrackCut_h
