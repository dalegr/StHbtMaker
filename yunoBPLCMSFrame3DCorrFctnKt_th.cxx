#include "yunoBPLCMSFrame3DCorrFctnKt_th.h"

#ifdef __ROOT__
ClassImp(yunoBPLCMSFrame3DCorrFctnKt_th)
#endif

  //_________________
yunoBPLCMSFrame3DCorrFctnKt_th::yunoBPLCMSFrame3DCorrFctnKt_th(char *title,
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
yunoBPLCMSFrame3DCorrFctnKt_th::~yunoBPLCMSFrame3DCorrFctnKt_th() {
  for (int i = 0; i < mNumberKt; i++) {
    for (int j = 0; j < mNumberRp; j++) {
      delete mNumerator[i][j];
      delete mDenominator[i][j];
      delete mQinvHisto[i][j];
    }
  }
}

//_________________
void yunoBPLCMSFrame3DCorrFctnKt_th::writeOutHistos() {

  for(int i=0; i<mNumberKt; i++) {
    for(int j = 0; j < mNumberRp; j++) {
      mNumerator[i][j]->Write();
      mDenominator[i][j]->Write();
      mQinvHisto[i][j]->Write();
    }
  }
}

//_________________
TList* yunoBPLCMSFrame3DCorrFctnKt_th::getOutputList() {
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
void yunoBPLCMSFrame3DCorrFctnKt_th::finish() {

  //Just making the qInv weight correction
  /*
     for(int i=0; i<mNumberKt; i++) {
     for(int j = 0; j < mNumberRp; j++) {
     mQinvHisto[i][j]->Divide(&mDenominator[i][j]);
     }
     }
     */
}

//_________________
void yunoBPLCMSFrame3DCorrFctnKt_th::addRealPair(const StHbtPair* pair){

  if (mPairCut){
    if (!(mPairCut->pass(pair))) return;
  }

  int mIndexKt = (int)(((fabs(pair->kT())-mKtMin)/mDeltaKt));
  int mIndexRp = getRpBin(pair);
  if ((mIndexKt>=0)&&(mIndexKt<mNumberKt) &&
      (mIndexRp>=0)&&(mIndexRp<mNumberRp)) {

    // get a pair of tracks from StHbtPair
    StHbtTrack *track1 = pair->track1()->track();
    StHbtTrack *track2 = pair->track2()->track();

    // constants
    double hc = 0.1973269718; // GeV*fm

    // first track
    float xfr1 = track1->emissionPointX();
    float yfr1 = track1->emissionPointY();
    float zfr1 = track1->emissionPointZ();
    float tfr1 = track1->emissionPointT();
    float E1   = sqrt(track1->ptot2() + track1->massSqr());
    float px1  = track1->p().x();
    float py1  = track1->p().y();
    float pz1  = track1->p().z();

    // second track
    float xfr2 = track2->emissionPointX();
    float yfr2 = track2->emissionPointY();
    float zfr2 = track2->emissionPointZ();
    float tfr2 = track2->emissionPointT();
    float E2   = sqrt(track2->ptot2() + track2->massSqr());
    float px2  = track2->p().x();
    float py2  = track2->p().y();
    float pz2  = track2->p().z();

    // create two TLorentzVectors and calculate weight of two particles
    TLorentzVector X1(xfr1, yfr1, zfr1, tfr1);
    TLorentzVector X2(xfr2, yfr2, zfr2, tfr2);

    TLorentzVector P1(px1, py1, pz1, E1);
    TLorentzVector P2(px2, py2, pz2, E2);

    TLorentzVector deltaX = X1 - X2;
    TLorentzVector deltaP = P1 - P2;

    double weight = 1.0 + cos(deltaP*deltaX/hc);
    double Qinv = pair->qInv();   
    double qOut = pair->qOutCMS();    
    double qSide = pair->qSideCMS();    
    double qLong = pair->qLongCMS();       

/*
    double Qinv = fabs(pair->qInv());
    double qOut = fabs(pair->qOutCMS());
    double qSide = fabs(pair->qSideCMS());
    double qLong = fabs(pair->qLongCMS());
    */
    /*    if (qLong < 0) {
      qOut *= -1.;
      qSide *=-1.;
      qLong *= -1.;
    }

    */
    /*
    cout << "weight = " << weight << "\n"
	 << "Qinv = " << Qinv << "\n" 
	 << "qOut = " << qOut << "\n"
	 << "qSide = " << qSide << "\n"
	 << "qLong = " << qLong << endl;
    /*
       std::cout << "real pair" << std::endl;

       std::cout << "angle = " << angle
       << " mRpAngle = " << mRpAngle
       << " angleDifference = " << angleDifference
       << " rpIndex = " << mIndexRp
       << std::endl;
       */
    mNumerator[mIndexKt][mIndexRp]->Fill(qOut,qSide,qLong,weight);
    mDenominator[mIndexKt][mIndexRp]->Fill(qOut,qSide,qLong);
    mQinvHisto[mIndexKt][mIndexRp]->Fill(qOut,qSide,qLong,Qinv);
  }
}

//_________________
void yunoBPLCMSFrame3DCorrFctnKt_th::addMixedPair(const StHbtPair* pair){

  /* NO-OP */
}
void yunoBPLCMSFrame3DCorrFctnKt_th::eventBegin(const StHbtEvent *event) { mHbtEvent =(StHbtEvent*)event; }

int yunoBPLCMSFrame3DCorrFctnKt_th::getRpBin(const StHbtPair* pair) {

  // Get pair angle, put it between 0 and 360
  double pxTotal = pair->fourMomentumSum().X();
  double pyTotal = pair->fourMomentumSum().Y();
  angle = atan2(pyTotal,pxTotal);
  if (angle < 0) angle += 2*PI;

  int rpIndex = (angle - mRpMin)/mDeltaRp;

  return rpIndex;
}




//_________________
StHbtString yunoBPLCMSFrame3DCorrFctnKt_th::report() {

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

