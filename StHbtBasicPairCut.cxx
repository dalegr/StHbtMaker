#include "StHbtBasicPairCut.h"

#ifdef __ROOT__
ClassImp(StHbtBasicPairCut)
#endif

//_________________
StHbtBasicPairCut::StHbtBasicPairCut() {
  mQuality[0] = -1.; mQuality[1] = +1.;
  mKt[0] = -1e9; mKt[1]= +1e9;
  mPt[0] = -1e9; mPt[1]= +1e9;
  mOpeningAngle[0] = -1e9; mOpeningAngle[1]= +1e9;
  mRapidity[0] = -1e9; mRapidity[1]= +1e9;
  mEta[0] = -3.5; mEta[1]= 3.5;
  mQinv[0] = -0.01; mQinv[1]= 1e9;
  mMinv[0] = -1e9; mMinv[1]= +1e9;
  mEntranceSeparation[0] = -1e9; mEntranceSeparation[1]= +1e9;
  mAngleToPrimaryVertex[0] = -1e9; mAngleToPrimaryVertex[1]= 1e9;
  mFracOfMergedRow[0] = -1e9; mFracOfMergedRow[1]=+1e9;
  mClosestRowAtDCA[0] = -1e9; mClosestRowAtDCA[1]=+1e9;
  mWeightedAvSep[0] = -1e9; mWeightedAvSep[1]=+1e9;
  mAverageSeparation[0] = -1e9; mAverageSeparation[1]=+1e9;
  mRValueLo = 0.;
  mNPairsPassed = mNPairsFailed = 0;
}

//_________________
StHbtBasicPairCut::StHbtBasicPairCut(const StHbtBasicPairCut& c) : StHbtPairCut(c) {

#ifdef STHBTDEBUG
  cout << " StHbtBasicPairCut::StHbtBasicPairCut(const StHbtBasicPairCut& c) " << endl;
#endif

  mNPairsPassed = mNPairsFailed = 0;
  mPrimaryVertex = c.mPrimaryVertex;
  mQuality[0] = c.mQuality[0];
  mQuality[1] = c.mQuality[1];
  mKt[0] = c.mKt[0];
  mKt[1] = c.mKt[1];
  mPt[0] = c.mPt[0];
  mPt[1] = c.mPt[1];
  mOpeningAngle[0] = c.mOpeningAngle[0];
  mOpeningAngle[1] = c.mOpeningAngle[1];
  mQinv[0] = c.mQinv[0];
  mQinv[1] = c.mQinv[1];
  mMinv[0] = c.mMinv[0];
  mMinv[1] = c.mMinv[1];
  mRapidity[0] = c.mRapidity[0];
  mRapidity[1] = c.mRapidity[1];
  mEta[0] = c.mEta[0];
  mEta[1] = c.mEta[1];
  mEntranceSeparation[0] = c.mEntranceSeparation[0];
  mEntranceSeparation[1] = c.mEntranceSeparation[1];
  mAngleToPrimaryVertex[0] = c.mAngleToPrimaryVertex[0];
  mAngleToPrimaryVertex[1] = c.mAngleToPrimaryVertex[1];
  mFracOfMergedRow[0] = c.mFracOfMergedRow[0];
  mFracOfMergedRow[1] = c.mFracOfMergedRow[1];
  mClosestRowAtDCA[0] = c.mClosestRowAtDCA[0]; 
  mClosestRowAtDCA[1] = c.mClosestRowAtDCA[1];
  mWeightedAvSep[0] = c.mWeightedAvSep[0];
  mWeightedAvSep[1] = c.mWeightedAvSep[1];
  mAverageSeparation[0] = c.mAverageSeparation[0];
  mAverageSeparation[1] = c.mAverageSeparation[1];
  mRValueLo = c.mRValueLo;
}

//_________________
StHbtBasicPairCut::~StHbtBasicPairCut(){
 /* no-op */
}  

//__________________
bool StHbtBasicPairCut::pass(const StHbtPair* pair){

#ifdef STHBTDEBUG
  std::cout << "--StHbtBasicPairCut--" << std::endl
	    << "Quality       = " << pair->quality() << std::endl
	    << "kT            = " << pair->kT() << std::endl
	    << "pT            = " << pair->pT() << std::endl
	    << "Opening angle = " << pair->OpeningAngle() << std::endl
	    << "Rapidity      = " << pair->rapidity() 
	    << std::endl
	    << "Pseudorapity    = " << pair->eta() 
	    << std::endl
	    << "Qinv            = " << pair->qInv() << std::endl
	    << "Minv            = " << pair->mInv() << std::endl
	    << "TpcEntranceSep  = " << pair->NominalTpcEntranceSeparation() 
	    << std::endl
	    << "FracOfMergedRow = " << pair->getFracOfMergedRow() << std::endl
	    << "ClosestRowAtDCA = " << pair->getClosestRowAtDCA() << std::endl
	    << "WeightedAvSep   = " << pair->getWeightedAvSep() << std::endl
	    << "AverageSep      = " << pair->NominalTpcAverageSeparation() 
	    << "rValue          = " << pair->rValue()
	    << std::endl << std::endl;
#endif

  bool mGoodPair = ( (pair->quality() >= mQuality[0]) &&
		     (pair->quality() <= mQuality[1]) &&
		     (pair->kT() >= mKt[0]) && 
		     (pair->kT() <= mKt[1]) &&
		     (pair->pT() >= mPt[0]) && 
		     (pair->pT() <= mPt[1]) &&
		     (pair->openingAngle() >= mOpeningAngle[0]) && 
		     (pair->openingAngle() <= mOpeningAngle[1]) &&
		     (pair->rap() >= mRapidity[0]) && 
		     (pair->rap() <= mRapidity[1]) && 
		     (pair->eta() >= mEta[0]) && 
		     (pair->eta() <= mEta[1]) &&
		     (fabs(pair->qInv()) >= mQinv[0]) && 
		     (fabs(pair->qInv()) <= mQinv[1]) &&
		     (fabs(pair->mInv()) >= mMinv[0]) && 
		     (fabs(pair->mInv()) <= mMinv[1]) &&
		     (pair->nominalTpcEntranceSeparation() >= mEntranceSeparation[0]) &&
		     (pair->nominalTpcEntranceSeparation() <= mEntranceSeparation[1]) &&
		     (pair->fractionOfMergedRow() >= mFracOfMergedRow[0]) &&
		     (pair->fractionOfMergedRow() <= mFracOfMergedRow[1]) &&
		     (pair->closestRowAtDCA() >= mClosestRowAtDCA[0]) &&
		     (pair->closestRowAtDCA() <= mClosestRowAtDCA[1]) &&
		     (pair->weightedAvSep() >= mWeightedAvSep[0]) &&
		     (pair->weightedAvSep() <= mWeightedAvSep[1]) &&
		     (pair->nominalTpcAverageSeparation() >= mAverageSeparation[0]) &&
		     (pair->nominalTpcAverageSeparation() <= mAverageSeparation[1]) &&
		     (pair->rValue() >= mRValueLo)
		   );

#ifdef STHBTDEBUG
  if(mGoodPair)
    std::cout << "Pair cut passed!" << std::endl;
  else
    std::cout << "Pair cut failed!" << std::endl;
#endif

  mGoodPair ? mNPairsPassed++ : mNPairsFailed++;
  
  return mGoodPair;
}

//__________________
#include <sstream>
StHbtString StHbtBasicPairCut::report(){

  TString report;
#define PRINTVAR(var) Form("%.4e <= " #var " <= %.4e\n", var[0], var[1])

  report = "\n-- StHbtBasicPairCut --\n";
  report += PRINTVAR(mQuality);
  report += PRINTVAR(mKt);
  report += PRINTVAR(mPt);
  report += PRINTVAR(mOpeningAngle);
  report += PRINTVAR(mRapidity);
  report += PRINTVAR(mEta);
  report += PRINTVAR(mQinv);
  report += PRINTVAR(mMinv);
  report += PRINTVAR(mEntranceSeparation);
  report += PRINTVAR(mAverageSeparation);
  report += Form("rValue >= %f\n", mRValueLo);
  report += Form("NPairsPassed = %li\nNPairsFailed = %li\n", mNPairsPassed, mNPairsFailed);
#undef PRINTVAR

  return StHbtString((const char *)report);
}

//_________________
TList *StHbtBasicPairCut::listSettings() {
  
  /// Return a list of settings in a writable form
  TList *settings_list = new TList();

#define NEWOBJ(var) new TObjString( TString::Format( "StHbtBasicPairCut." #var ".min=%f", var[0] ) ), \
                    new TObjString( TString::Format( "StHbtBasicPairCut." #var ".max=%f", var[1] ) )

  settings_list->AddVector(NEWOBJ(mQuality),
                           NEWOBJ(mKt),
                           NEWOBJ(mPt),
                           NEWOBJ(mOpeningAngle),
                           NEWOBJ(mRapidity),
                           NEWOBJ(mEta),
                           NEWOBJ(mQinv),
                           NEWOBJ(mMinv),
                           NEWOBJ(mEntranceSeparation),
                           NEWOBJ(mAverageSeparation),
                           new TObjString( TString::Format( "StHbtBasicPairCut.mRValueLo=%f", mRValueLo ) ),
                           NULL);

  return settings_list;
}
