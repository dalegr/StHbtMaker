/**
 * Description: A special type of particle dealing with the specifics of the V0 type
 * of particle.
 *
 * This class stores the information both about the V0 itself and about its
 * daughters. This easily enables cuts on daughter characteristics.
 */

#ifndef StHbtV0_h
#define StHbtV0_h

/// C++ headers
#include <limits>

/// StHbtMaker headers
#include "StHbtTypes.h"
#include "StHbtPhysicalHelix.h"
#include "StHbtHiddenInfo.h"
#include "phys_constants.h"

/// ROOT headers
#include "TVector3.h"
#include "TMath.h"

//_________________
class StHbtV0 {
  
 public:
  /// Constructor
  StHbtV0();
  /// Copy constructor
  StHbtV0(const StHbtV0& copy);
  /// Assignment operator
  StHbtV0& operator=(const StHbtV0& copy);
  /// Destructor
  ~StHbtV0();

  /**
   *  Getters  
   **/

  ///////////////////
  // V0 parameters //
  ///////////////////
  TVector3 decayPoint() const    { return TVector3( mV0DecayPointX, mV0DecayPointY, mV0DecayPointZ ); }
  TVector3 decayVertex() const   { return decayPoint(); }
  TVector3 primaryVertex() const { return TVector3( mPrimaryVertexX, mPrimaryVertexY, mPrimaryVertexZ ); }
  float    bField() const        { return mBField; }
  float    magneticField() const { return bField(); }
  TVector3 v0DecayVector() const { return ( decayPoint() - primaryVertex() ); }
  float v0DecayLength() const    { return v0DecayVector().Mag(); }
  float v0AndgleBetweenMomentumAndDecayVector() const
  { return TMath::Cos( momV0().Angle( v0DecayVector() ) ); }
  TVector3 momV0() const         { return TVector3( mV0MomX, mV0MomY, mV0MomZ); }
  float momV0X() const           { return momV0().X(); }
  float momV0Y() const           { return momV0().Y(); }
  float momV0Z() const           { return momV0().Z(); }
  float ptV0() const             { return momV0().Perp(); }
  float pt2V0() const            { return momV0().Perp2(); }
  float ptotV0() const           { return momV0().Mag(); }
  float ptot2V0() const          { return momV0().Mag2(); }
  float etaV0() const            { return momV0().PseudoRapidity(); }
  float pseudoRapV0() const      { return etaV0(); }
  float phiV0() const            { return momV0().Phi(); }
  float v0PtotPos() const        { return mV0PtotPos; }
  float v0PtotNeg() const        { return mV0PtotNeg; }
  float alphaV0() const          { return mAlphaV0; }
  float ptArmV0() const          { return mPtArmV0; }
  float eLambda() const          { return TMath::Sqrt(ptot2V0() + M_LAMBDA*M_LAMBDA); }
  float eK0Short() const         { return TMath::Sqrt(ptot2V0() + M_KAON_0_SHORT*M_KAON_0_SHORT); }
  float ePhi() const             { return TMath::Sqrt(ptot2V0() + M_PHI*M_PHI); }
  float massLambda() const
  { return TMath::Sqrt( ( eNegPion() + ePosProton() ) * ( eNegPion() + ePosProton() ) + ptot2V0() ); }
  float massAntiLambda() const
  { return TMath::Sqrt( ( ePosPion() + eNegProton() ) * ( ePosPion() + eNegProton() ) + ptot2V0() ); }
  float massK0Short() const
  { return TMath::Sqrt( ( ePosPion() + eNegPion() ) * ( ePosPion() + ePosPion() ) + ptot2V0() ); }
  float massPhi() const
  { return TMath::Sqrt( ( ePosKaon() + eNegKaon() ) * ( ePosKaon() + eNegKaon() ) + ptot2V0() ); }
  float dMLambda() const         { return (massLambda() - M_LAMBDA); }
  float dMAntiLambda() const     { return (massAntiLambda() - M_LAMBDA); }
  float dMK0Short() const        { return (massK0Short() - M_KAON_0_SHORT); }
  float dMPhi() const            { return (massPhi() - M_PHI); }
  float rapidityLambda() const;
  float rapidityK0Short() const;
  float rapidityPhi() const;
  float rapLambda() const        { return rapidityLambda(); }
  float rapK0Short() const       { return rapidityK0Short(); }
  float rapPhi() const           { return rapidityPhi(); }
  float cTauLambda() const       { return ( M_LAMBDA * v0DecayLength() / ptotV0() ); }
  float cTauK0Short() const      { return ( M_KAON_0_SHORT * v0DecayLength() / ptotV0() ); }
  float cTauPhi() const          { return ( M_PHI * v0DecayLength() / ptotV0() );}
  float ePosProton() const       { return TMath::Sqrt(M_PROTON*M_PROTON + mV0PtotPos*mV0PtotPos); }
  float ePosPion() const         { return TMath::Sqrt(M_PION_PLUS*M_PION_PLUS + mV0PtotPos*mV0PtotPos); }
  float ePosKaon() const         { return TMath::Sqrt(M_KAON_PLUS*M_KAON_PLUS + mV0PtotPos*mV0PtotPos); }
  float eNegProton() const       { return TMath::Sqrt(M_ANTIPROTON *M_ANTIPROTON + mV0PtotNeg*mV0PtotNeg); }
  float eNegPion() const         { return TMath::Sqrt(M_PION_MINUS*M_PION_MINUS + mV0PtotNeg*mV0PtotNeg); }
  float eNegKaon() const         { return TMath::Sqrt(M_KAON_MINUS*M_KAON_MINUS + mV0PtotNeg*mV0PtotNeg); }
  float chi2V0() const           { return (float)mChi2V0 / 10; }
  float clV0() const             { return mClV0; }
  float armAlphaV0() const       { return mAlphaV0; }
  float armPtV0() const          { return mPtArmV0; }

  void setPrimaryVertex(const float& x, const float& y, const float& z)
  { mPrimaryVertexX = x; mPrimaryVertexY = y; mPrimaryVertexZ = z; }
  void setPrimaryVertex(const TVector3& vtx)
  { setPrimaryVertex( vtx.X(), vtx.Y(), vtx.Z() ); }
  void setDecayPoint(const float& x, const float& y, const float& z)
  { mV0DecayPointX = x; mV0DecayPointY = y; mV0DecayPointZ = z; }
  void setDecayPoint(const TVector3& point)
  { setDecayPoint( point.X(), point.Y(), point.Z() ); }
  void setBField(const float& field)             { mBField = field; }
  void setMagneticField(const float& field)      { setBField( field ); }
  void setV0Mom(const float& px, const float& py, const float& pz)
  { mV0MomX = px; mV0MomY = py; mV0MomZ = pz; }
  void setV0Mom(const TVector3& mom)             { setV0Mom( mom.X(), mom.Y(), mom.Z() ); }
  void setMomV0(const TVector3& mom)             { setV0Mom( mom ) ; }
  void setV0PtotPos(const float& ptot)           { mV0PtotPos = ptot; }
  void setV0PtotNeg(const float& ptot)           { mV0PtotNeg = ptot; }
  void setV0DcaDaughters(const float& dca)       { mV0DcaDaughters = dca; }
  void setV0Dca2PrimaryVertex(const float& dca)  { mV0DcaToPrimVertex = dca; }
  void setV0DcaToPrimaryVertex(const float& dca) { mV0DcaToPrimVertex = dca; }
  void setChi2V0(const float& chi2);
  void setClV0(const float& cl)                  { mClV0 = cl; }
  void setArmAlphaV0(const float& alpha)         { mAlphaV0 = alpha; }
  void setArmPtV0(const float& pt)               { mPtArmV0 = pt; }

  /// Recalculate most of V0 parameters using daughter tracks
  /// and primary vertex information
  void updateV0();

  ///////////////////////
  // Positive daughter //
  ///////////////////////
  unsigned short idPos() const   { return mPosId; }
  unsigned short keyPos() const  { return mPosId; }
  TVector3 momPos() const        { return TVector3( mPosMomX, mPosMomY, mPosMomZ ); }
  float momXPos() const          { return momPos().X(); }
  float momYPos() const          { return momPos().Y(); }
  float momZPos() const          { return momPos().Z(); }
  float ptPos() const            { return momPos().Perp(); }
  float ptotPos() const          { return momPos().Mag(); }
  float ptot2Pos() const         { return momPos().Mag2(); }
  float etaPos() const           { return momPos().PseudoRapidity(); }
  float pseudoRapPos() const     { return etaPos(); }
  float phiPos() const           { return momPos().Phi(); }
  TVector3 dcaPosToPrimVertex() const
  { return TVector3( mPosDca2PrimVertexX, mPosDca2PrimVertexY, mPosDca2PrimVertexZ ); }
  TVector3 originPos() const          { return ( primaryVertex() + dcaPosToPrimVertex() ); }
  unsigned short tpcHitsPos() const   { return nHitsPos(); }
  unsigned short nHitsPos() const     { return (unsigned short)mPosNHits; }
  unsigned short nHitsFitPos() const  { return (unsigned short)mPosNHits; }
  unsigned short nHitsPossiblePos() const { return (unsigned short)mPosNHitsPoss; }
  float nHitsFitOPossRatioPos() const { return (float)nHitsFitPos()/ nHitsPossiblePos(); }
  unsigned short nHitsDedxPos() const { return (unsigned short)mPosNHitsDedx; }
  unsigned short numdedxPos() const   { return nHitsDedxPos(); }
  float chi2Pos() const               { return (float)mPosChi2 / 10.f; }
  float dedxPos() const               { return dEdxPos(); }
  float dEdxPos() const               { return (float)mPosDedx * 1e-9; }
  float nSigmaElectronPos() const     { return (float)mPosNSigmaElectron / 1000.f; }
  float nSigmaPionPos() const         { return (float)mPosNSigmaPion / 1000.f; }
  float nSigmaKaonPos() const         { return (float)mPosNSigmaKaon / 1000.f; }
  float nSigmaProtonPos() const       { return (float)mPosNSigmaProton / 1000.f; }
  bool isTofTrackPos() const          { return (mPosTofBeta>0) ? true : false; }
  float betaPos() const               { return ( isTofTrackPos() ) ? (float)mPosTofBeta / 20000.f : -999.f; }
  float inverseBetaPos() const        { return ( isTofTrackPos() ) ? 1./betaPos() : -999.f; }
  float inverseBeta2Pos() const       { return ( isTofTrackPos() ) ? 1./ ( betaPos() * betaPos() ) : -999.f; }
  float massSqrPos() const
  { return ( isTofTrackPos() ) ? ( ptot2Pos() * (inverseBeta2Pos() - 1.) ) : -999.f; }
  unsigned int topologyMapPos(unsigned int& word) const { return mPosTopologyMap[word]; }
  unsigned int trackTopologyMapPos(unsigned int& word) const { return topologyMapPos(word); }
  StHbtPhysicalHelix helixPos() const;

  void setIdPos(const int& id)        { mPosId = (id>0) ? id : 0; }
  void setIdPos(const short& id)      { mPosId = (id>0) ? id : 0; }
  void setKeyPos(const int& id)       { mPosId = (id>0) ? id : 0; }
  void setKeyPos(const short& id)     { mPosId = (id>0) ? id : 0; }
  void setMomPos(const float& px, const float& py, const float& pz)
  { mPosMomX = px; mPosMomY = py; mPosMomZ = pz; }
  void setMomPos(const TVector3& mom) { setMomPos( mom.X(), mom.Y(), mom.Z() ); }
  void setMomXPos(const float& px)    { mPosMomX = px; }
  void setMomYPos(const float& py)    { mPosMomY = py; }
  void setMomZPos(const float& pz)    { mPosMomZ = pz; }
  void setDcaGlobalPos(const float& x, const float& y, const float& z)
  { mPosDca2PrimVertexX = x; mPosDca2PrimVertexY = y; mPosDca2PrimVertexZ = z; }
  void setDcaGlobalPos(const TVector3& dca) { setDcaGlobalPos( dca.X(), dca.Y(), dca.Z() ); }
  void setDcaGlobalXPos(const float& x)     { mPosDca2PrimVertexX = x; }
  void setDcaGlobalYPos(const float& y)     { mPosDca2PrimVertexY = y; }
  void setDcaGlobalZPos(const float& z)     { mPosDca2PrimVertexZ = z; }
  void setNHitsPos(const int& nhits)        { mPosNHits = (nhits>0) ? nhits : 0; }
  void setNHitsPossiblePos(const int& nhits){ mPosNHitsPoss = (nhits>0) ? nhits : 0; }
  void setNHitsDedxPos(const int& nhits)    { mPosNHitsDedx = (nhits>0) ? nhits : 0; }
  void setTopologyMapPos(const int& word, const int& val) { mPosTopologyMap[word] = val; }
  void setChi2Pos(const float& chi2)        { mPosChi2 = ( (chi2 * 10) > std::numeric_limits<unsigned char>::max() ?
							   std::numeric_limits<unsigned char>::max() :
							   (unsigned char)TMath::Nint( chi2 * 10.f ) ); }
  void setDedxPos(const double& dEdx)       {
    if( dEdx <= 0 ) { mPosDedx = 0; }
    else {
      mPosDedx = ( (dEdx * 1e9) > std::numeric_limits<unsigned short>::max() ?
		   std::numeric_limits<unsigned short>::max() :
		   (unsigned short) (dEdx * 1e9) );
    }
  }
  void setNSigmaElectronPos(const float& nsigma);
  void setNSigmaPionPos(const float& nsigma);
  void setNSigmaKaonPos(const float& nsigma);
  void setNSigmaProtonPos(const float& nsigma);
  void setTofBetaPos(const float& beta);

  ///////////////////////
  // Negative daughter //
  ///////////////////////
  unsigned short idNeg() const   { return mNegId; }
  unsigned short keyNeg() const  { return mNegId; }
  TVector3 momNeg() const        { return TVector3( mNegMomX, mNegMomY, mNegMomZ ); }
  float momXNeg() const          { return momNeg().X(); }
  float momYNeg() const          { return momNeg().Y(); }
  float momZNeg() const          { return momNeg().Z(); }
  float ptNeg() const            { return momNeg().Perp(); }
  float ptotNeg() const          { return momNeg().Mag(); }
  float ptot2Neg() const         { return momNeg().Mag2(); }
  float etaNeg() const           { return momNeg().PseudoRapidity(); }
  float pseudoRapNeg() const     { return etaNeg(); }
  float phiNeg() const           { return momNeg().Phi(); }
  TVector3 dcaNegToPrimVertex() const
  { return TVector3( mNegDca2PrimVertexX, mNegDca2PrimVertexY, mNegDca2PrimVertexZ ); }
  TVector3 originNeg() const     { return ( primaryVertex() + dcaNegToPrimVertex() ); }
  unsigned short tpcHitsNeg() const   { return nHitsNeg(); }
  unsigned short nHitsNeg() const     { return (unsigned short)mNegNHits; }
  unsigned short nHitsFitNeg() const  { return (unsigned short)mNegNHits; }
  unsigned short nHitsPossibleNeg() const { return (unsigned short)mNegNHitsPoss; }
  float nHitsFitOPossRatioNeg() const { return (float)nHitsFitNeg()/ nHitsPossibleNeg(); }
  unsigned short nHitsDedxNeg() const { return (unsigned short)mNegNHitsDedx; }
  unsigned short numdedxNeg() const   { return nHitsDedxNeg(); }
  float chi2Neg() const               { return (float)mNegChi2 / 10.f; }
  float dedxNeg() const               { return dEdxNeg(); }
  float dEdxNeg() const               { return (float)mNegDedx * 1e-9; }
  float nSigmaElectronNeg() const     { return (float)mNegNSigmaElectron / 1000.f; }
  float nSigmaPionNeg() const         { return (float)mNegNSigmaPion / 1000.f; }
  float nSigmaKaonNeg() const         { return (float)mNegNSigmaKaon / 1000.f; }
  float nSigmaProtonNeg() const       { return (float)mNegNSigmaProton / 1000.f; }
  bool isTofTrackNeg() const          { return (mNegTofBeta>0) ? true : false; }
  float betaNeg() const               { return ( isTofTrackNeg() ) ? (float)mNegTofBeta / 20000.f : -999.f; }
  float inverseBetaNeg() const        { return ( isTofTrackNeg() ) ? 1./betaNeg() : -999.f; }
  float inverseBeta2Neg() const       { return ( isTofTrackNeg() ) ? 1./ ( betaNeg() * betaNeg() ) : -999.f; }
  float massSqrNeg() const
  { return ( isTofTrackNeg() ) ? ( ptot2Neg() * (inverseBeta2Neg() - 1.) ) : -999.f; }
  unsigned int topologyMapNeg(unsigned int& word) const { return mNegTopologyMap[word]; }
  unsigned int trackTopologyMapNeg(unsigned int& word) const { return topologyMapNeg(word); }
  StHbtPhysicalHelix helixNeg() const;

  void setIdNeg(const int& id)        { mNegId = (id>0) ? id : 0; }
  void setIdNeg(const short& id)      { mNegId = (id>0) ? id : 0; }
  void setKeyNeg(const int& id)       { mNegId = (id>0) ? id : 0; }
  void setKeyNeg(const short& id)     { mNegId = (id>0) ? id : 0; }
  void setMomNeg(const float& px, const float& py, const float& pz)
  { mNegMomX = px; mNegMomY = py; mNegMomZ = pz; }
  void setMomNeg(const TVector3& mom) { setMomNeg( mom.X(), mom.Y(), mom.Z() ); }
  void setMomXNeg(const float& px)    { mNegMomX = px; }
  void setMomYNeg(const float& py)    { mNegMomY = py; }
  void setMomZNeg(const float& pz)    { mNegMomZ = pz; }
  void setDcaGlobalNeg(const float& x, const float& y, const float& z)
  { mNegDca2PrimVertexX = x; mNegDca2PrimVertexY = y; mNegDca2PrimVertexZ = z; }
  void setDcaGlobalNeg(const TVector3& dca) { setDcaGlobalNeg( dca.X(), dca.Y(), dca.Z() ); }
  void setDcaGlobalXNeg(const float& x)     { mNegDca2PrimVertexX = x; }
  void setDcaGlobalYNeg(const float& y)     { mNegDca2PrimVertexY = y; }
  void setDcaGlobalZNeg(const float& z)     { mNegDca2PrimVertexZ = z; }
  void setNHitsNeg(const int& nhits)        { mNegNHits = (nhits>0) ? nhits : 0; }
  void setNHitsPossibleNeg(const int& nhits){ mNegNHitsPoss = (nhits>0) ? nhits : 0; }
  void setNHitsDedxNeg(const int& nhits)    { mNegNHitsDedx = (nhits>0) ? nhits : 0; }
  void setTopologyMapNeg(const int& word, const int& val) { mNegTopologyMap[word] = val; }
  void setChi2Neg(const float& chi2)        { mNegChi2 = ( (chi2 * 10) > std::numeric_limits<unsigned char>::max() ?
							   std::numeric_limits<unsigned char>::max() :
							   (unsigned char)TMath::Nint( chi2 * 10.f ) ); }
  void setDedxNeg(const double& dEdx)       {
    if( dEdx <= 0 ) { mNegDedx = 0; }
    else {
      mNegDedx = ( (dEdx * 1e9) > std::numeric_limits<unsigned short>::max() ?
		   std::numeric_limits<unsigned short>::max() :
		   (unsigned short)(dEdx * 1e9) );
    }
  }
  void setNSigmaElectronNeg(const float& nsigma);
  void setNSigmaPionNeg(const float& nsigma);
  void setNSigmaKaonNeg(const float& nsigma);
  void setNSigmaProtonNeg(const float& nsigma);
  void setTofBetaNeg(const float& beta);
  
  ///////////////
  // Th. stuff //
  ///////////////
  void setHiddenInfo(StHbtHiddenInfo* aHiddenInfo) { mHiddenInfo = aHiddenInfo; }
  bool isValidHiddenInfo() const                   { return (mHiddenInfo) ? true : false; }
  bool validHiddenInfo() const                     { return isValidHiddenInfo(); }
  StHbtHiddenInfo* getHiddenInfo() const           { return mHiddenInfo; }

 protected:

  /// Primary vertex position
  float mPrimaryVertexX;
  float mPrimaryVertexY;
  float mPrimaryVertexZ;

  /// Magnetic field
  float mBField;
  
  ///////////////////////
  //   V0 parameters   //
  ///////////////////////

  /// Decay point of V0
  float mV0DecayPointX;
  float mV0DecayPointY;
  float mV0DecayPointZ;

  /// Reconstructed momentum of V0
  float mV0MomX;
  float mV0MomY;
  float mV0MomZ;

  /// Total momentum of daughter tracks at decay point
  float mV0PtotPos;
  float mV0PtotNeg;

  /// Distance between daughters (at DCA)
  float mV0DcaDaughters;
  /// DCA of V0 to primary vertex
  float mV0DcaToPrimVertex;

  /// Chi2 of the V0 reconstruction (compression *= 10)
  unsigned char mChi2V0;
  float mClV0;
  /// Podolyanski-Armenteros parameters of V0
  float mAlphaV0;
  float mPtArmV0;

  /**
   * Important: For daughters we store DCA to primary vertex,
   * momentum of the global track at DCA and the other parameters.
   * this is important, because it provides the ability to recalculate
   * V0 parameters at any time.
   **/
  
  ///////////////////////
  // Positive daughter //
  ///////////////////////

  /// Unique ID
  unsigned short mPosId;
  /// Momentum of the track (at DCA to primary vertex)
  float mPosMomX;
  float mPosMomY;
  float mPosMomZ;
  /// DCA of the track to primary vertex
  float mPosDca2PrimVertexX;
  float mPosDca2PrimVertexY;
  float mPosDca2PrimVertexZ;

  /// Number of hits, possible number of hits, and number
  /// of hits used in the dEdx estimation
  unsigned char mPosNHits;
  unsigned char mPosNHitsPoss;
  unsigned char mPosNHitsDedx;
  /// Topology map of the track
  unsigned int mPosTopologyMap[2];

  /// chi2 of the track reconstruction (compression factor *= 10)
  unsigned char mPosChi2;
  /// dEdx of the track (in eV/cm) (compression factor = *10^9)
  unsigned short mPosDedx;

  /// Number of sigma for electron, pion, kaon and proton
  /// estimated via dE/dx in TPC. (compression factor = *1000)
  short mPosNSigmaElectron;
  short mPosNSigmaPion;
  short mPosNSigmaKaon;
  short mPosNSigmaProton;

  /// Time-of-Flight information. 0 correseponds
  /// to the absence of the signal (compression = *20000)
  unsigned short mPosTofBeta;

  ///////////////////////
  // Negative daughter //
  ///////////////////////

  /// Unique ID
  unsigned short mNegId;
  /// Momentum of the track (at DCA to primary vertex)
  float mNegMomX;
  float mNegMomY;
  float mNegMomZ;
  /// DCA of the track to primary vertex
  float mNegDca2PrimVertexX;
  float mNegDca2PrimVertexY;
  float mNegDca2PrimVertexZ;

  /// Number of hits, possible number of hits, and number
  /// of hits used in the dEdx estimation
  unsigned char mNegNHits;
  unsigned char mNegNHitsPoss;
  unsigned char mNegNHitsDedx;
  /// Topology map of the track
  unsigned int mNegTopologyMap[2];

  /// chi2 of the track reconstruction
  unsigned short mNegChi2;
  /// dEdx of the track (in eV/cm) (compression factor = *10^9)
  unsigned short mNegDedx;

  /// Number of sigma for electron, pion, kaon and proton
  /// estimated via dE/dx in TPC. (compression factor = *1000)
  short mNegNSigmaElectron;
  short mNegNSigmaPion;
  short mNegNSigmaKaon;
  short mNegNSigmaProton;

  /// Time-of-Flight information. 0 correseponds
  /// to the absence of the signal (compression = *20000)
  unsigned short mNegTofBeta;
  
  /// Theoretical stuff
  mutable StHbtHiddenInfo* mHiddenInfo; //!
};

#endif // #define StHbtV0_h


















