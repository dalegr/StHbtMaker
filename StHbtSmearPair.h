/**
 * Description: given a StHbtPair, this class provides a corresponding
 *     StHbtPair whose constituent StHbtParticles' momenta have been
 *     smeared according to a parameterization of the STAR momentum
 *     resolution.
 *     >> The input StHbtPair is not altered in anyway <<
 *
 */

#ifndef StHbtSmearPair_h
#define StHbtSmearPair_h

/// StHbtMaker headers
#include "StHbtPair.h"

/// ROOT headers
#include "TLorentzVector.h"
#include "TRandom3.h"

//_________________
class StHbtSmearPair {
  
 public:
  /// Default constructor
  StHbtSmearPair();
  /// Constructor that takes unsmeared pair
  StHbtSmearPair(const StHbtPair* unSmearedPair);
  /// Destructor
  virtual ~StHbtSmearPair()             { /* empty */ }
  
  // Essentially same as c'tor
  void setUnsmearedPair(const StHbtPair* unSmearedPair);

  /// Access to the smeared pair
  StHbtPair& smearedPair()              { return mSmearedPair; }

  ///========= Resolution parameters ==========
  /// pT resolution parameterized by d(pT) = Frac*pT
  void setFractionalPtRes(double val)   { mFracPtRes = val; }
  /// phi resolution parameterized d(phi)= by a+b*P^alpha (Fabrice Retiere's way)
  void setPhiRes_a(double val)          { mPhi_a = val; }
  void setPhiRes_b(double val)          { mPhi_b = val; }
  void setPhiRes_alpha(double val)      { mPhi_alpha = val; }
  /// phi resolution parameterized by d(theta) = a+b*P^alpha (Fabrice Retiere's way)
  void setThetaRes_a(double val)        { mTheta_a = val; }
  void setThetaRes_b(double val)        { mTheta_b = val; }
  void setThetaRes_alpha(double val)    { mTheta_alpha = val; }

  TLorentzVector smearedMomentum(TLorentzVector input);

 private:

  /// Pair with smeared parameters
  StHbtPair mSmearedPair;
  /// First and second particles
  StHbtParticle mParticle1;
  StHbtParticle mParticle2;

  /// Pair resolution parameters
  double mFracPtRes;
  double mPhi_a;
  double mPhi_b;
  double mPhi_alpha;
  double mTheta_a;
  double mTheta_b;
  double mTheta_alpha;

  TRandom3* mHbtRandom;

  void setup();

#ifdef __ROOT__
  ClassDef(StHbtSmearPair, 0)
#endif
};

#endif // #define StHbtSmearPair_h
