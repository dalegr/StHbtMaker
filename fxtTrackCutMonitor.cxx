#include "StHbtTrack.h"
#include "fxtTrackCutMonitor.h"
#include <cstdio>
#include <string>
//#include "StLorentzVector.hh"

#ifdef __ROOT__ 
ClassImp(fxtTrackCutMonitor)
#endif

//_________________
fxtTrackCutMonitor::fxtTrackCutMonitor(const char* name,
				       const double ParticleMass){ // default constructor
  monMass = ParticleMass;
  string s("fxtTrackCutMonitor");
  string n(name);
  mDCAGlobal= new TH1F( (s+n+"mDCAGlobal").c_str(),
				"DCA Global; DCA Global (cm)",
				100,0.,5.); 
  mNhits = new TH1F( (s+n+"mNhits").c_str(),"nHits;nHits",
			     50, 0., 50.);
  mP = new TH1F( (s+n+"mP").c_str(),"Momentum;P (GeV/c)",
			  180,0.,1.8);
  mPt = new TH1F( (s+n+"mPt").c_str(),
			  "Transverse momentum; Pt (GeV/c)",
			  180,0.,1.8);
  mPtVsNsigmaPion = new TH2F( (s+n+"mPtVsNsigmaPion").c_str(),
				     "p{T} vs n#sigma(#pi);p_{T} (GeV/c);n#sigma(#pi)",
				      36,0.1,1.9,100,-10.,10.);
  mPtVsNsigmaKaon = new TH2F( (s+n+"mPtVsNsigmaKaon").c_str(),
				     "p_{T} vs n#sigma(K);p_{T} (GeV/c);n#sigma(K)",
				     36,0.1,1.9,100,-10.,10.);
  mPtVsNsigmaProton = new TH2F( (s+n+"mPtVsNsigmaProton").c_str(),
				    "p_{T} vs n#sigma(p);p_{T} (GeV/c);n#sigma(p)",
					36,0.1,1.9,100,-10.,10.);
  mPvsDedx= new TH2F( (s+n+"mPvsDedx").c_str(),
			      "p vs dE/dx (a.u.);p (GeV/c); dE/dx (a.u.)",
			      180, 0.1, 1.9, 100, 0., 10.); 
  mRapidity = new TH1F( (s+n+"mRapidity").c_str(),
				"Rapidity;y",
				70, -1.2, 1.2);
  mPseudoRapidity = new TH1F( (s+n+"mPseudoRapidity").c_str(),
				      "PseudoRapidity;#eta",
				      120, -1.2, 1.2);
  mPvsMassSqr = new TH2F( (s+n+"mPvsMassSqr").c_str(),
				  "p_{T} vs m^{2};p_{T} (GeV/c);m^{2} (GeV/c^{2})^{2}",
				   180,0.1,1.9,120, -0.1, 1.1);
  mPvsInvBeta = new TH2F( (s+n+"mPvsInvBeta").c_str(),
				  "1/#beta vs P;p (GeV/c);1/#beta",
				  180, 0.1, 1.9, 60, 0.8, 2.);
  mPtVsEta  = new TH2F( (s+n+"mPtVsEta").c_str(),
			"p_{T} vs #eta;p_{T} (GeV/c);#eta",
			36,0.1,1.9,100,-10.,10.);
#ifdef TPC_DNDX
  mPtVsDndxNsigmaPion = new TH2F( (s+n+"mPtVsDndxNsigmaPion").c_str(),
                                          "p_{T} vs n#sigma^{dN/dx}(#pi);p_{T} (GeV/c);n#sigma^{dN/dx}(#pi)",
                                          36,0.1,1.9, 100, -10., 10.);
  mPtVsDndxNsigmaKaon = new TH2F( (s+n+"mPtVsDndxNsigmaKaon").c_str(),
                                          "p_{T} vs n#sigma^{dN/dx}(K);p_{T} (GeV/c);n#sigma^{dN/dx}(K)",
                                          36,0.1,1.9, 100, -10., 10.);
  mPtVsDndxNsigmaProton = new TH2F( (s+n+"mPtVsDndxNsigmaProton").c_str(),
                                          "p_{T} vs n#sigma^{dN/dx}(p);p_{T} (GeV/c);n#sigma^{dN/dx}(p)",
                                          36,0.1,1.9, 100, -10., 10.);
  mPvsDndx= new TH2F( (s+n+"mPvsDndx").c_str(),
	                  		      "p vs dN/dx (a.u.);p (GeV/c); dN/dx (a.u.)",
			                        180, 0.1, 1.9, 400, 20., 100.);
#endif
}

//_________________
fxtTrackCutMonitor::fxtTrackCutMonitor( const  fxtTrackCutMonitor& cutMoni)  {
  mDCAGlobal =new TH1F(*(cutMoni.mDCAGlobal));
  mNhits = new TH1F(*(cutMoni.mNhits));
  mP = new TH1F(*(cutMoni.mP));
  mPt = new TH1F(*(cutMoni.mPt));
  mPtVsNsigmaPion = new TH2F(*(cutMoni.mPtVsNsigmaPion));
  mPtVsNsigmaKaon = new TH2F(*(cutMoni.mPtVsNsigmaKaon));
  mPtVsNsigmaProton = new TH2F(*(cutMoni.mPtVsNsigmaProton));
  mPvsDedx =new TH2F(*(cutMoni.mPvsDedx));
  mRapidity= new TH1F(*(cutMoni.mRapidity));
  mPseudoRapidity= new TH1F(*(cutMoni.mPseudoRapidity));
  mPvsMassSqr = new TH2F(*(cutMoni.mPvsMassSqr));
  mPvsInvBeta = new TH2F(*(cutMoni.mPvsInvBeta));
  mPtVsEta = new TH2F(*(cutMoni.mPtVsEta));
#ifdef TPC_DNDX
  mPtVsDndxNsigmaPion = new TH2F(*(cutMoni.mPtVsDndxNsigmaPion));
  mPtVsDndxNsigmaKaon = new TH2F(*(cutMoni.mPtVsDndxNsigmaKaon));
  mPtVsDndxNsigmaProton = new TH2F(*(cutMoni.mPtVsDndxNsigmaProton));
  mPvsDndx =new TH2F(*(cutMoni.mPvsDndx));
#endif
}

//_________________
fxtTrackCutMonitor::~fxtTrackCutMonitor(){
  delete mDCAGlobal;
  delete mNhits;
  delete mP;
  delete mPt;
  delete mPtVsNsigmaPion;
  delete mPtVsNsigmaKaon;
  delete mPtVsNsigmaProton;
  delete mPvsDedx ;
  delete mRapidity;
  delete mPseudoRapidity;
  delete mPvsMassSqr;
  delete mPvsInvBeta;
  delete mPtVsEta;
#ifdef TPC_DNDX
  delete mPtVsDndxNsigmaPion;
  delete mPtVsDndxNsigmaKaon;
  delete mPtVsDndxNsigmaProton;
  delete mPvsDndx;
#endif
}

//_________________
void  fxtTrackCutMonitor::fill(const StHbtTrack* track){


  /*
    float TPhi = atan2(track->P().y(),track->P().x());
    if(TPhi<0.0) { TPhi += 2.*TMath::Pi(); }
    TPhi *= 180./TMath::Pi();
  */
  
  mDCAGlobal->Fill( track->gDCAxy(), 1.); //using for DCAxyz global
  mNhits->Fill(track->nHits(), 1.);
  mP->Fill(track->p().Mag(), 1.);
  mPt->Fill(track->pt(), 1.);
  mPtVsNsigmaPion->Fill(track->pt(), track->nSigmaPion(), 1.);
  mPtVsNsigmaKaon->Fill(track->pt(), track->nSigmaKaon(), 1.);
  mPtVsNsigmaProton->Fill(track->pt(), track->nSigmaProton(), 1.);
  mPvsDedx->Fill( fabs(track->p().Mag()), track->dEdx()*1000000, 1.);
  mPseudoRapidity->Fill(track->eta(), 1.);
  mPvsMassSqr->Fill(track->p().Mag(), track->massSqr(), 1.);
  mPvsInvBeta->Fill( fabs(track->p().Mag()), (1./track->beta()), 1.);
  mPtVsEta->Fill(track->pt(), track->eta(), 1.);
#ifdef TPC_DNDX
  mPvsDndx->Fill(track->p().Mag(), track->dNdx()*1000000, 1.);
  mPtVsDndxNsigmaPion->Fill(track->Pt(), track->DndxNSigmaPion(), 1.);
  mPtVsDndxNsigmaKaon->Fill(track->Pt(), track->DndxNSigmaKaon(), 1.);
  mPtVsDndxNsigmaProton->Fill(track->Pt(), track->DndxNSigmaProton(), 1.);
#endif
}


