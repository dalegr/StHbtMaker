/**
 * Description: part of STAR HBT Framework: StHbtMaker package
 *    This is a Coulomb correction class which
 *  1. Reads in the dat from a file
 *  2. Performs a linear interpolation in R and creates any array of interpolations
 *  3. Interpolates in eta and returns the Coulomb correction to user
 */

#ifndef StHbtCoulomb_HH
#define StHbtCoulomb_HH

/// StHbtMaker headers
#include "StHbtPair.h"

/// ROOT headers
#include "TH1D.h"
#include "TH3D.h"

//_________________
class StHbtCoulomb {

 public:
  /// Default constructor
  StHbtCoulomb();
  /// Constructor with parameters
  StHbtCoulomb(const char *readFile, const double& radius, const double& charge);
  /// Copy constructor
  StHbtCoulomb(const StHbtCoulomb& copy);
  /// Copy constructor
  StHbtCoulomb& operator=(const StHbtCoulomb& copy);
  /// Destructor
  virtual ~StHbtCoulomb();

  /// Setters
  void setRadius(const double& radius);
  void setFile(const char *readFile);
  void setChargeProduct(const double& charge);

  /// Getters
  double radius()    { return mRadius; }
  /// These have different names so eta/Qinv don't confuse the compiler
  double coulombCorrect(const double& eta);
  double coulombCorrect(const double& eta, const double& radius);
  double coulombCorrect(const StHbtPair* pair)
  { return coulombCorrect( eta( pair ) ); }
  double coulombCorrect(const StHbtPair* pair, const double& radius)
  { return coulombCorrect( eta(pair), radius ); }
  double coulombCorrect(const double& mass,
			const double& charge,
		        const double& radius,
			const double& qInv);
  TH1D* correctionHistogram(const double& mass1,
			    const double& mass2,
			    const int& nBins, 
			    const double& low,
			    const double& high);
#ifdef __ROOT__
  TH1D* correctionHistogram(const TH1D*, const double);
  TH3D* correctionHistogram(const TH3D*, const double);
#endif
  
 private:
  /// Calculates eta
  double eta(const StHbtPair* pair);
  /// Creates look-up table
  void createLookupTable(const double& radius);
  /// File to interpolate corrections from    
  const char* mFile;
  /// Radius from previous iteration
  double mRadius;
  /// Charge product of particles
  double mZ1Z2;
  /// Interpolated Coulomb correction table
  double mEta[1000];
  /// Interpolated Coulomb correction table
  double mCoulomb[1000];
  /// Number of Eta's in lookup-table
  int mNLines;                                   

#ifdef __ROOT__
  ClassDef(StHbtCoulomb, 0)
#endif
};

#endif
