#ifndef yunoBPLCMSFrame3DCorrFctnKt_th_hh
#define yunoBPLCMSFrame3DCorrFctnKt_th_hh

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
class yunoBPLCMSFrame3DCorrFctnKt_th : public StHbtCorrFctn {

 public:
  yunoBPLCMSFrame3DCorrFctnKt_th(char *title, 
                                 const int &nbins, const float &Qlo, const float &Qhi,
                                 const int &detector, /*east = 0, west = 1*/
                                 const int& ktBin=10, const float& KtLo=0.05, const float& KtHi=1.05,
                                 const int& rpBin=12, const float& rpLo=0, const float& rpHi=2*PI);

  virtual ~yunoBPLCMSFrame3DCorrFctnKt_th();

  virtual StHbtString report();
  virtual void addRealPair(const StHbtPair*);
  virtual void addMixedPair(const StHbtPair*);

  virtual void finish();
  void writeOutHistos();

  int getRpBin(const StHbtPair*);
  virtual void eventBegin(const StHbtEvent*);

  TH3F* numerator(int ktBin, int rpBin);
  TH3F* denominator(int ktBin, int rpBin);
  TH3F* qinvHisto(int ktBin, int rpBin);

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
  int mDetector;

  double angle, mRpAngle, angleDifference;

#ifdef __ROOT__
  ClassDef(yunoBPLCMSFrame3DCorrFctnKt_th, 1)
#endif
};

inline TH3F *yunoBPLCMSFrame3DCorrFctnKt_th::numerator(int ktBin, int rpBin)
{  return mNumerator[ktBin][rpBin]; }
inline TH3F *yunoBPLCMSFrame3DCorrFctnKt_th::denominator(int ktBin, int rpBin)
{  return mDenominator[ktBin][rpBin]; }
inline TH3F *yunoBPLCMSFrame3DCorrFctnKt_th::qinvHisto(int ktBin, int rpBin)
{  return mQinvHisto[ktBin][rpBin]; }
#endif
