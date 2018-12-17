#ifndef fxtEventCutMonitor_hh
#define fxtEventCutMonitor_hh

#include "StHbtTypes.h"
#include "StHbtEvent.h"
#include "StHbtCutMonitor.h"
#include "TProfile.h"
#include "TH2F.h"
#include "TH1F.h"
class fxtEventCutMonitor : public StHbtCutMonitor{

private:
  TH2F*  mVertexYvsVertexX;  
  TH1F*  mVertexZ; 
  TH1F*  mRefMult;
  TH1F*  mVpdVzDiff;

public:
  fxtEventCutMonitor();
  fxtEventCutMonitor(const char* TitCutMoni, const char* title);
  virtual ~fxtEventCutMonitor();


  virtual StHbtString report(); 
  virtual void fill(const StHbtEvent* event);
  virtual void finish();
  
  // These dummy Fill() functions were introduced to remove a compiler
  //   warning related to overloaded base-class Fill() functions being 
  //   hidden by a single version of Fill() in this derived class
  void fill(const StHbtParticleCollection* d) {;}
  void fill(const StHbtEvent *d1, const StHbtParticleCollection* d2) {;}
  void fill(const StHbtPair* d) {;}
  void fill(const StHbtKink* d) {;}
  void fill(const StHbtV0* d) {;}
  void fill(const StHbtTrack* d) {;}

  TH2F* VertexYvsVertexX() {return mVertexYvsVertexX;}
  TH1F* VertexZ() {return mVertexZ;}
  TH1F* RefMult() {return mRefMult;}
  TH1F* VpdVzDiff() {return mVpdVzDiff;}
    
#ifdef __ROOT__ 
 ClassDef(fxtEventCutMonitor, 1)
#endif
};

#endif

