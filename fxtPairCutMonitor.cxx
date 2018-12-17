#include "StHbtPair.h"
#include "fxtPairCutMonitor.h"
#include <cstdio>
#include <string>
//#include "StLorentzVector.hh"

#ifdef __ROOT__ 
ClassImp(fxtPairCutMonitor)
#endif

//_________________
fxtPairCutMonitor::fxtPairCutMonitor(const char* name){ // default constructor
  string s("fxtPairCutMonitor");
  string n(name);
  mKt = new TH1F( (s+n+"mKt").c_str(),"Kt;k_{T} (GeV/c)",
			  150,0.,1.5);
  mPt1Pt2Qinv = new TH3F( (s+n+"mPt1Pt2Qinv").c_str(),
				  "p_{T1} vs p_{T2} vs q_{inv};p_{T1} (GeV/c);p_{T2} (GeV/c);q_{inv} (GeV/c)",
				  32,0.,1.6,32,0.,1.6,400,0.,0.8);
			     
  mFMRvsQinv = new TH2F( (s+n+"mFMRvsQinv").c_str(),
				 "FMR vs q_{inv};q_{Inv} (GeV/c);FMR",
				 200, 0., 0.8,
				 100, 0., 1.); 
  mSLvsQinv = new TH2F( (s+n+"mSLvsQinv").c_str(),
				"SL vs q_{inv};q_{inv} (GeV/c);SL",
				200, 0., 0.8,
				32,-0.6, 1.); 
  mAveSepVsQinv = new TH2F( (s+n+"mAveSepVsQinv").c_str(),
				    "AveSep vs q_{inv};q_{inv} (GeV/c); AveSep (cm)",
				    200, 0., 0.8, 100, 0., 50.);
  mRValueVsQinv = new TH2F( (s+n+"mRValueVsQinv").c_str(),
				    "R=#sqrt{#\Delta#eta+#Delta#phi} vs q_{inv};q_{inv} (GeV/c);R",
				    200, 0., 0.8, 200, 0., 2.);
  mDEtaDPhi = new TH2F( (s+n+"mDEtaDPhi").c_str(),
				    "#Delta#eta vs. #Delta#phi;#Delta#phi;#Delta#eta",
          400, -2., 2., 300, -1.5, 1.5 );
  mMinv = new TH1F( (s+n+"mMinv").c_str(),
		    "M_{inv};M_{inv} (GeV/c^{2});Entries",
                    200, 0., 2.);
  
  mPartMass = 0.13957; //pion mass by default
}

//_________________
fxtPairCutMonitor::fxtPairCutMonitor( const  fxtPairCutMonitor& cutMoni)  {
  mKt = new TH1F(*(cutMoni.mKt));
  mPt1Pt2Qinv = new TH3F(*(cutMoni.mPt1Pt2Qinv));
  mFMRvsQinv =new TH2F(*(cutMoni.mFMRvsQinv));
  mSLvsQinv =new TH2F(*(cutMoni.mSLvsQinv));
  mAveSepVsQinv = new TH2F(*(cutMoni.mAveSepVsQinv));
  mRValueVsQinv = new TH2F(*(cutMoni.mRValueVsQinv));
  mDEtaDPhi = new TH2F(*(cutMoni.mDEtaDPhi));
  mMinv = new TH1F(*(cutMoni.mMinv));
  mPartMass = cutMoni.mPartMass;
}

//_________________
fxtPairCutMonitor::~fxtPairCutMonitor(){
  delete mKt;
  delete mPt1Pt2Qinv;
  delete mFMRvsQinv;
  delete mSLvsQinv;
  delete mAveSepVsQinv;
  delete mRValueVsQinv;
  delete mMinv;
  delete mDEtaDPhi;
}

//_________________
void  fxtPairCutMonitor::fill(const StHbtPair* pair){
  //Float_t mT = sqrt(pair->kT()*pair->kT() + (mPartMass*mPartMass));
  mKt->Fill( pair->kT(), 1.);
  mPt1Pt2Qinv->Fill(  pair->track1()->track()->pt(),
		      pair->track2()->track()->pt(),
		      pair->qInv() );
  mFMRvsQinv->Fill( pair->qInv(), pair->fractionOfMergedRow(), 1.);
  mSLvsQinv->Fill( pair->qInv(), pair->quality(), 1.);
  mAveSepVsQinv->Fill(pair->qInv(), pair->nominalTpcAverageSeparation(), 1.);
  mRValueVsQinv->Fill(pair->qInv(), pair->rValue(), 1.);
  mDEtaDPhi->Fill( pair->deltaPhi(), pair->deltaEta() );
  mMinv->Fill( pair->mInv() );

}


