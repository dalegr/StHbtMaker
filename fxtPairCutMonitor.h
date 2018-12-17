#ifndef fxtPairCutMonitor_hh
#define fxtPairCutMonitor_hh

class StHbtPair;

//#include "StHbtMaker/Infrastructure/StHbtHisto.hh"
#include "StHbtCutMonitor.h"
#include "TH3F.h"
#include "TH2F.h"
#include "TH1F.h"

class fxtPairCutMonitor : public StHbtCutMonitor {

private:
  TH1F* mKt;
  TH3F* mPt1Pt2Qinv;
  TH2F* mFMRvsQinv;
  TH2F* mSLvsQinv;
  TH2F* mAveSepVsQinv;
  TH2F* mRValueVsQinv;
  TH2F* mDEtaDPhi;
  TH1F* mMinv;
  double mPartMass;

public:
  fxtPairCutMonitor(const char*);   // default constructor
  fxtPairCutMonitor( const  fxtPairCutMonitor& cutMoni);
  virtual ~fxtPairCutMonitor();

  virtual void fill(const StHbtPair* pair);

  // These dummy Fill() functions were introduced to remove a compiler
  //   warning related to overloaded base-class Fill() functions being 
  //   hidden by a single version of Fill() in this derived class
  void fill(const StHbtParticleCollection* d) {;}
  void fill(const StHbtEvent *d1, const StHbtParticleCollection* d2) {;}
  void fill(const StHbtTrack* d) {;}
  //void Fill(const StHbtPair* d) {;}
  void fill(const StHbtKink* d) {;}
  void fill(const StHbtV0* d) {;}
  void fill(const StHbtEvent* d) {;}
  
  TH1F* Kt() { return mKt; }
  TH3F* Pt1Pt2Qinv() { return mPt1Pt2Qinv; }
  TH2F* FMRvsQinv() { return mFMRvsQinv; }
  TH2F* SLvsQinv() { return mSLvsQinv; }
  TH2F* AveSepVsQinv() { return mAveSepVsQinv; }
  TH2F* RValueVsQinv() { return mRValueVsQinv; }
  TH2F* DEtaDPhi() { return mDEtaDPhi; }
  TH1F* Minv() { return mMinv; }
  
  void SetParticleMass(double mass);

#ifdef __ROOT__  
 ClassDef(fxtPairCutMonitor, 1)
#endif
};

inline void fxtPairCutMonitor::SetParticleMass(double mass) { mPartMass = mass; }

#endif
