#ifndef StHbtParticle_h
#define StHbtParticle_h

/// StHbtMaker headers
#include "StHbtTypes.h"
#include "StHbtTrack.h"
#include "StHbtV0.h"
#include "StHbtKink.h"
#include "StHbtXi.h"
#include "StHbtHiddenInfo.h"
#include "StHbtPhysicalHelix.h"

/// ROOT headers
#include "TLorentzVector.h"
#include "TVector3.h"

//_________________
class StHbtParticle {

 public:
  /// Default constructor
  StHbtParticle();
  /// Copy constructor
  StHbtParticle(const StHbtParticle &copy);
  /// Constructor for StHbtTrack
  StHbtParticle(const StHbtTrack* const hbtTrack, const double& mass);
  /// Constructor for StHbtV0
  StHbtParticle(const StHbtV0* const hbtV0, const double& mass);
  /// Constructor for StHbtKink
  StHbtParticle(const StHbtKink* const hbtKink, const double& mass);
  /// Constructor for StHbtXi
  StHbtParticle(const StHbtXi* const hbtXi, const double& mass);
  /// Constructor copy
  StHbtParticle& operator=(const StHbtParticle& copy);
  /// Default destructor
  ~StHbtParticle();


  /// Information important for the track merging estimation
  static float mInnerTpcRadius;  //[cm]
  static float mOuterTpcRadius;  //[cm]
  static float mTpcHalfLength;   //[cm]
  static const unsigned short mNumberOfPoints = 11;
  static const unsigned short mNumberOfPadrows = 45;
  static float tRowRadius[mNumberOfPadrows];

  /**
   * Getters
   **/
  
  StHbtTrack *track() const                { return mTrack; }
  StHbtV0    *v0() const                   { return mV0; }
  StHbtKink  *kink() const                 { return mKink; }
  StHbtXi    *xi() const                   { return mXi; }
  TLorentzVector fourMomentum() const      { return TLorentzVector( mPx, mPy, mPz, mEnergy ); }
  double      eta() const                  { return fourMomentum().Eta(); }
  double      pseudoRapidity()             { return eta(); }
  double      rapidity()                   { return fourMomentum().Rapidity(); }
  double      phi() const                  { return fourMomentum().Phi(); }
  TVector3    momentum() const             { return fourMomentum().Vect(); }
  TVector3    p() const                    { return momentum(); }
  double      px() const                   { return momentum().X(); }
  double      py() const                   { return momentum().Y(); }
  double      pz() const                   { return momentum().Z(); }
  double      ptot() const                 { return momentum().Mag(); }
  double      ptot2() const                { return momentum().Mag2(); }
  double      pt() const                   { return momentum().Perp(); }
  double      energy() const               { return fourMomentum().Energy(); }
  double      e() const                    { return energy(); }
  double      t() const                    { return fourMomentum().T(); }
  double      energy2() const              { return ( energy() * energy() ); }
  
  TVector3 primaryVertex() const
  { return TVector3( mPrimaryVertexX, mPrimaryVertexY, mPrimaryVertexZ ); }

  /// StHbtTrack information
  StHbtPhysicalHelix helix() const         { return mTrack ? mTrack->helix() : StHbtPhysicalHelix(); }
  unsigned int topologyMap(const unsigned int& word) const { return mTrack ? mTrack->topologyMap(word) : 0; }
  unsigned short nHits() const             { return mTrack ? mTrack->nHits() : 0; }
  unsigned short numberOfHits() const      { return nHits(); }
  unsigned short trackId() const           { return mTrack ? mTrack->id() : -1; }
  /// Position of track entrance and exit TPC points assuming start it at (0,0,0)
  TVector3 nominalTpcExitPoint() const
  { return TVector3( mTpcTrackExitPointX, mTpcTrackExitPointY, mTpcTrackExitPointZ ); }
  TVector3 nominalTpcEntrancePoint() const
  { return TVector3( mTpcTrackEntrancePointX, mTpcTrackEntrancePointY, mTpcTrackEntrancePointZ ); }
  /// Information about track positions at mNumberOfPoints points in TPC
  const float *nominalPosSampleX() const   { return &mNominalPosSampleX[0]; }
  const float *nominalPosSampleY() const   { return &mNominalPosSampleY[0]; }
  const float *nominalPosSampleZ() const   { return &mNominalPosSampleZ[0]; }
  float nominalPosSampleX(const int& point) const;
  float nominalPosSampleY(const int& point) const;
  float nominalPosSampleZ(const int& point) const;
  TVector3 nominalPosSample(const int& i) const;
  /// Information about hit positions in TPC local coordinate system
  float *z()                    { return &mZ[0]; }
  float *u()                    { return &mU[0]; }
  int *sect()                   { return &mSect[0]; }

  /// Purity estimations
  void   calculatePurity();
  double pionPurity();
  double kaonPurity();
  double protonPurity();

  /// StHbtV0 information
  TVector3 secondaryVertex() const
  { return TVector3( secondaryVertexX() , secondaryVertexY(), secondaryVertexZ() ); }
  float    secondaryVertexX() const;
  float    secondaryVertexY() const;
  float    secondaryVertexZ() const;
  TVector3 decayVertexPosition() const     { return secondaryVertex(); }
  unsigned short negTrackId() const        { return mV0->idNeg(); }
  unsigned short posTrackId() const        { return mV0->idPos(); }
  TVector3 tpcV0PosExitPoint() const
  { return TVector3( tpcV0PosExitPointX(), tpcV0PosExitPointY(), tpcV0PosExitPointZ() ); }
  float    tpcV0PosExitPointX() const;      
  float    tpcV0PosExitPointY() const;
  float    tpcV0PosExitPointZ() const;
  TVector3 tpcV0PosEntrancePoint() const
  { return TVector3( tpcV0PosEntrancePointX(), tpcV0PosEntrancePointY(), tpcV0PosEntrancePointZ() ); }
  float    tpcV0PosEntrancePointX() const;      
  float    tpcV0PosEntrancePointY() const;
  float    tpcV0PosEntrancePointZ() const;
  TVector3 tpcV0NegExitPoint() const
  { return TVector3( tpcV0NegExitPointX(), tpcV0NegExitPointY(), tpcV0NegExitPointZ() ); }
  float    tpcV0NegExitPointX() const;      
  float    tpcV0NegExitPointY() const;
  float    tpcV0NegExitPointZ() const;
  TVector3 tpcV0NegEntrancePoint() const
  { return TVector3( tpcV0NegEntrancePointX(), tpcV0NegEntrancePointY(), tpcV0NegEntrancePointZ() ); }
  float    tpcV0NegEntrancePointX() const;      
  float    tpcV0NegEntrancePointY() const;
  float    tpcV0NegEntrancePointZ() const; 
  
  /// This will be called only for V0s
  const float *tpcV0NegPosSampleX() const   { return (mTpcV0NegPosSampleX) ? &mTpcV0NegPosSampleX[0] : nullptr; }
  const float *tpcV0NegPosSampleY() const   { return (mTpcV0NegPosSampleY) ? &mTpcV0NegPosSampleY[0] : nullptr; }
  const float *tpcV0NegPosSampleZ() const   { return (mTpcV0NegPosSampleZ) ? &mTpcV0NegPosSampleZ[0] : nullptr; }
  float tpcV0NegPosSampleX(const int& point) const;
  float tpcV0NegPosSampleY(const int& point) const;
  float tpcV0NegPosSampleZ(const int& point) const;
  TVector3 tpcV0NegPosSample(const int& i) const;
  /// This will be called only for V0s (info about hit positions in the local
  /// coordinate system)
  float *v0NegZ()               { return (mV0NegZ) ? &mV0NegZ[0] : nullptr; }
  float *v0NegU()               { return (mV0NegU) ? &mV0NegU[0] : nullptr; }
  int *v0NegSect()              { return (mV0NegSect) ? &mV0NegSect[0] : nullptr;}
  
  /// The following method is for explicit internal calculation to fill datamembers.
  /// It is invoked automatically if StHbtParticle constructed from StHbtTrack
  void calculateTpcExitAndEntrancePoints( StHbtPhysicalHelix *tHelix,
					  TVector3 *PrimVert,
					  TVector3 *SecVert,
					  TVector3 *tmpTpcEntrancePoint,
					  TVector3 *tmpTpcExitPoint,
					  TVector3 *tmpPosSample,
					  float    *tmpZ,
					  float    *tmpU,
					  int      *tmpSect );

  /**
   * Setters
   **/
  
  void resetFourMomentum(const TLorentzVector& vec)
  { mPx = vec.Px(); mPy = vec.Py(); mPz = vec.Pz(); mEnergy = vec.E(); }
  void setPrimaryVertex(const TVector3& pvtx)
  { mPrimaryVertexX = pvtx.X(); mPrimaryVertexY = pvtx.Y(); mPrimaryVertexZ = pvtx.Z(); }
  /// Position of track entrance and exit TPC points assuming start it at (0,0,0)
  void setNominalTpcExitPoint(const TVector3& point)
  { mTpcTrackExitPointX = point.X(); mTpcTrackExitPointY = point.Y(); mTpcTrackExitPointZ = point.Z(); }
  void setNominalTpcEntrancePoint(const TVector3& point)
  { mTpcTrackEntrancePointX = point.X(); mTpcTrackEntrancePointY = point.Y(); mTpcTrackEntrancePointZ = point.Z(); }

  /// StHbtV0 information
  void setSecondaryVertex(const TVector3& vtx) {
    setSecondaryVertexX( vtx.X() );
    setSecondaryVertexY( vtx.Y() );
    setSecondaryVertexZ( vtx.Z() ); }
  void setSecondaryVertexX(const float& val);
  void setSecondaryVertexY(const float& val);
  void setSecondaryVertexZ(const float& val);
  void setSecondaryVertex(StHbtV0 *v0) {
    setSecondaryVertexX( v0->decayPoint().X() );
    setSecondaryVertexY( v0->decayPoint().Y() );
    setSecondaryVertexZ( v0->decayPoint().Z() );
  }
  void setDecayPoint(const TVector3& vtx)              { setSecondaryVertex( vtx ); }
  void setDecayPoint(StHbtV0 *v0)                      { setSecondaryVertex( v0 ); }

  void setTpcV0PosExitPoint(const TVector3& vec) {
    setTpcV0PosExitPointX( vec.X() );
    setTpcV0PosExitPointY( vec.Y() );
    setTpcV0PosExitPointZ( vec.Z() );
  }
  void setTpcV0PosExitPointX(const float& val);
  void setTpcV0PosExitPointY(const float& val);
  void setTpcV0PosExitPointZ(const float& val);
  void setTpcV0PosEntrancePoint(const TVector3& vec) {
    setTpcV0PosEntrancePointX( vec.X() );
    setTpcV0PosEntrancePointY( vec.Y() );
    setTpcV0PosEntrancePointZ( vec.Z() );
  }
  void setTpcV0PosEntrancePointX(const float& val);
  void setTpcV0PosEntrancePointY(const float& val);
  void setTpcV0PosEntrancePointZ(const float& val);
  void setTpcV0NegExitPoint(const TVector3& vec) {
    setTpcV0NegExitPointX( vec.X() );
    setTpcV0NegExitPointY( vec.Y() );
    setTpcV0NegExitPointZ( vec.Z() );
  }
  void setTpcV0NegExitPointX(const float& val);
  void setTpcV0NegExitPointY(const float& val);
  void setTpcV0NegExitPointZ(const float& val);
  void setTpcV0NegEntrancePoint(const TVector3& vec) {
    setTpcV0NegEntrancePointX( vec.X() );
    setTpcV0NegEntrancePointY( vec.Y() );
    setTpcV0NegEntrancePointZ( vec.Z() );
  }
  void setTpcV0NegEntrancePointX(const float& val);
  void setTpcV0NegEntrancePointY(const float& val);
  void setTpcV0NegEntrancePointZ(const float& val);
  

  /// Information about track positions at mNumberOfPoints points in TPC
  void setNominalPosSample(float x[mNumberOfPoints], float y[mNumberOfPoints], float z[mNumberOfPoints]);
  void setNominalPosSample(TVector3 pos[mNumberOfPoints]);
  void setNominalPosSampleX(const int& i, const float& val);
  void setNominalPosSampleY(const int& i, const float& val);
  void setNominalPosSampleZ(const int& i, const float& val);
  void setNominalPosSampleX(float x[mNumberOfPoints]);
  void setNominalPosSampleY(float y[mNumberOfPoints]);
  void setNominalPosSampleZ(float z[mNumberOfPoints]);

  /// This will be called only for V0s
  void setTpcV0NegPosSample(float x[mNumberOfPoints], float y[mNumberOfPoints], float z[mNumberOfPoints]);
  void setTpcV0NegPosSample(TVector3 vec[mNumberOfPoints]);
  void setTpcV0NegPosSampleX(float x[mNumberOfPoints]);
  void setTpcV0NegPosSampleY(float y[mNumberOfPoints]);
  void setTpcV0NegPosSampleZ(float z[mNumberOfPoints]);
  void setTpcV0NegPosSampleX(const int& i, const float& val);
  void setTpcV0NegPosSampleY(const int& i, const float& val);
  void setTpcV0NegPosSampleZ(const int& i, const float& val);
  
  /// Information about hit positions in TPC local coordinate system
  void setZ(float z[mNumberOfPadrows]);
  void setU(float u[mNumberOfPadrows]);
  void setSect(int sector[mNumberOfPadrows]);

  /// This will be called only for V0s (info about hit positions in the local
  /// coordinate system)
  void setV0NegZ(float z[mNumberOfPadrows]);
  void setV0NegU(float u[mNumberOfPadrows]);
  void setV0NegSect(int sect[mNumberOfPadrows]);

  /// Information for the theoretical estimations
  StHbtHiddenInfo*  hiddenInfo() const             { return mHiddenInfo; }
  StHbtHiddenInfo*  getHiddenInfo() const          { return hiddenInfo(); }
  bool validHiddenInfo() const                     { return (mHiddenInfo) ? true : false; }
  void setHiddenInfo(StHbtHiddenInfo* aHiddenInfo) { mHiddenInfo = aHiddenInfo->clone(); }
  
 private:

  /// Pointer to StHbtTrack
  StHbtTrack *mTrack;
  /// Pointer to StHbtV0
  StHbtV0    *mV0;
  /// Pointer to StHbtKink
  StHbtKink  *mKink;
  /// Pointer to StHbtXi
  StHbtXi    *mXi;

  /// Four-momentum components
  float mPx;
  float mPy;
  float mPz;
  float mEnergy;
  /// TPC entrance and exit points of the track
  float mTpcTrackEntrancePointX;
  float mTpcTrackEntrancePointY;
  float mTpcTrackEntrancePointZ;
  float mTpcTrackExitPointX;
  float mTpcTrackExitPointY;
  float mTpcTrackExitPointZ;
  
  /// Calculated track positions at each mNumberOfPoints
  float mNominalPosSampleX[mNumberOfPoints];
  float mNominalPosSampleY[mNumberOfPoints];
  float mNominalPosSampleZ[mNumberOfPoints];
  /// Next are the pointers (placeholders) for positions
  /// of the negative V0 daughter track at mNumberOfPoints
  /// in TPC. We will use *new* operator when the default or
  /// StHbtV0 constructors are called. For positive V0 daughters
  /// we will use existing mNominalPosSample arrays
  float *mTpcV0NegPosSampleX;
  float *mTpcV0NegPosSampleY;
  float *mTpcV0NegPosSampleZ;

  /// Spacial hit positions at each padrow of mNumberOfPadrows
  /// in TPC local coordinate system
  float mZ[mNumberOfPadrows];
  float mU[mNumberOfPadrows];
  int   mSect[mNumberOfPadrows];
  /// Next are the pointers (placeholders) for hit positions
  /// of the negative V0 daughter track at each padrow of mNumberOfPadrows
  /// at in TPC local coordinate system. We will use *new* operator
  /// when the default or StHbtV0 constructors are called.
  /// For positive V0 daughters we will use existing
  /// mZ,mU and mSect arrays
  float *mV0NegZ;
  float *mV0NegU;
  int   *mV0NegSect;
  
  /// Hidden info for simulated data
  StHbtHiddenInfo* mHiddenInfo;

  /// Purity parametrization parameters
  float mPurity[6];
  static float mPrimPimPar0;
  static float mPrimPimPar1;
  static float mPrimPimPar2;
  static float mPrimPipPar0;
  static float mPrimPipPar1;
  static float mPrimPipPar2;
  static float mPrimPmPar0;
  static float mPrimPmPar1;
  static float mPrimPmPar2;
  static float mPrimPpPar0;
  static float mPrimPpPar1;
  static float mPrimPpPar2;

  /// Primary vertex position
  float mPrimaryVertexX;
  float mPrimaryVertexY;
  float mPrimaryVertexZ;

  /// To save the memory lets use pointers for next variables
  
  /// Secondary vertex position (V0 decay point)
  float *mSecondaryVertexX;
  float *mSecondaryVertexY;
  float *mSecondaryVertexZ;

  /// Helices of positive and negative V0 dauthers can
  /// be returned from the StHbtTrack information
  /// Thus, for V0 daugthers we store only calculated TpcEntrance/ExitPoints
  float *mTpcV0PosEntrancePointX;
  float *mTpcV0PosEntrancePointY;
  float *mTpcV0PosEntrancePointZ;
  float *mTpcV0PosExitPointX;
  float *mTpcV0PosExitPointY;
  float *mTpcV0PosExitPointZ;

  float *mTpcV0NegEntrancePointX;
  float *mTpcV0NegEntrancePointY;
  float *mTpcV0NegEntrancePointZ;
  float *mTpcV0NegExitPointX;
  float *mTpcV0NegExitPointY;
  float *mTpcV0NegExitPointZ;
};

#endif // #define StHbtParticle_h
