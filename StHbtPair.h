/**
 * Author: Grigory Nigmatkulov
 * Date: September 9, 2018
 * Description:
 * The class describes a pair of StHbtParticle instances and allows various
 * relative 4-momentum quantities, such as, qInv, qOut, qSide and qLong in different
 * frames (CMS - center of mass of the experiment, LCMS - longitudinally co-moving
 * system, PF - pair frame), as well as, sum of 4-momenta, such as, invariant mass,
 * kT, mT and so on.
 * It also provides esitmations for two-particle effects, for instance, track-merging
 * and track-splitiing effects.
 **/

#ifndef StHbtPair_h
#define StHbtPair_h

/// C++ headers
#include <utility>

/// StHbtMaker headers
#include "StHbtParticle.h"
#include "StHbtTypes.h"

/// ROOT headers
#include "TVector3.h"
#include "TLorentzVector.h"
#include "TMath.h"

//_________________
class StHbtPair {

 public:
  /// Default constructor
  StHbtPair();
  /// Constructor with particles
  StHbtPair(StHbtParticle*, StHbtParticle*);
  /// Copy constructor
  StHbtPair(const StHbtPair& copy);
  /// Copy constructor
  StHbtPair& operator=(const StHbtPair& copy);
  /// Default destructor
  ~StHbtPair();

  /**
   * Getters
   **/
  
  StHbtParticle* track1() const                 { return mTrack1; }
  StHbtParticle* track2() const                 { return mTrack2; }

  TLorentzVector fourMomentumDiff() const
  { return ( mTrack1->fourMomentum() - mTrack2->fourMomentum() ); } 
  TLorentzVector fourMomentumSum() const
  { return ( mTrack1->fourMomentum() + mTrack2->fourMomentum() ); }
  double qInv() const                           { return (-1.)*fourMomentumDiff().M(); }
  double pT() const                             { return p().Perp(); }
  double kT()   const                           { return 0.5 * pT(); }
  double mInv() const                           { return fourMomentumSum().M(); }
  TVector3 momentum() const                     { return fourMomentumSum().Vect(); }
  TVector3 p() const                            { return momentum(); }
  double px() const                             { return p().X(); }
  double py() const                             { return p().Y(); }
  double pz() const                             { return p().Z(); }
  double ptot() const                           { return p().Mag(); }
  double ptot2() const                          { return p().Mag2(); }
  double energy() const                         { return fourMomentumSum().Energy(); }

  //Additional pair variables
  double rap() const                            { return fourMomentumSum().Rapidity(); }
  double rapidity() const                       { return rap(); }
  double emissionAngle() const;
  double eta() const                            { return fourMomentumSum().Eta(); }
  double pseudoRapidity() const                 { return eta(); }
  double phi() const                            { return fourMomentumSum().Phi(); }
  double deltaPhi() const                       { return ( mTrack1->phi() - mTrack2->phi() ); }
  double deltaEta() const                       { return ( mTrack1->eta() - mTrack2->eta() ); }
  double rValue() const
  { return TMath::Sqrt( deltaEta()*deltaEta() + deltaPhi()*deltaPhi() ); }

  // Bertsch-Pratt momentum components in Pair Frame - written by Bekele/Humanic
  double qSidePf() const;
  double qOutPf() const;
  double qLongPf() const;
   
  // Bertsch-Pratt momentum components in Local CMS (longitudinally comoving) frame
  // - written by Bekele/Humanic
  double qSideCMS() const;
  double qOutCMS() const;
  double qLongCMS() const;

  double dKSide() const     { if(mNonIdParNotCalculated) { calcNonIdPar(); } return mDKSide; }
  double dKOut() const      { if(mNonIdParNotCalculated) { calcNonIdPar(); } return mDKOut; }
  double dKLong() const     { if(mNonIdParNotCalculated) { calcNonIdPar(); } return mDKLong; }

  // Bertsch-Pratt momentum components in a longitudinally boosted frame
  // the argument is the beta of the longitudinal boost (default is 0.0, meaning lab frame)
  // - written by Bekele/Humanic
  double qSideBf(double beta=0.0) const;
  double qOutBf(double beta=0.0) const;
  double qLongBf(double beta=0.0) const;

  // Yano-Koonin-Podgoretskii Parametrisation 
  // source rest frame (usually lab frame)
  void qYKPCMS(double& qP, double& qT, double& q0) const ;
  // longitudinal comoving frame
  void qYKPLCMS(double& qP, double& qT, double& q0) const ;
  // pair rest frame
  void qYKPPF(double& qP, double& qT, double& q0) const ;

  double quality() const;

  /// The following two methods calculate the "nominal" separation of the tracks 
  /// at the inner field cage (EntranceSeparation) and when they exit the TPC,
  /// which may be at the outer field cage, or at the endcaps.
  /// "nominal" means that the tracks are assumed to start at (0,0,0).  Making this
  /// assumption is important for the Event Mixing-- it is not a mistake. - Mike Lisa
  double nominalTpcExitSeparation() const;
  double nominalTpcEntranceSeparation() const;
  double nominalTpcAverageSeparation() const;
  // adapted calculation of Entrance/Exit/Average Tpc separation to V0 daughters
  double tpcExitSeparationTrackV0Pos() const
  { return ( mTrack1->nominalTpcExitPoint() - mTrack2->tpcV0PosExitPoint() ).Mag(); }
  double tpcEntranceSeparationTrackV0Pos() const
  { return ( mTrack1->nominalTpcEntrancePoint() - mTrack2->tpcV0PosEntrancePoint() ).Mag(); }
  double tpcAverageSeparationTrackV0Pos() const; 

  double tpcExitSeparationTrackV0Neg() const
  { return ( mTrack1->nominalTpcExitPoint() - mTrack2->tpcV0NegExitPoint() ).Mag(); }
  double tpcEntranceSeparationTrackV0Neg() const
  { return ( mTrack1->nominalTpcEntrancePoint() - mTrack2->tpcV0NegEntrancePoint() ).Mag(); }
  double tpcAverageSeparationTrackV0Neg() const; 

  double tpcExitSeparationV0PosV0Pos() const
  { return ( mTrack1->tpcV0PosExitPoint() - mTrack2->tpcV0PosExitPoint() ).Mag(); }
  double tpcEntranceSeparationV0PosV0Pos() const
  { return ( mTrack1->tpcV0PosEntrancePoint() - mTrack2->tpcV0PosEntrancePoint() ).Mag(); }
  double tpcAverageSeparationV0PosV0Pos() const; 

  double tpcExitSeparationV0PosV0Neg() const
  { return ( mTrack1->tpcV0PosExitPoint() - mTrack2->tpcV0NegExitPoint() ).Mag(); }
  double tpcEntranceSeparationV0PosV0Neg() const
  { return ( mTrack1->tpcV0PosEntrancePoint() - mTrack2->tpcV0NegEntrancePoint() ).Mag(); }
  double tpcAverageSeparationV0PosV0Neg() const; 
 
  double tpcExitSeparationV0NegV0Pos() const
  { return (  mTrack1->tpcV0NegExitPoint() - mTrack2->tpcV0PosExitPoint() ).Mag(); }
  double tpcEntranceSeparationV0NegV0Pos() const
  { return ( mTrack1->tpcV0NegEntrancePoint() - mTrack2->tpcV0PosEntrancePoint() ).Mag(); }
  double tpcAverageSeparationV0NegV0Pos() const; 
  
  double tpcExitSeparationV0NegV0Neg() const
  { return ( mTrack1->tpcV0NegExitPoint() - mTrack2->tpcV0NegExitPoint() ).Mag(); }
  double tpcEntranceSeparationV0NegV0Neg() const
  { return ( mTrack1->tpcV0NegEntrancePoint() - mTrack2->tpcV0NegEntrancePoint() ).Mag(); }
  double tpcAverageSeparationV0NegV0Neg() const; 

  double pInv() const;
  double kStar() const           { if(mNonIdParNotCalculated) { calcNonIdPar(); } return mKStarCalc; }
  double kStarFlipped() const;
  double cvk() const             { if(mNonIdParNotCalculated) { calcNonIdPar(); } return mCVK; }
  double cvkFlipped() const;
  /// XY-plane rotation
  double qInvFlippedXY() const;
  double qInvRandomFlippedXY() const;
  /// Opposite-hemisphere rotation
  double qInvFlippedXYZ() const;
  double qInvRandomFlippedXYZ() const;

  double openingAngle() const
  { return TMath::RadToDeg() * ( mTrack1->p().Angle( mTrack2->p() ) ); }

  // Fabrice Private <<<
  double kStarSide() const       { if(mNonIdParNotCalculated) { calcNonIdPar(); } return mDKSide; }
  double kStarOut() const        { if(mNonIdParNotCalculated) { calcNonIdPar(); } return mDKOut; }
  double kStarLong() const       { if(mNonIdParNotCalculated) { calcNonIdPar(); } return mDKLong; }

  double electronPairProbability() const
  { return (mTrack1->track()->pidProbElectron()) * (mTrack2->track()->pidProbElectron()); }
  double pionPairProbability() const
  { return (mTrack1->track()->pidProbPion()) * (mTrack2->track()->pidProbPion()); }
  double kaonPairProbability() const
  { return (mTrack1->track()->pidProbKaon()) * (mTrack2->track()->pidProbKaon()); }
  double protonPairProbability() const
  { return (mTrack1->track()->pidProbProton()) * (mTrack2->track()->pidProbProton()); }
  double kaonPionPairProbability() const
  { return (mTrack1->track()->pidProbKaon()) * (mTrack2->track()->pidProbPion()); }

  double dcaInsideTpc() const;
  double quality2() const;

  double kStarGlobal() const
  { if(mNonIdParNotCalculatedGlobal) { calcNonIdParGlobal(); } return mKStarCalcGlobal; }
  double cvkGlobal() const
  { if(mNonIdParNotCalculatedGlobal) { calcNonIdParGlobal(); } return mCVKGlobal; }
  double kStarSideGlobal() const
  { if(mNonIdParNotCalculatedGlobal) { calcNonIdParGlobal(); } return mDKSideGlobal; }
  double kStarOutGlobal() const
  { if(mNonIdParNotCalculatedGlobal) { calcNonIdParGlobal(); } return mDKOutGlobal; }
  double kStarLongGlobal() const
  { if(mNonIdParNotCalculatedGlobal) { calcNonIdParGlobal(); } return mDKLongGlobal; }

  double fractionOfMergedRow() const
  { if(mMergingParNotCalculated) { calcMergingPar(); } return mFracOfMergedRow; }
  double closestRowAtDCA() const
  { if(mMergingParNotCalculated) { calcMergingPar(); } return mClosestRowAtDCA; }
  double weightedAvSep() const
  { if(mMergingParNotCalculated) { calcMergingPar(); } return mWeightedAvSep; }
  double fractionOfMergedRowTrkV0Pos() const
  { if(mMergingParNotCalculatedTrkV0Pos) { calcMergingParFctn( &mMergingParNotCalculatedTrkV0Pos,
							       mTrack1->z(), mTrack1->u(),
							       mTrack2->z(), mTrack2->u(),
							       mTrack1->sect(), mTrack2->sect(),
							       &mFracOfMergedRowTrkV0Pos,
							       &mClosestRowAtDCATrkV0Pos ); }
    return mFracOfMergedRowTrkV0Pos;
  }
  double closestRowAtDCATrkV0Pos() const
  { if(mMergingParNotCalculatedTrkV0Pos) { calcMergingParFctn( &mMergingParNotCalculatedTrkV0Pos,
							       mTrack1->z(), mTrack1->u(),
							       mTrack2->z(), mTrack2->u(),
							       mTrack1->sect(), mTrack2->sect(),
							       &mFracOfMergedRowTrkV0Pos,
							       &mClosestRowAtDCATrkV0Pos ); }
    return mClosestRowAtDCATrkV0Pos;
  }

  double fractionOfMergedRowTrkV0Neg() const
  { if(mMergingParNotCalculatedTrkV0Neg) { calcMergingParFctn( &mMergingParNotCalculatedTrkV0Neg,
							       mTrack1->z(), mTrack1->u(),
							       mTrack2->v0NegZ(), mTrack2->v0NegU(),
							       mTrack1->sect(), mTrack2->v0NegSect(),
							       &mFracOfMergedRowTrkV0Neg,
							       &mClosestRowAtDCATrkV0Neg ); }
    return mFracOfMergedRowTrkV0Neg;
  }
  double closestRowAtDCATrkV0Neg() const
  { if(mMergingParNotCalculatedTrkV0Neg) { calcMergingParFctn( &mMergingParNotCalculatedTrkV0Neg,
							       mTrack1->z(),  mTrack1->u(),
							       mTrack2->v0NegZ(), mTrack2->v0NegU(),
							       mTrack1->sect(), mTrack2->v0NegSect(),
							       &mFracOfMergedRowTrkV0Neg,
							       &mClosestRowAtDCATrkV0Neg ); }
    return mClosestRowAtDCATrkV0Neg;
  }

  double fractionOfMergedRowV0PosV0Neg() const
  { if(mMergingParNotCalculatedV0PosV0Neg) { calcMergingParFctn( &mMergingParNotCalculatedV0PosV0Neg,
								 mTrack1->z(), mTrack1->u(),
								 mTrack2->v0NegZ(),mTrack2->v0NegU(),
								 mTrack1->sect(), mTrack2->v0NegSect(),
								 &mFracOfMergedRowV0PosV0Neg,
								 &mClosestRowAtDCAV0PosV0Neg ); }
    return mFracOfMergedRowV0PosV0Neg;
  }
  double fractionOfMergedRowV0NegV0Pos() const
  { if(mMergingParNotCalculatedV0NegV0Pos) { calcMergingParFctn( &mMergingParNotCalculatedV0NegV0Pos,
								 mTrack1->v0NegZ(), mTrack1->v0NegU(),
								 mTrack2->z(), mTrack2->u(),
								 mTrack1->v0NegSect(), mTrack2->sect(),
								 &mFracOfMergedRowV0NegV0Pos,
								 &mClosestRowAtDCAV0NegV0Pos ); }
    return mFracOfMergedRowV0NegV0Pos;
  }
  double fractionOfMergedRowV0PosV0Pos() const
  { if(mMergingParNotCalculatedV0PosV0Pos) { calcMergingParFctn( &mMergingParNotCalculatedV0PosV0Pos,
								 mTrack1->z(), mTrack1->u(),
								 mTrack2->z(), mTrack2->u(),
								 mTrack1->sect(), mTrack2->sect(),
								 &mFracOfMergedRowV0PosV0Pos,
								 &mClosestRowAtDCAV0PosV0Pos ); }
    return mFracOfMergedRowV0PosV0Pos;
  }
  double fractionOfMergedRowV0NegV0Neg() const
  { if(mMergingParNotCalculatedV0NegV0Neg) { calcMergingParFctn( &mMergingParNotCalculatedV0NegV0Neg,
								 mTrack1->v0NegZ(), mTrack1->v0NegU(),
								 mTrack2->v0NegZ(), mTrack2->v0NegU(),
								 mTrack1->v0NegSect(), mTrack2->v0NegSect(),
								 &mFracOfMergedRowV0NegV0Neg,
								 &mClosestRowAtDCAV0NegV0Neg ); }
    return mFracOfMergedRowV0NegV0Neg;
  }

  /**
   * Setters
   **/
  void setTrack1(const StHbtParticle* trkPtr) { mTrack1=(StHbtParticle*)trkPtr; resetParCalculated(); }
  void setTrack2(const StHbtParticle* trkPtr) { mTrack2=(StHbtParticle*)trkPtr; resetParCalculated(); }

  void setMergingPar(float aMaxDuInner, float aMaxDzInner,
		     float aMaxDuOuter, float aMaxDzOuter);
  void setDefaultHalfFieldMergingPar();
  void setDefaultFullFieldMergingPar();

private:

  StHbtParticle* mTrack1;
  StHbtParticle* mTrack2;

  mutable short mNonIdParNotCalculated;
  mutable float mDKSide;
  mutable float mDKOut;
  mutable float mDKLong;
  mutable float mCVK;
  mutable float mKStarCalc;
  void calcNonIdPar() const;

  mutable short mNonIdParNotCalculatedGlobal;
  mutable float mDKSideGlobal;
  mutable float mDKOutGlobal;
  mutable float mDKLongGlobal;
  mutable float mKStarCalcGlobal;
  mutable float mCVKGlobal;
  void calcNonIdParGlobal() const;

  mutable short mMergingParNotCalculated;
  mutable float mWeightedAvSep;
  mutable float mFracOfMergedRow;
  mutable float mClosestRowAtDCA;

  mutable short mMergingParNotCalculatedTrkV0Pos;
  mutable float mFracOfMergedRowTrkV0Pos;
  mutable float mClosestRowAtDCATrkV0Pos;

  mutable short mMergingParNotCalculatedTrkV0Neg;
  mutable float mFracOfMergedRowTrkV0Neg;
  mutable float mClosestRowAtDCATrkV0Neg;

  mutable short mMergingParNotCalculatedV0PosV0Neg;
  mutable float mFracOfMergedRowV0PosV0Neg;
  mutable float mClosestRowAtDCAV0PosV0Neg;

  mutable short mMergingParNotCalculatedV0NegV0Pos;
  mutable float mFracOfMergedRowV0NegV0Pos;
  mutable float mClosestRowAtDCAV0NegV0Pos;

  mutable short mMergingParNotCalculatedV0PosV0Pos;
  mutable float mFracOfMergedRowV0PosV0Pos;
  mutable float mClosestRowAtDCAV0PosV0Pos;

  mutable short mMergingParNotCalculatedV0NegV0Neg;
  mutable float mFracOfMergedRowV0NegV0Neg;
  mutable float mClosestRowAtDCAV0NegV0Neg;

  static float mMaxDuInner;
  static float mMaxDzInner;
  static float mMaxDuOuter;
  static float mMaxDzOuter;
  static float mTpcRadiusMin;   //[cm]
  static float mTpcRadiusMax;   //[cm]
  void calcMergingPar() const;

  void calcMergingParFctn(short* tmpMergingParNotCalculatedFctn,
			  float* tmpZ1, float* tmpU1,
			  float* tmpZ2, float* tmpU2,
			  int *tmpSect1, int *tmpSect2,
			  float* tmpFracOfMergedRow,
			  float* tmpClosestRowAtDCA) const;

  void resetParCalculated() {
    mNonIdParNotCalculated=1; mNonIdParNotCalculatedGlobal=1;
    mMergingParNotCalculated=1; mMergingParNotCalculatedTrkV0Pos=1;
    mMergingParNotCalculatedTrkV0Neg=1; mMergingParNotCalculatedV0PosV0Pos=1;
    mMergingParNotCalculatedV0NegV0Pos=1; mMergingParNotCalculatedV0PosV0Neg=1;
    mMergingParNotCalculatedV0NegV0Neg=1;
  }
};

#endif // #define StHbtPair_h
