/**
 * Description: 3D correlation function of identical particles
 * in Bertsch-Pratt coordinate system
 */

#ifndef StHbtCorrFctn3DLCMSSym_h
#define StHbtCorrFctn3DLCMSSym_h

/// Forward declarations
class TH3F;
class StHbtPairCut;

/// Include headers
#include "StHbtCorrFctn.h"

//_________________
class StHbtCorrFctn3DLCMSSym : public StHbtCorrFctn {

 public:

  /// Build the correlation function with parameters.
  ///
  /// \param title The title with which to give the output
  /// \param nbins The number of bins in each direction of , and q
  ///
  StHbtCorrFctn3DLCMSSym(const char* title, const int nbins, const float QHi);

  /// Copy Constructor
  StHbtCorrFctn3DLCMSSym(const StHbtCorrFctn3DLCMSSym& aCorrFctn);

  /// Assignment operator
  StHbtCorrFctn3DLCMSSym& operator=(const StHbtCorrFctn3DLCMSSym& aCorrFctn);

  /// Destructor
  virtual ~StHbtCorrFctn3DLCMSSym();

  virtual StHbtString report();
  virtual void addRealPair(const StHbtPair* aPair);
  virtual void addMixedPair(const StHbtPair* aPair);

  virtual void finish();

  /// Return numerator
  TH3F* numerator()                    { return mNumerator; }
  /// Return denominator
  TH3F* denominator()                  { return mDenominator; }
  /// Return numerator weighed by qinv
  TH3F* numeratorW()                   { return mNumeratorW; }
  /// Return denominator weighed by qinv
  TH3F* denominatorW()                 { return mDenominatorW; }

  void writeOutHistos();
  virtual TList* getOutputList();

  void setUseLCMS(bool useLCMS)        { mUseLCMS = useLCMS; }
  int  getUseLCMS()                    { return mUseLCMS; }
  virtual StHbtCorrFctn* clone() const { return new StHbtCorrFctn3DLCMSSym( *this ); }

 private:
  
  /// Numerator
  TH3F* mNumerator;
  /// Denominator
  TH3F* mDenominator;
  /// Qinv-weighted numerator
  TH3F* mNumeratorW;
  /// Qinv-weighted denominator
  TH3F* mDenominatorW;

  /// False - use PRF, True - use LCMS
  bool mUseLCMS;

#ifdef __ROOT__
  ClassDef(StHbtCorrFctn3DLCMSSym, 1);
#endif
};

#endif // StHbtCorrFctn3DLCMSSym_h
