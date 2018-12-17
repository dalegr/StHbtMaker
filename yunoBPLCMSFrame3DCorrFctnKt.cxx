#include "yunoBPLCMSFrame3DCorrFctnKt.h"

#ifdef __ROOT__
ClassImp(yunoBPLCMSFrame3DCorrFctnKt)
#endif

//_________________
yunoBPLCMSFrame3DCorrFctnKt::yunoBPLCMSFrame3DCorrFctnKt(char *title,
							 const int &nbins, const float &QLo, const float &QHi,
							 const int& ktBin, const float& KtLo, const float& KtHi,
							 const int& rpBin, const float& rpLo, const float& rpHi) {
  
  // set some stuff...

  mNumberKt = ktBin;
  mKtMin = KtLo;
  mKtMax = KtHi;
  mDeltaKt = (mKtMax-mKtMin)/mNumberKt;

  mNumberRp = rpBin;
  mRpMin = rpLo;
  mRpMax = rpHi;
  mDeltaRp = (mRpMax-mRpMin)/mNumberRp;

  
  stringstream TitNum,TitDen,TitQinv,TitCurrent;
  TitNum.str("");TitDen.str("");TitQinv.str("");TitCurrent.str("");
  TitNum<<title<<"_Num";
  TitDen<<title<<"_Den";
  TitQinv<<title<<"_Qinv";

  TString hist_title = TString::Format("%s; q_{out} (GeV/c); q_{side} (GeV/c); q_{long} (GeV/c)", title);

  //Histogram loop
  
  for(int i=0; i<mNumberKt; i++) {
    for(int j = 0; j < mNumberRp; j++) {
    
      TitCurrent.str("");
      TitCurrent << TitNum.str() << "_kt_" << i << "_rp_" << j;
      mNumerator[i][j] = new TH3F(TitCurrent.str().c_str(),
				  hist_title,
				  nbins, QLo, QHi,
				  nbins, QLo, QHi,
				  nbins, QLo, QHi);
      mNumerator[i][j]->Sumw2();

      TitCurrent.str("");
      TitCurrent << TitDen.str()<< "_kt_" << i << "_rp_" << j;
      mDenominator[i][j] = new TH3F(TitCurrent.str().c_str(),
				    hist_title,
				    nbins, QLo, QHi,
				    nbins, QLo, QHi,
				    nbins, QLo, QHi);
      mDenominator[i][j]->Sumw2();

      TitCurrent.str("");
      TitCurrent << TitQinv.str()<< "_kt_" << i << "_rp_" << j;
      mQinvHisto[i][j] = new TH3F(TitCurrent.str().c_str(),
				  hist_title,
				  nbins, QLo, QHi,
				  nbins, QLo, QHi,
				  nbins, QLo, QHi);
      mQinvHisto[i][j]->Sumw2();
    }
  }
}

//_________________
yunoBPLCMSFrame3DCorrFctnKt::~yunoBPLCMSFrame3DCorrFctnKt() {
  for (int i = 0; i < mNumberKt; i++) {
    for (int j = 0; j < mNumberRp; j++) {
      delete mNumerator[i][j];
      delete mDenominator[i][j];
      delete mQinvHisto[i][j];
    }
  }
}

//_________________
void yunoBPLCMSFrame3DCorrFctnKt::writeOutHistos() {

  for(int i=0; i<mNumberKt; i++) {
    for(int j = 0; j < mNumberRp; j++) {
      mNumerator[i][j]->Write();
      mDenominator[i][j]->Write();
      mQinvHisto[i][j]->Write();
    }
  }
}

//_________________
TList* yunoBPLCMSFrame3DCorrFctnKt::getOutputList() {
  /// Prepare the list of objects to be written to the output
  TList *outputList = new TList();
  for (int i = 0; i < mNumberKt; i++) {
    for (int j = 0; j < mNumberRp; j++) {

      outputList->Add(mNumerator[i][j]);
      outputList->Add(mDenominator[i][j]);
      outputList->Add(mQinvHisto[i][j]);
    }
  }
  return outputList;
}

//_________________
void yunoBPLCMSFrame3DCorrFctnKt::finish() { }

//_________________
void yunoBPLCMSFrame3DCorrFctnKt::addRealPair(const StHbtPair* pair){

  if (mPairCut)
    {
      if (!(mPairCut->pass(pair))) return;
    }

  int mIndexKt = (int)(((pair->kT()-mKtMin)/mDeltaKt));
  int mIndexRp = getRpBin(pair);
  if ((mIndexKt>=0)&&(mIndexKt<mNumberKt)
      &&
      (mIndexRp>=0)&&(mIndexRp<mNumberRp)) {


    double qOut, qSide, qLong; 
    if (mRpMin < 0) {
      qOut = fabs(pair->qOutCMS());
      qSide = fabs(pair->qSideCMS());
      qLong = fabs(pair->qLongCMS());
    }
    else {
      qOut = pair->qOutCMS();
      qSide = pair->qSideCMS();
      qLong = pair->qLongCMS();
    }
    mNumerator[mIndexKt][mIndexRp]->Fill(qOut,qSide,qLong);
  }
}

//_________________
void yunoBPLCMSFrame3DCorrFctnKt::addMixedPair(const StHbtPair* pair){

  if (mPairCut)
    {
      if (!(mPairCut->pass(pair))) return;
    }

  int mIndexKt = (int)(((fabs(pair->kT())-mKtMin)/mDeltaKt));
  int mIndexRp = getRpBin(pair);
  if ((mIndexKt>=0)&&(mIndexKt<mNumberKt)
      &&
      (mIndexRp>=0)&&(mIndexRp<mNumberRp)) {

    
    double Qinv = fabs(pair->qInv());
    double qOut, qSide, qLong; 
    if (mRpMin < 0) {
      qOut = fabs(pair->qOutCMS());
      qSide = fabs(pair->qSideCMS());
      qLong = fabs(pair->qLongCMS());
    }
    else {
      qOut = pair->qOutCMS();
      qSide = pair->qSideCMS();
      qLong = pair->qLongCMS();
    }
    
    mDenominator[mIndexKt][mIndexRp]->Fill(qOut,qSide,qLong,1.0);
    mQinvHisto[mIndexKt][mIndexRp]->Fill(qOut,qSide,qLong,Qinv);
  }
}
void yunoBPLCMSFrame3DCorrFctnKt::eventBegin(const StHbtEvent *event) { mHbtEvent =(StHbtEvent*)event; }

int yunoBPLCMSFrame3DCorrFctnKt::getRpBin(const StHbtPair* pair) {

  angle = pair->phi();
  mRpAngle = mHbtEvent->eventPlaneAngle();
   
  angleDifference = angle - mRpAngle;
  if (angleDifference < 0) angleDifference +=2*PI;

  int rpIndex = (angleDifference - mRpMin)/mDeltaRp;
  
  return rpIndex;
}




//_________________
StHbtString yunoBPLCMSFrame3DCorrFctnKt::report() {

  int mNumeratorEntries=0;
  int mDenominatorEntries=0;
  int mQinvHistoEntries=0;

  for (int i=0; i<mNumberKt; i++){
    for(int j = 0; j < mNumberRp; j++) {
      mNumeratorEntries += (int)mNumerator[i][j]->GetEntries();
      mDenominatorEntries += (int)mDenominator[i][j]->GetEntries();
      mQinvHistoEntries += (int)mQinvHisto[i][j]->GetEntries();
    }
  }
    
  string stemp = "yuno LCMS Frame Bertsch-Pratt 3D Correlation Function Report:\n";
  char ctemp[100];
  for(int i=0; i<mNumberKt; i++) {
    for(int j = 0; j < mNumberRp; j++) {
      sprintf(ctemp,"Number of entries in numerator:\t%E\n",mNumerator[i][j]->GetEntries());
      stemp += ctemp;
      sprintf(ctemp,"Number of entries in denominator:\t%E\n",mDenominator[i][j]->GetEntries());
      stemp += ctemp;
      sprintf(ctemp,"Number of entries in Qinv histo:\t%E\n",mQinvHisto[i][j]->GetEntries());
      stemp += ctemp;
    }
  }
  StHbtString returnThis = stemp;
  return returnThis;
}

