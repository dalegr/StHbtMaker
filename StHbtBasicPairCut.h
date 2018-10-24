#ifndef StHbtBasicPairCut_h
#define StHbtBasicPairCut_h

#include "StHbtPairCut.h"
#include "StHbtTypes.h"
#include "SystemOfUnits.h"
#include <string>
#include <cstdio>

class StHbtPair;

//_________________
class StHbtBasicPairCut : public StHbtPairCut {
 public:
  StHbtBasicPairCut();
  StHbtBasicPairCut(const StHbtBasicPairCut&);
  ~StHbtBasicPairCut();

  virtual TList *listSettings();
  virtual bool pass(const StHbtPair*);
  void setQuality(const float& lo, const float& hi );
  void setKt(const float& lo, const float& hi);
  void setPt(const float& lo, const float& hi);
  void setOpeningAngle(const float& lo, const float& hi);
  void setEntranceSeparation(const float& lo, const float& hi);
  void setRapidity(const float& lo, const float& hi);
  void setEta(const float& lo, const float& hi);
  void setQinv(const float& lo, const float& hi);
  void setMinv(const float& lo, const float& hi);
  void setAngleToPrimaryVertex(const float& lo, const float& hi);
  void setFracOfMergedRow(const float& lo, const float& hi);
  void setClosestRowAtDCA(const float& lo, const float& hi);
  void setWeightedAvSep(const float& lo, const float& hi);
  void setAverageSeparation(const float& lo, const float& hi);
  void setRValue(const float& lo);
  virtual StHbtString report();

 private:

  TVector3 mPrimaryVertex;
  float mFracOfMergedRow[2];

  double mClosestRowAtDCA[2];
  double mWeightedAvSep[2];
  float mQuality[2];
  float mKt[2];
  float mPt[2];
  float mRapidity[2];
  float mEta[2];
  float mQinv[2];
  float mMinv[2];
  float mOpeningAngle[2];
  float mAngleToPrimaryVertex[2];
  float mEntranceSeparation[2];
  float mAverageSeparation[2];
  float mRValueLo;
  long mNPairsPassed;
  long mNPairsFailed;

 protected:

#ifdef __ROOT__
  ClassDef(StHbtBasicPairCut, 1)
#endif
};

inline void StHbtBasicPairCut::setQuality(const float& lo, const float& hi) 
{ mQuality[0]=lo; mQuality[1]=hi; }
inline void StHbtBasicPairCut::setKt(const float& lo, const float& hi) 
{ mKt[0]=lo; mKt[1]=hi; }
inline void StHbtBasicPairCut::setPt(const float& lo, const float& hi) 
{ mPt[0]=lo; mPt[1]=hi; }
inline void StHbtBasicPairCut::setOpeningAngle(const float& lo, const float& hi) 
{ mOpeningAngle[0]=lo; mOpeningAngle[1]=hi; }
inline void StHbtBasicPairCut::setRapidity(const float& lo, const float& hi) 
{ mRapidity[0]=lo; mRapidity[1]=hi; }
inline void StHbtBasicPairCut::setEta(const float& lo, const float& hi) 
{ mEta[0]=lo; mEta[1]=hi; }
inline void StHbtBasicPairCut::setQinv(const float& lo, const float& hi) 
{ mQinv[0]=lo; mQinv[1]=hi; }
inline void StHbtBasicPairCut::setMinv(const float& lo, const float& hi) 
{ mMinv[0]=lo; mMinv[1]=hi; }
inline void StHbtBasicPairCut::setEntranceSeparation(const float& lo, const float& hi) 
{ mEntranceSeparation[0]=lo; mEntranceSeparation[1]=hi; }
inline void StHbtBasicPairCut::setAngleToPrimaryVertex(const float& lo, const float& hi) 
{ mAngleToPrimaryVertex[0]=lo; mAngleToPrimaryVertex[1]=hi; }
inline void StHbtBasicPairCut::setFracOfMergedRow(const float& lo, const float& hi)
{mFracOfMergedRow[0]=lo; mFracOfMergedRow[1]=hi;}
inline void StHbtBasicPairCut::setClosestRowAtDCA(const float& lo, const float& hi)
{mClosestRowAtDCA[0]=lo; mClosestRowAtDCA[1]=hi;}
inline void StHbtBasicPairCut::setWeightedAvSep(const float& lo, const float& hi)
{mWeightedAvSep[0]=lo; mWeightedAvSep[1]=hi;}
inline void StHbtBasicPairCut::setRValue(const float& lo)
{mRValueLo = lo;}
inline void StHbtBasicPairCut::setAverageSeparation(const float& lo, const float& hi) {
  mAverageSeparation[0]=lo; mAverageSeparation[1]=hi; }

#endif
