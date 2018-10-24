/**
 * Description: The basic cut for events.
 *
 * Only cuts on event multiplicity, z-vertex position and trigger
 */

#ifndef StHbtBasicEventCut_h
#define StHbtBasicEventCut_h

/// C++ headers
#include <vector>

/// StHbtMaker headers
#include "StHbtEvent.h"
#include "StHbtEventCut.h"
#include "StHbtString.h"

/// ROOT headers
#include "TList.h"
#include "TString.h"

//_________________
class StHbtBasicEventCut : public StHbtEventCut {

 public:
  /// Constructor
  StHbtBasicEventCut();
  /// Copy contructor
  StHbtBasicEventCut(const StHbtBasicEventCut& c);
  /// Assignment operator
  StHbtBasicEventCut& operator=(const StHbtBasicEventCut& c);
  /// Destructor
  virtual ~StHbtBasicEventCut();
  
  /// Check bad run flag
  void setCheckBadRun(bool check) { mCheckBadRun = check; }
  /// Set min and max acceptable event multiplicity
  void setEventMult(const int& lo, const int& hi)     { mRefMult[0] = lo; mRefMult[1] = hi; }
  /// Set min and max acceptable vertex z-coordinate
  void setVertZPos(const float& lo, const float& hi) { mVertZPos[0] = lo; mVertZPos[1] = hi; }
  /// Set min and max acceptable (Vz-VpdVz) values
  void setVpdVzDiff(const float& lo, const float& hi){ mVpdVzDiff[0] = lo; mVpdVzDiff[1] = hi; }
  /// Set x and y shifts of primary vertex, and min and max acceptrable
  /// radial position of the vertex
  void setVertXShift(const float& shift)             { mVertXShift = shift; }
  void setVertYShift(const float& shift)             { mVertYShift = shift; }
  void setVertRPos(const float& lo, const float& hi) { mVertRPos[0] = lo; mVertRPos[1] = hi; }
  /// Set min and max acceptable values of sphericity
  void setSphericity(const float& lo, const float& hi) { mSphericity[0] = lo; mSphericity[1] = hi; }
  /// Set min and max acceptable TOF tray multiplicity
  void setBTofTrayMult(const int& lo, const int& hi) { mBTofTrayMult[0] = lo; mBTofTrayMult[1] = hi; }
  /// Set min and max acceptable TOF-matched tracks
  void setBTofMatchMult(const int& lo, const int& hi){ mBTofMatch[0] = lo; mBTofMatch[1] = hi; }
  /// Number of events passed
  int nEventsPassed() const                          { return mNEventsPassed; }
  /// Number of events failed
  int nEventsFailed() const                          { return mNEventsFailed; }
  /// Add trigger to select
  void addTriggerId(const unsigned int& id);
  void setTriggerId(const unsigned int& id)          { addTriggerId( id ); }
  /// Set the min and max allowed event plane angle
  void setEventPlaneAngle(const float& lo, const float& hi)  { mPsiEP[0] = lo; mPsiEP[1] = hi; }
  void setEPAngle(const float& lo, const float& hi)  { setEventPlaneAngle( lo, hi ); }

  virtual TList* appendSettings(TList*, const TString& prefix="") const;
  virtual StHbtString report();
  virtual bool pass(const StHbtEvent* event);

  virtual StHbtEventCut* clone() const
  { StHbtBasicEventCut* c = new StHbtBasicEventCut(*this); return c; }

 private:

  /// Check bad run flag. By default it is true (see constructor for more info)
  bool mCheckBadRun;
  /// Range of multiplicity
  unsigned short mRefMult[2];
  /// Range of z-position of vertex
  float mVertZPos[2];
  /// Range of (Vz - VpdVz) of vertex
  float mVpdVzDiff[2];
  /// Range of transverse positions of vertex and their shifts
  float mVertXShift;
  float mVertYShift;
  float mVertRPos[2];
  /// Range of min and max values of event sphericity
  float mSphericity[2];
  /// Range of TOF tray multiplicity
  unsigned short mBTofTrayMult[2];
  /// Range of TOF matched tracks (multplicity)
  unsigned short mBTofMatch[2];
  // Range of centralities
  short mCent9[2];
  /// Range of vzero ep angle
  float mPsiEP[2];
  /// Number of events checked by this cut that passed
  unsigned int mNEventsPassed;
  /// Number of events checked by this cut that failed
  unsigned int mNEventsFailed;
  /// If set, only given trigger will be selected
  std::vector<unsigned int> mTriggersToSelect;

  /// Method that looks at the bad run lists
  bool isInBadRunList(int, const Int_t*, int);

  static const int n_bad_run_numbers[7];
  static const int bad_run_list_7GeV[328];
  static const int bad_run_list_11GeV[27];
  static const int bad_run_list_19GeV[35];
  static const int bad_run_list_27GeV[34];
  static const int bad_run_list_39GeV[38];
  static const int bad_run_list_62GeV[105];
  static const int bad_run_list_200GeV[219];

#ifdef __ROOT__
  ClassDef(StHbtBasicEventCut, 1);
#endif
};

#endif // StHbtBasicEventCut_h
