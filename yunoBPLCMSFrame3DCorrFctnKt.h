#ifndef yunoBPLCMSFrame3DCorrFctnKt_hh
#define yunoBPLCMSFrame3DCorrFctnKt_hh

#include "StHbtCorrFctn.h"
#include "StHbtPairCut.h"

/// ROOT headers
#include <TH3F.h>
#include <TString.h>
#include <sstream>
#include <cstdio>


using namespace std;

#define PI 3.14159265359
//_________________
class yunoBPLCMSFrame3DCorrFctnKt : public StHbtCorrFctn {

 public:
  yunoBPLCMSFrame3DCorrFctnKt(char *title, 
			      const int &nbins, const float &Qlo, const float &Qhi,
			      const int& ktBin=10, const float& KtLo=0.05, const float& KtHi=1.05,
			      const int& rpBin=12, const float& rpLo=0, const float& rpHi=2*PI);

  virtual ~yunoBPLCMSFrame3DCorrFctnKt();

  virtual StHbtString report();
  virtual void addRealPair(const StHbtPair*);
  virtual void addMixedPair(const StHbtPair*);

  virtual void finish();
  void writeOutHistos();

  int getRpBin(const StHbtPair*);
  virtual void eventBegin(const StHbtEvent*);

  virtual TList* getOutputList();

  StHbtEvent *mHbtEvent;
 private:

  TH3F *mNumerator[10][12];
  TH3F *mDenominator[10][12];
  TH3F *mQinvHisto[10][12];

  //for the kt binning:
  int mNumberKt, mNumberRp;
  float mKtMin, mRpMin;
  float mKtMax, mRpMax;

  int* mIndexKt, mIndexRp;
  float mDeltaKt, mDeltaRp;

  double angle, mRpAngle, angleDifference;

#ifdef __ROOT__
  ClassDef(yunoBPLCMSFrame3DCorrFctnKt, 1)
#endif
    };
#endif
