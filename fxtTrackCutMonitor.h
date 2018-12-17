#ifndef fxtTrackCutMonitor_hh
#define fxtTrackCutMonitor_hh

class StHbtTrack;

//#include "StHbtMaker/Infrastructure/StHbtHisto.hh"
#include "StHbtCutMonitor.h"
#include "TH2F.h"
#include "TH1F.h"
//_________________
class fxtTrackCutMonitor : public StHbtCutMonitor {

 private:
  TH1F* mDCAGlobal;
  TH1F* mNhits;
  TH1F* mP;
  TH1F* mPt;
  TH2F* mPtVsNsigmaPion;
  TH2F* mPtVsNsigmaKaon;
  TH2F* mPtVsNsigmaProton;
  TH2F* mPvsDedx;
  TH1F* mRapidity;
  TH1F* mPseudoRapidity;
  TH2F* mPvsMassSqr;
  TH2F* mPvsInvBeta;
  TH2F* mPtVsEta;
#ifdef TPC_DNDX
  TH2F* mPtVsDndxNsigmaPion;
  TH2F* mPtVsDndxNsigmaKaon;
  TH2F* mPtVsDndxNsigmaProton;
  TH2F* mPvsDndx;
#endif
  double monMass;
  
public:
  fxtTrackCutMonitor(const char*, const double);   // default constructor
  fxtTrackCutMonitor( const  fxtTrackCutMonitor& cutMoni);
  virtual ~fxtTrackCutMonitor();

  virtual void fill(const StHbtTrack* track);

  // These dummy Fill() functions were introduced to remove a compiler
  //   warning related to overloaded base-class Fill() functions being 
  //   hidden by a single version of Fill() in this derived class
  void fill(const StHbtParticleCollection* d) {;}
  void fill(const StHbtEvent *d1, const StHbtParticleCollection* d2) {;}
  void fill(const StHbtPair* d) {;}
  void fill(const StHbtKink* d) {;}
  void fill(const StHbtV0* d) {;}
  void fill(const StHbtEvent* d) {;}
  
  TH1F* DCAGlobal() { return mDCAGlobal; }
  TH1F* Nhits() { return mNhits; }
  TH1F* P() { return mP; }
  TH1F* Pt() { return mPt; }
  TH2F* PtVsNsigmaPion() { return mPtVsNsigmaPion; }
  TH2F* PtVsNsigmaKaon() { return mPtVsNsigmaKaon; }
  TH2F* PtVsNsigmaProton() {return mPtVsNsigmaProton; }
  TH2F* PvsDedx() { return mPvsDedx; }
  TH1F* PseudoRapidity() { return mPseudoRapidity; }
  TH2F* PvsMassSqr() { return mPvsMassSqr; }
  TH2F* PvsInvBeta() {return mPvsInvBeta; }
  TH2F* PtVsEta() { return mPtVsEta; }
#ifdef TPC_DNDX
  TH2F* PtVsDndxNsigmaPion()   { return mPtVsDndxNsigmaPion;}
  TH2F* PtVsDndxNsigmaKaon()   { return mPtVsDndxNsigmaKaon;}
  TH2F* PtVsDndxNsigmaProton() { return mPtVsDndxNsigmaProton;}
  TH2F* PvsDndx() { return mPvsDndx;}
#endif
  
#ifdef __ROOT__  
 ClassDef(fxtTrackCutMonitor, 2)
#endif
};

#endif
