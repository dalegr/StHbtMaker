/**
 * Description: Main class holding track information (before identification)
 *
 * StHbtTrack holds all the necessary information about a track that is
 * required during femtoscopic analysis. This class is filled with information
 * from the input stream by the reader. A particle has a link back to the Track
 * it was created from, so we do not copy the information.
 */

/// StHbtMaker headers
#include "StHbtTrack.h"

//________________
StHbtTrack::StHbtTrack() :
  mId(0), mFlag(0), mNHits(0), mNHitsPoss(0), mNHitsDedx(0), mChi2(0), mDedx(0),
  mNSigmaElectron(-30), mNSigmaPion(-30), mNSigmaKaon(-30), mNSigmaProton(-30),
  mPidProbElectron(0), mPidProbPion(0), mPidProbKaon(0), mPidProbProton(0),
  mMap{}, mTofBeta(0),
  mPrimaryPx(0), mPrimaryPy(0), mPrimaryPz(0), mGlobalPx(0), mGlobalPy(0), mGlobalPz(0),
  mDcaX(-999), mDcaY(-999), mDcaZ(-999),
  mPrimaryVertexX(0), mPrimaryVertexY(0), mPrimaryVertexZ(0),
  mXfr(0), mYfr(0), mZfr(0), mTfr(0), mPdgId(0) {
    
  /// Default constructor
  mHiddenInfo = nullptr;
}

//________________
StHbtTrack::StHbtTrack(const StHbtTrack& t) { 

  /// Copy constructor
  mId = t.mId;
  mFlag = t.mFlag;     
  mNHits = t.mNHits;
  mNHitsPoss = t.mNHitsPoss;
  mNHitsDedx = t.mNHitsDedx;
  mChi2 = t.mChi2;
  mDedx = t.mDedx;
  mNSigmaElectron = t.mNSigmaElectron;
  mNSigmaPion = t.mNSigmaPion;
  mNSigmaKaon = t.mNSigmaKaon;
  mNSigmaProton = t.mNSigmaProton;
  mPidProbElectron = t.mPidProbElectron;
  mPidProbPion = t.mPidProbPion;
  mPidProbKaon = t.mPidProbKaon;
  mPidProbProton = t.mPidProbProton;
  mDcaX = t.mDcaX; mDcaY = t.mDcaY; mDcaZ = t.mDcaZ;
  mMap[0] = t.mMap[0]; mMap[1] = t.mMap[1];
  mTofBeta = t.mTofBeta;
  mPrimaryPx = t.mPrimaryPx;
  mPrimaryPy = t.mPrimaryPy;
  mPrimaryPz = t.mPrimaryPz;
  mGlobalPx = t.mGlobalPx;
  mGlobalPy = t.mGlobalPy;
  mGlobalPz = t.mGlobalPz;
  mPrimaryVertexX = t.mPrimaryVertexX;
  mPrimaryVertexY = t.mPrimaryVertexY;
  mPrimaryVertexZ = t.mPrimaryVertexZ;
  mXfr = t.mXfr;
  mYfr = t.mYfr;
  mZfr = t.mZfr;
  mTfr = t.mTfr;
  mPdgId = t.mPdgId;
  
  if ( t.validHiddenInfo() ) {
    mHiddenInfo = t.getHiddenInfo()->clone();
  }
  else {
    mHiddenInfo = nullptr;
  }
}

//_________________
StHbtTrack& StHbtTrack::operator=(const StHbtTrack& trk) {
  if( this != &trk ) {
    mId = trk.mId;
    mFlag = trk.mFlag;
    mNHits = trk.mNHits;
    mNHitsPoss = trk.mNHitsPoss;
    mNHitsDedx = trk.mNHitsDedx;
    mChi2 = trk.mChi2;
    mDedx = trk.mDedx;
    mNSigmaElectron = trk.mNSigmaElectron;
    mNSigmaPion = trk.mNSigmaPion;
    mNSigmaKaon = trk.mNSigmaKaon;
    mNSigmaProton = trk.mNSigmaProton;
    mPidProbElectron = trk.mPidProbElectron;
    mPidProbPion = trk.mPidProbPion;
    mPidProbKaon = trk.mPidProbKaon;
    mPidProbProton = trk.mPidProbProton;
    mMap[0] = trk.mMap[0];
    mMap[1] = trk.mMap[1];
    mTofBeta = trk.mTofBeta;
    mPrimaryPx = trk.mPrimaryPx;
    mPrimaryPy = trk.mPrimaryPy;
    mPrimaryPz = trk.mPrimaryPz;
    mGlobalPx = trk.mGlobalPx;
    mGlobalPy = trk.mGlobalPy;
    mGlobalPz = trk.mGlobalPz;
    mDcaX = trk.mDcaX;
    mDcaY = trk.mDcaY;
    mDcaZ = trk.mDcaZ;
    mPrimaryVertexX = trk.mPrimaryVertexX;
    mPrimaryVertexY = trk.mPrimaryVertexY;
    mPrimaryVertexZ = trk.mPrimaryVertexZ;
    mBField = trk.mBField;

    if ( trk.mXfr ) {
      if( !mXfr ) {
	mXfr = new float;
      }
      mXfr = trk.mXfr;
    }

    if ( trk.mYfr ) {
      if( !mYfr ) {
	mYfr = new float;
      }
      mYfr = trk.mYfr;
    }

    if ( trk.mZfr ) {
      if( !mZfr ) {
	mZfr = new float;
      }
      mZfr = trk.mZfr;
    }

    if ( trk.mTfr ) {
      if( !mTfr ) {
	mTfr = new float;
      }
      mTfr = trk.mTfr;
    }

    if (trk.mPdgId) {
      if (!mPdgId) {
	mPdgId = new int;
      }
      mPdgId = trk.mPdgId;
    }

    if(mHiddenInfo) delete mHiddenInfo;
    mHiddenInfo = trk.validHiddenInfo() ? trk.getHiddenInfo()->clone() : nullptr;
  }

  return *this;
}

//_________________
StHbtTrack::~StHbtTrack() {
  if (mHiddenInfo) delete mHiddenInfo;
  if (mXfr) delete mXfr;
  if (mYfr) delete mYfr;
  if (mZfr) delete mZfr;
  if (mTfr) delete mTfr;
  if (mPdgId) delete mPdgId;
}

//_________________
float StHbtTrack::massSqr() const {
  float massSqr = -999.;
  if( isTofTrack() ) {
    massSqr = gPtot2() * ( invBeta2() - 1.);
  }
  return massSqr;
}

//_________________
void StHbtTrack::setNSigmaElectron(const float& ns) {
  mNSigmaElectron = ( TMath::Abs(ns * 1000.) > std::numeric_limits<short>::max() ?
		      ( (ns>0) ? std::numeric_limits<short>::max() : std::numeric_limits<short>::min() ) :
		      (short)( ns * 1000.) );
}

//_________________
void StHbtTrack::setNSigmaPion(const float& ns) {
  mNSigmaPion = ( TMath::Abs(ns * 1000.) > std::numeric_limits<short>::max() ?
		  ( (ns>0) ? std::numeric_limits<short>::max() : std::numeric_limits<short>::min() ) :
		  (short)( ns * 1000.) );
}

//_________________
void StHbtTrack::setNSigmaKaon(const float& ns) {
  mNSigmaKaon = ( TMath::Abs(ns * 1000.) > std::numeric_limits<short>::max() ?
		  ( (ns>0) ? std::numeric_limits<short>::max() : std::numeric_limits<short>::min() ) :
		  (short)( ns * 1000.) );
}

//_________________
void StHbtTrack::setNSigmaProton(const float& ns) {
  mNSigmaProton = ( TMath::Abs(ns * 1000.) > std::numeric_limits<short>::max() ?
		    ( (ns>0) ? std::numeric_limits<short>::max() : std::numeric_limits<short>::min() ) :
		    (short)( ns * 1000.) );
}

//_________________
void StHbtTrack::setChi2(const float& x) {
  mChi2 = ( ( x * 1000.) > std::numeric_limits<unsigned short>::max() ?
	    std::numeric_limits<unsigned short>::max() :
	    (unsigned short)( x * 1000.) );
}

//_________________
void StHbtTrack::setPidProbElectron(const float& prob) {
  mPidProbElectron = ( (prob * 10000.) > std::numeric_limits<unsigned short>::max() ?
		       std::numeric_limits<unsigned short>::max() :
		       (unsigned short)(prob * 10000.) );
}

//_________________
void StHbtTrack::setPidProbPion(const float& prob) {
  if( prob < 0 ) {
    mPidProbPion = std::numeric_limits<unsigned short>::max();
  }
  else {
    mPidProbPion = ( (prob * 10000.) > std::numeric_limits<unsigned short>::max() ?
		     std::numeric_limits<unsigned short>::max() :
		     (unsigned short)(prob * 10000.) );
  }
}

//_________________
void StHbtTrack::setPidProbKaon(const float& prob) {
  if( prob < 0 ) {
    mPidProbKaon = std::numeric_limits<unsigned short>::max();
  }
  else {
    mPidProbKaon = ( (prob * 10000.) > std::numeric_limits<unsigned short>::max() ?
		     std::numeric_limits<unsigned short>::max() :
		     (unsigned short)(prob * 10000.) );
  }
}

//_________________
void StHbtTrack::setPidProbProton(const float& prob) {
  if( prob < 0 ) {
    mPidProbProton = std::numeric_limits<unsigned short>::max();
  }
  else {
    mPidProbProton = ( (prob * 10000.) > std::numeric_limits<unsigned short>::max() ?
		       std::numeric_limits<unsigned short>::max() :
		       (unsigned short)(prob * 10000.) );
  }
}

//_________________
void StHbtTrack::setDedx(const double& dEdx) {
  if( dEdx < 0 ) {
    mDedx = 0;
  }
  else {
    mDedx = ( (dEdx * 1e9) > std::numeric_limits<unsigned short>::max() ?
	      std::numeric_limits<unsigned short>::max() :
	      (unsigned short)(dEdx * 1e9) );
  }
}

//_________________
void StHbtTrack::setBeta(const float& beta) {
  if( beta <= 0 ) {
    mTofBeta = 0;
  }
  else {
    mTofBeta = ( (beta * 20000.) > std::numeric_limits<unsigned short>::max() ?
		 std::numeric_limits<unsigned short>::max() :
		 (unsigned short)(beta * 20000.) );
  }
}

//_________________
StHbtPhysicalHelix StHbtTrack::helix() const {
  return StHbtPhysicalHelix( pMom(), primaryVertex(),
			     mBField * kilogauss,
			     static_cast<float>( charge() ) );
}

//_________________
StHbtPhysicalHelix StHbtTrack::gHelix() const {
  return StHbtPhysicalHelix( gMom(), origin(),
			     mBField * kilogauss,
			     static_cast<float>( charge() ) );
}

//_________________
void StHbtTrack::setEmissionPointX(const float& x) {
  if( !mXfr ) {
    mXfr = new float;
  }
  *mXfr = x;
}

//_________________
void StHbtTrack::setEmissionPointY(const float& y) {
  if( !mYfr ) {
    mYfr = new float;
  }
  *mYfr = y;
}

//_________________
void StHbtTrack::setEmissionPointZ(const float& z) {
  if( !mZfr ) {
    mZfr = new float;
  }
  *mZfr = z;
}

//_________________
void StHbtTrack::setEmissionPointT(const float& t) {
  if( !mTfr ) {
    mTfr = new float;
  }
  *mTfr = t;
}

//_________________
void StHbtTrack::setPdgCode(const int& id) {
  if( !mPdgId ) {
    mPdgId = new int;
  }
  *mPdgId = id;
}
