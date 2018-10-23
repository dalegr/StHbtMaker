/**
 * Description: StHbtEvent holds the event information specific and a track list.
 *
 * StHbtEvent is the "transient microDST". Objects of this class are
 * generated from the input data by an StHbtEventReader, and then presented
 * to the cuts of the various active Analyses.
 */

#ifndef StHbtEvent_h
#define StHbtEvent_h

/// C++ headers
#include <vector>

/// ROOT headers
#include "TVector3.h"
#include "TLorentzVector.h"

/// HbtMaker headers
#include "StHbtTypes.h"
#include "StHbtTrackCollection.h"
#include "StHbtV0Collection.h"
#include "StHbtXiCollection.h"
#include "StHbtKinkCollection.h"

class StHbtTrackCut;
class StHbtV0Cut;
class StHbtXiCut;
class StHbtKinkCut;

//_________________
class StHbtEvent {
  
 public:

  /// Constructor
  StHbtEvent();
  /// Copy constructor
  StHbtEvent(const StHbtEvent& ev, StHbtTrackCut* track=0, StHbtV0Cut* v0=0,
	     StHbtXiCut* xi=0, StHbtKinkCut* kink=0);
  /// Copy constructor
  StHbtEvent& operator=(const StHbtEvent& event);
  /// Destructor
  ~StHbtEvent();
  
  /// Perform rotation
  void rotateZ(const double& angle);

  /**
   * Getters
   **/

  unsigned int eventId() const                 { return mEventNumber; }
  unsigned int runId() const                   { return runNumber(); }
  unsigned int runNumber() const               { return mRunNumber; }
  float magneticField() const                  { return bField(); }
  float bField() const                         { return mMagneticField; }

  unsigned short refMult() const               { return mRefMult; }
  unsigned short refMultPositive() const       { return mRefMultPos; }
  unsigned short refMultNegative() const       { return (mRefMult - mRefMultPos); }
  unsigned short refMult2() const              { return mRefMult2; }
  unsigned short refMult2Positive() const      { return mRefMult2Pos; }
  unsigned short refMult2Negative() const      { return (mRefMult2 - mRefMult2Pos); }
  unsigned short refMultCorr() const           { return mRefMultCorr; }
  unsigned short refMultCorrWeight() const     { return mRefMultCorrWeight; }
  unsigned short grefMult() const              { return mGRefMult; }
  unsigned short grefMultPositive() const      { return mGRefMultPos; }
  unsigned short grefMultNegative() const      { return (mGRefMult - mGRefMultPos); }
  unsigned short btofTrayMultiplicity() const  { return mBTofTrayMultiplicity; }
  unsigned short numberOfBTofMatched() const   { return mNBTOFMatch; }
  unsigned short numberOfBEMCMatched() const   { return mNBEMCMatch; }
  unsigned short numberOfPrimaryTracks() const { return mNumberOfPrimaryTracks; }
  unsigned short numberOfGlobalTracks() const  { return mNumberOfGlobalTracks; }
  unsigned short zdcSumAdcEast() const         { return mZdcSumAdcEast; }
  unsigned short zdcSumAdcWest() const         { return mZdcSumAdcWest; }
  float zdcCoincidenceRate() const             { return mZdcCoincidenceRate; }
  float bbcCoincidenceRate() const             { return mBbcCoincidenceRate; }

  float sphericity() const                     { return mSphericity; }
  float sphericity2() const                    { return mSphericity2; }
  float eventPlaneAngle() const                { return mEventPlaneAngle; }
  float eventPlaneResolution() const           { return mEventPlaneResolution; }
  short cent16() const                         { return mCent16; }
  short cent9() const;

  TVector3 primaryVertex() const
  { return TVector3(mPrimaryVertexPositionX, mPrimaryVertexPositionY, mPrimaryVertexPositionZ); }
  float vpdVz() const                          { return mVpdVz; }
  float vpdVzDiff() const                      { return ( primaryVertex().Z() - vpdVz() ); }
  float ranking() const                        { return mRanking; }

  std::vector<unsigned int> triggerIds() const { return mTriggerIds; }
  bool isTrigger(const unsigned int& word) const;
  unsigned int l3TriggerAlgorithm(const unsigned int& i) const { return mL3TriggerAlgorithm[i]; }

  StHbtTrackCollection *trackCollection() const { return mTrackCollection; }
  StHbtV0Collection *v0Collection() const       { return mV0Collection; }
  StHbtXiCollection *xiCollection() const       { return mXiCollection; }
  StHbtKinkCollection *kinkCollection() const   { return mKinkCollection; }
  
  /**
   * Setters
   **/

  void setEventNumber(const unsigned int& id) { mEventNumber = id; }
  void setEventId(const unsigned int& id)     { mEventNumber = id; }
  void setRunNumber(const unsigned int& n)    { mRunNumber = n; }
  void setRunNumber(const int& n)             { mRunNumber = n; }
  void setMagneticField(const float& bField)  { mMagneticField = bField; }
  void setBField(const float& bField)         { mMagneticField = bField; }

  void setRefMult(const int& mult)            { mRefMult = (mult>0) ? (unsigned short)mult : 0; }
  void setRefMultPos(const int& mult)         { mRefMultPos = (mult>0) ? (unsigned short)mult : 0; }
  void setRefMult2(const int& mult)           { mRefMult2 = (mult>0) ? (unsigned short)mult : 0; }
  void setRefMult2Pos(const int& mult)        { mRefMult2Pos = (mult>0) ? (unsigned short)mult : 0; }
  void setRefMultCorr(const float& mult)      { mRefMultCorr = (mult>0) ? (unsigned short)mult : 0; }
  void setRefMultCorrWeight(const float& wgt) { mRefMultCorrWeight = wgt; }
  void setGRefMult(const int& mult)           { mGRefMult = (mult>0) ? (unsigned short)mult : 0; }
  void setGRefMultPos(const int& mult)        { mGRefMultPos = (mult>0) ? (unsigned short)mult : 0; }
  void setBTofTrayMult(const int& mult)       { mBTofTrayMultiplicity = (mult>0) ? (unsigned short)mult : 0; }
  void setNumberOfBTofMatched(const int& mult){ mNBTOFMatch = (mult>0) ? (unsigned short)mult : 0; }
  void setNumberOfBEMCMatched(const int& mult){ mNBEMCMatch = (mult>0) ? (unsigned short)mult : 0; }
  void setNumberOfPrimaryTracks(const int& mult)
  { mNumberOfPrimaryTracks = (mult>0) ? (unsigned short)mult : 0; }
  void setNumberOfGlobalTracks(const int& mult)  { mNumberOfGlobalTracks = (mult>0) ? (unsigned short) mult: 0; }
  void setZdcAdcEast(const float& adc)        { mZdcSumAdcEast = (adc>0) ? (unsigned short)adc : 0; }
  void setZdcAdcEast(const int& adc)          { mZdcSumAdcEast = (adc>0) ? (unsigned short)adc : 0; }
  void setZdcAdcWest(const float& adc)        { mZdcSumAdcWest = (adc>0) ? (unsigned short)adc : 0; }
  void setZdcAdcWest(const int& adc)          { mZdcSumAdcWest = (adc>0) ? (unsigned short)adc : 0; }
  void setZdcCoincidenceRate(const float& rt) { mZdcCoincidenceRate = rt; }
  void setBbcCoincidenceRate(const float& rt) { mBbcCoincidenceRate = rt; }

  void setSphericity(const float& sph)        { mSphericity = (sph>=0) ? (char)(sph * 100.) : -1; }
  void setSphericity2(const float& sph)       { mSphericity2 = (sph>=0) ? (char)(sph * 100.) : -1; }
  void setEventPlaneAngle(const float& angle) { mEventPlaneAngle = angle; }
  void setEventPlaneResolution(const float& res) { mEventPlaneResolution = res; }
  void setCent16(const int& cent)             { mCent16 = cent; }

  void setPrimaryVertex(const float& x, const float& y, const float& z)
  { mPrimaryVertexPositionX = x; mPrimaryVertexPositionY = y; mPrimaryVertexPositionZ = z; }
  void setPrimaryVertex(const TVector3& pvtx)
  { mPrimaryVertexPositionX = pvtx.X(); mPrimaryVertexPositionY = pvtx.Y(); mPrimaryVertexPositionZ = pvtx.Z(); }
  void setPrimaryVertexX(const float& x)      { mPrimaryVertexPositionX = x; }
  void setPrimaryVertexY(const float& y)      { mPrimaryVertexPositionX = y; }
  void setPrimaryVertexZ(const float& z)      { mPrimaryVertexPositionX = z; }
  void setVpdVz(const float& vpdVz)           { mVpdVz = vpdVz; }
  void setRanking(const float& ranking)       { mRanking = ranking; }

  void setTriggerIds(const std::vector<unsigned int>& ids) { mTriggerIds = ids; }
  void addTriggerId(const unsigned int& id);
  void setL3TriggerAlgorithm(const unsigned int& i, const unsigned int& t)
  { mL3TriggerAlgorithm[i] = t; }

 private:

  /// Global information
  unsigned int mEventNumber;
  unsigned int mRunNumber;
  float mMagneticField;

  /// Information about hits and tracks
  unsigned short mRefMult;
  unsigned short mRefMultPos;
  unsigned short mRefMultCorr;         // From StRefMultCorr package
  unsigned short mRefMultCorrWeight;   // From StRefMultCorr package
  unsigned short mRefMult2;
  unsigned short mRefMult2Pos;
  unsigned short mGRefMult;
  unsigned short mGRefMultPos;
  unsigned short mBTofTrayMultiplicity;
  unsigned short mNBTOFMatch;
  unsigned short mNBEMCMatch;
  unsigned short mNumberOfPrimaryTracks;
  unsigned short mNumberOfGlobalTracks;
  unsigned short mZdcSumAdcEast;
  unsigned short mZdcSumAdcWest;
  float mZdcCoincidenceRate;
  float mBbcCoincidenceRate;

  /// Event properties (|eta|<0.5 and |eta|<1)
  float mSphericity;
  float mSphericity2;
  float mEventPlaneAngle;
  float mEventPlaneResolution;
  char  mCent16;

  /// Primary vertex information
  float mPrimaryVertexPositionX;
  float mPrimaryVertexPositionY;
  float mPrimaryVertexPositionZ;
  float mVpdVz;
  float mRanking;

  /// Trigger properties
  std::vector<unsigned int> mTriggerIds;
  unsigned int mL3TriggerAlgorithm[4];

  /// Hbt collections
  StHbtTrackCollection* mTrackCollection;
  StHbtV0Collection* mV0Collection;
  StHbtXiCollection* mXiCollection;
  StHbtKinkCollection* mKinkCollection;
};

#endif // StHbtEvent_h
