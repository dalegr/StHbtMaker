/**
 * Description: Main class holding track information (before identification)
 *
 * StHbtTrack holds all the necessary information about a track that is
 * required during femtoscopic analysis. This class is filled with information
 * from the input stream by the reader. A particle has a link back to the Track
 * it was created from, so we do not copy the information.
 */

#ifndef StHbtTrack_h
#define StHbtTrack_h

/// C++ headers
#include <cmath>
#include <limits>

/// StHbtMaker headers
// Infrastructure
#include "StHbtTypes.h"
#include "StHbtPhysicalHelix.h"
// Base
#include "StHbtHiddenInfo.h"

/// ROOT headers
#include "TMath.h"
#include "TVector3.h"
#include "TLorentzVector.h"

//_________________
class StHbtTrack {

 public:
  /// Constructor
  StHbtTrack();
  /// Copy constructor
  StHbtTrack(const StHbtTrack& track);
  /// Copy constructor
  StHbtTrack& operator=(const StHbtTrack& track);
  /// Destructor
  ~StHbtTrack();

  /**
   * Getters  
   **/
  
  unsigned short id() const        { return mId; }
  short type() const               { return ( isPrimary() ) ? 1 : 0; }
  bool  isPrimary() const          { return ( pMom().Mag()>0 ) ? true : false; }
  short charge() const             { return ( mNHits>0) ? 1 : -1; }
  unsigned short flag() const      { return mFlag; }
  unsigned short nHits() const     { return (unsigned short)TMath::Abs(mNHits); }
  unsigned short numberOfHits() const { return nHits(); }
  unsigned short nHitsFit() const  { return nHits(); }
  unsigned short nHitsPossible() const { return (unsigned short)mNHitsPoss; }
  unsigned short nHitsDedx() const { return (unsigned short)mNHitsDedx; }
  float nHitsFit2PossRatio() const { return ( nHitsPossible()>0 ) ? (float)nHits()/nHitsPossible() : 0; }
  float nSigmaElectron() const     { return (float)mNSigmaElectron / 1000.; }
  float nSigmaPion() const         { return (float)mNSigmaPion / 1000.; }
  float nSigmaKaon() const         { return (float)mNSigmaKaon / 1000.; }
  float nSigmaProton() const       { return (float)mNSigmaProton / 1000.; }
  float pidProbElectron() const    { return (float)mPidProbElectron / 10000.; }
  float pidProbPion() const        { return (float)mPidProbPion / 10000.; }
  float pidProbKaon() const        { return (float)mPidProbKaon / 10000.; }
  float pidProbProton() const      { return (float)mPidProbProton / 10000.; }
  double dEdx() const              { return (double)mDedx * 1e-9; }
  TVector3 momentum() const        { return ( isPrimary() ) ? pMom() : gMom(); }
  TVector3 p() const               { return momentum(); }
  TVector3 pMom() const            { return TVector3(mPrimaryPx, mPrimaryPy, mPrimaryPz); }
  float ptot() const               { return ( isPrimary() ) ? pMom().Mag() : gPtot(); }
  float ptot2() const              { return ( isPrimary() ) ? pMom().Mag2() : gPtot2(); }
  float pt() const                 { return ( isPrimary() ) ? pMom().Perp() : gPt(); }
  float pt2() const                { return ( isPrimary() ) ? pMom().Perp2() : gPt2(); }
  float eta() const                { return ( isPrimary() ) ? pMom().PseudoRapidity() : gEta(); }
  float pseudoRapidity() const     { return ( isPrimary() ) ? eta() : gEta(); }
  float phi() const                { return ( isPrimary() ) ? pMom().Phi() : gPhi(); }
  float theta() const              { return ( isPrimary() ) ? pMom().Theta() : gTheta(); }
  TVector3 gMom() const            { return TVector3(mGlobalPx, mGlobalPy, mGlobalPz); }
  float gPtot() const              { return gMom().Mag(); }
  float gPtot2() const             { return gMom().Mag2(); }
  float gPt() const                { return gMom().Perp(); }
  float gPt2() const               { return gMom().Perp2(); }
  float gEta() const               { return gMom().Eta(); }
  float gTheta() const             { return gMom().Theta(); }
  float gPhi() const               { return gMom().Phi(); }
  TVector3 primaryVertex() const   { return TVector3(mPrimaryVertexX, mPrimaryVertexY, mPrimaryVertexZ); }
  TVector3 origin() const          { return ( primaryVertex()+gDCA() ); }
  TVector3 gDCA() const            { return TVector3(mDcaX, mDcaY, mDcaZ); }
  float gDCAxy() const             { return gDCA().Perp(); }
  float gDCAz() const              { return gDCA().Z(); }
  float chi2() const               { return (float)mChi2 * 0.001; }
  unsigned int topologyMap(const unsigned int& word) const { return mMap[word]; }
  float beta() const               { return ( isTofTrack() ) ? (float)mTofBeta / 20000 : -999.; }
  bool  isTofTrack() const         { return ( mTofBeta>0 ) ? false : true; }
  float invBeta() const            { return ( isTofTrack() ) ? 1./beta() : -999.; }
  float invBeta2() const           { return ( isTofTrack() ) ? invBeta()*invBeta() : -999; }
  float massSqr() const;
  TLorentzVector emissionPoint() const
  { return TLorentzVector( emissionPointX(), emissionPointY(), emissionPointZ(), emissionPointT() ); }
  float emissionPointX() const     { return (mXfr) ? *mXfr : 0.; }
  float emissionPointY() const     { return (mYfr) ? *mYfr : 0.; }
  float emissionPointZ() const     { return (mZfr) ? *mZfr : 0.; }
  float emissionPointT() const     { return (mTfr) ? *mTfr : -1.; }
  int pdgId() const                { return (mPdgId) ? *mPdgId : 0.; }
  int pdgCode() const              { return pdgId(); }

  StHbtPhysicalHelix helix() const;
  StHbtPhysicalHelix gHelix() const;  

  /**
   * Setters  
   **/
  
  void setId(const unsigned short& id)   { mId = (unsigned short)id; }
  void setFlag(const short& flag)        { mFlag = flag; }
  void setNHits(const short& nhits)      { mNHits = (char)nhits;}  //Has to be charge*nHits
  void setNHitsPossible(const short& nh) { mNHitsPoss = (unsigned char)nh; }
  void setNHitsDedx(const short& nh)     { mNHitsDedx = (unsigned char)nh; }
  void setChi2(const float& chi2);
  void setDedx(const double& dEdx);
  void setNSigmaElectron(const float& nsigma);
  void setNSigmaPion(const float& nsigma);
  void setNSigmaKaon(const float& nsigma);
  void setNSigmaProton(const float& nsigma);
  void setPidProbElectron(const float& prob);
  void setPidProbPion(const float& prob);
  void setPidProbKaon(const float& prob);
  void setPidProbProton(const float& prob);
  void setDca(const float& x, const float& y, const float& z) { mDcaX=x; mDcaY=y; mDcaZ=z; }
  void setDcaX(const float& x)                                { mDcaX=x; }
  void setDcaY(const float& y)                                { mDcaY=y; }
  void setDcaZ(const float& z)                                { mDcaZ=z; }
  void setP(const float& px, const float& py, const float& pz)
  { mPrimaryPx=px; mPrimaryPy=py; mPrimaryPz=pz; }
  void setP(const TVector3& mom)
  { mPrimaryPx=mom.X(); mPrimaryPy=mom.Y(); mPrimaryPz=mom.Z(); }
  void setPx(const float& px)                                 { mPrimaryPx=px; }
  void setPy(const float& py)                                 { mPrimaryPy=py; }
  void setPz(const float& pz)                                 { mPrimaryPz=pz; }
  void setGlobalP(const float& px, const float& py, const float& pz)
  { mGlobalPx=px; mGlobalPy=py; mGlobalPz=pz; }
  void setGlobalP(const TVector3& mom)
  { mGlobalPx=mom.X(); mGlobalPy=mom.Y(); mGlobalPz=mom.Z(); }
  void setGlobalPx(const float& px)                           { mGlobalPx=px; }
  void setGlobalPy(const float& py)                           { mGlobalPy=py; }
  void setGlobalPz(const float& pz)                           { mGlobalPz=pz; }
  void setPrimaryVertex(const float& x, const float& y, const float& z)
  { mPrimaryVertexX=x; mPrimaryVertexY=y; mPrimaryVertexZ=z; }
  void setPrimaryVertex(const TVector3& vtx)
  { mPrimaryVertexX=vtx.X(); mPrimaryVertexY=vtx.Y(); mPrimaryVertexZ=vtx.Z(); }
  void setPrimaryVertexX(const float& x)                      { mPrimaryVertexX=x; }
  void setPrimaryVertexY(const float& y)                      { mPrimaryVertexY=y; }
  void setPrimaryVertexZ(const float& z)                      { mPrimaryVertexZ=z; }
  void setMagneticField(const float& bField)                  { mBField = bField; }
  void setBField(const float& bField)                         { setMagneticField(bField); }
  void setTopologyMap(const int word, const unsigned int map) {mMap[word] = map;}
  void setBeta(const float &beta);
  // Freeze-out parameters (for the simulation only)
  void setEmissionPoint(const TLorentzVector& point)
  { *mXfr=point.X(); *mYfr=point.Y(); *mZfr=point.Z(); *mTfr=point.T(); }
  void setEmissionPointX(const float &x);
  void setEmissionPointY(const float &y);
  void setEmissionPointZ(const float &z);
  void setEmissionPointT(const float &t);
  void setPdgCode(const int& pdg);
  void setPdgId(const int& id)                                { setPdgCode(id); }

  /* Th stuff */
  void setHiddenInfo(StHbtHiddenInfo* aHiddenInfo) { mHiddenInfo = aHiddenInfo; }
  bool validHiddenInfo() const { return (mHiddenInfo) ? true : false; }
  StHbtHiddenInfo* getHiddenInfo() const {return mHiddenInfo;}
  /***/

 private:

  /// Track unique ID
  unsigned short mId;
  short mFlag;
  /// nHits*charge
  char  mNHits;               
  unsigned char mNHitsPoss;  
  unsigned char mNHitsDedx;
  /// chi2 of the track reconstruction (compression factor = *1000)
  unsigned short mChi2;
  /// Ionization energy loss (in eV/cm) (compression factor = *10^9)
  unsigned short mDedx;

  /// Number of sigma for electron, pion, kaon and proton
  /// estimated via dE/dx in TPC. (compression factor = *1000)
  short mNSigmaElectron;
  short mNSigmaPion;
  short mNSigmaKaon;
  short mNSigmaProton;
  /// Probability of the track to be electron, pion, kaon, proton.
  /// (Compression factor = *10000)
  unsigned short mPidProbElectron;
  unsigned short mPidProbPion;
  unsigned short mPidProbKaon;
  unsigned short mPidProbProton;
  
  /// Topology map
  unsigned int mMap[2];
  
  /// Time-of-Flight information. 0 correseponds
  /// to the absence of the signal (compression = *20000)
  unsigned short mTofBeta;

  /// Primary track momentum (0 -  if not primary)
  float mPrimaryPx;
  float mPrimaryPy;
  float mPrimaryPz;
  /// Global track momentum at DCA to primary vertex
  float mGlobalPx;
  float mGlobalPy;
  float mGlobalPz;
  /// DCA(x,y,z) of the global track to primary vertex
  float mDcaX;
  float mDcaY;
  float mDcaZ;

  /// Primary vertex position ( dca2pvtx = trackOrigin - vertexPosition )
  float mPrimaryVertexX;
  float mPrimaryVertexY;
  float mPrimaryVertexZ;
  /// Need magnetic field for the helix construction
  float mBField;

  /// Particle positions at freeze-out (duplicates hidden info and must be removed)
  float *mXfr;
  float *mYfr;
  float *mZfr;
  float *mTfr;
  int   *mPdgId;

  /* Th stuff */
  // Fab private : add mutable
  StHbtHiddenInfo* mHiddenInfo; //!
  /***/
};

#endif //#define StHbtTrack_h
