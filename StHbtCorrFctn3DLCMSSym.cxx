/**
 * Description: 3D correlation function of identical particles
 * in Bertsch-Pratt coordinate system
 */

/// StHbtMaker headers
#include "StHbtCorrFctn3DLCMSSym.h"
#include "StHbtPairCut.h"

/// ROOT headers
#include "TH3F.h"
#include "TString.h"

#ifdef __ROOT__
ClassImp(StHbtCorrFctn3DLCMSSym);
#endif

//____________________________
StHbtCorrFctn3DLCMSSym::StHbtCorrFctn3DLCMSSym(const char* title,
					       const int nbins,
					       const float QHi):
  StHbtCorrFctn(),
  mNumerator(nullptr),
  mDenominator(nullptr),
  mNumeratorW(nullptr),
  mDenominatorW(nullptr),
  mUseLCMS(true) {
  /// Default constructor
  TString hist_title = TString::Format("%s; q_{out} (GeV/c); q_{side} (GeV/c); q_{long} (GeV/c)", title);
  
  /// set up numerator
  mNumerator = new TH3F(TString("Num") + title,
			hist_title,
			nbins, -QHi, QHi,
			nbins, -QHi, QHi,
			nbins, -QHi, QHi);
  /// set up denominator
  mDenominator = new TH3F(TString("Den") + title,
                          hist_title,
                          nbins, -QHi, QHi,
                          nbins, -QHi, QHi,
                          nbins, -QHi, QHi);
  
  /// Weighted by qinv histos
  /// set up numerator
  mNumeratorW = new TH3F(TString("NumWqinv") + title,
                         hist_title,
                         nbins, -QHi, QHi,
                         nbins, -QHi, QHi,
                         nbins, -QHi, QHi);

  /// Set up denominator
  mDenominatorW = new TH3F(TString("DenWqinv") + title,
                           hist_title,
                           nbins, -QHi, QHi,
                           nbins, -QHi, QHi,
                           nbins, -QHi, QHi);
  
  /// Enable error bar calculation
  mNumerator->Sumw2();
  mDenominator->Sumw2();
  mNumeratorW->Sumw2();
  mDenominatorW->Sumw2();
}

//_________________
StHbtCorrFctn3DLCMSSym::StHbtCorrFctn3DLCMSSym(const StHbtCorrFctn3DLCMSSym& aCorrFctn):
  StHbtCorrFctn(aCorrFctn),
  mNumerator( new TH3F(*aCorrFctn.mNumerator) ),
  mDenominator( new TH3F(*aCorrFctn.mDenominator) ),
  mNumeratorW( new TH3F(*aCorrFctn.mNumeratorW) ),
  mDenominatorW( new TH3F(*aCorrFctn.mDenominatorW) ),
  mUseLCMS( aCorrFctn.mUseLCMS ) {
  /// Copy constructor
  mNumerator->Sumw2();
  mDenominator->Sumw2();
  mNumeratorW->Sumw2();
  mDenominatorW->Sumw2();
}

//_________________
StHbtCorrFctn3DLCMSSym& StHbtCorrFctn3DLCMSSym::operator=(const StHbtCorrFctn3DLCMSSym& aCorrFctn) {
  /// Assignment operator
  if ( this != &aCorrFctn) {

    StHbtCorrFctn::operator=(aCorrFctn);

    *mNumerator = *aCorrFctn.mNumerator;
    *mDenominator = *aCorrFctn.mDenominator;
    *mNumeratorW = *aCorrFctn.mNumeratorW;
    *mDenominatorW = *aCorrFctn.mDenominatorW;
    
    mUseLCMS = aCorrFctn.mUseLCMS;

    mNumerator->Sumw2();
    mDenominator->Sumw2();
    mNumeratorW->Sumw2();
    mDenominatorW->Sumw2();
  }

  return *this;
}

//_________________
StHbtCorrFctn3DLCMSSym::~StHbtCorrFctn3DLCMSSym() {
  /// Destructor
  delete mNumerator;
  delete mDenominator;
  delete mNumeratorW;
  delete mDenominatorW;
}

//_________________
void StHbtCorrFctn3DLCMSSym::writeOutHistos() {
  /// Write out all histograms to file
  mNumerator->Write();
  mDenominator->Write();
  mNumeratorW->Write();
  mDenominatorW->Write();
}

//_________________
TList* StHbtCorrFctn3DLCMSSym::getOutputList() {
  /// Prepare the list of objects to be written to the output
  TList *outputList = new TList();

  outputList->Add(mNumerator);
  outputList->Add(mDenominator);
  outputList->Add(mNumeratorW);
  outputList->Add(mDenominatorW);

  return outputList;
}

//_________________
void StHbtCorrFctn3DLCMSSym::finish() {
  /// Here is where we should normalize, fit, etc...
}

//_________________
StHbtString StHbtCorrFctn3DLCMSSym::report() {
  /// Construct the report
  TString report = "LCMS Frame Bertsch-Pratt 3D Correlation Function Report:\n";
  report += TString::Format("Number of entries in numerator:\t%E\n", mNumerator->GetEntries());
  report += TString::Format("Number of entries in denominator:\t%E\n", mDenominator->GetEntries());

  if (mPairCut) {
    report += "Here is the PairCut specific to this CorrFctn\n";
    report += mPairCut->report();
  }
  else {
    report += "No PairCut specific to this CorrFctn\n";
  }

  return StHbtString( (const char *)report );
}

//_________________
void StHbtCorrFctn3DLCMSSym::addRealPair(const StHbtPair* pair) {
  /// Perform operations on real pairs
  if ( mPairCut && !mPairCut->pass( pair ) ) {
    return;
  }

  if (mUseLCMS) {
    
    mNumerator->Fill( pair->qOutCMS(), pair->qSideCMS(), pair->qLongCMS(), 1.0);
    mNumeratorW->Fill( pair->qOutCMS(), pair->qSideCMS(), pair->qLongCMS(), pair->qInv());
  }
  else {
    mNumerator->Fill( pair->qOutPf(), pair->qSidePf(), pair->qLongPf(), 1.0);
    mNumeratorW->Fill( pair->qOutPf(), pair->qSidePf(), pair->qLongPf(), pair->qInv());
  }
}

//____________________________
void StHbtCorrFctn3DLCMSSym::addMixedPair(const StHbtPair* pair) {
  
  /// Perform operations on mixed pairs
  if ( mPairCut && !mPairCut->pass(pair) ) {
    return;
  }

  if (mUseLCMS) {
    mDenominator->Fill( pair->qOutCMS(), pair->qSideCMS(), pair->qLongCMS(), 1.0 );
    mDenominatorW->Fill( pair->qOutCMS(), pair->qSideCMS(), pair->qLongCMS(), pair->qInv());
  }
  else {
    mDenominator->Fill( pair->qOutPf(), pair->qSidePf(), pair->qLongPf(), 1.0 );
    mDenominatorW->Fill( pair->qOutPf(), pair->qSidePf(), pair->qLongPf(), pair->qInv());
  }
}
