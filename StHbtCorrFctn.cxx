/**
 * Description: The pure-virtual base class for correlation functions
 *
 * All correlation function classes must inherit from this one.
 * This class has a optional pointers to the "parent" analysis and
 * a pair cut
 */

#include "StHbtCorrFctn.h"

//_________________
StHbtCorrFctn::StHbtCorrFctn() :
  mBaseAnalysis(nullptr),
  mPairCut(nullptr) {
  /* no-op */
}

//_________________
StHbtCorrFctn::StHbtCorrFctn(const StHbtCorrFctn& c) :
  mBaseAnalysis( c.mBaseAnalysis ),
  mPairCut( c.mPairCut ) {
  /* no-op */
}

//_________________
StHbtCorrFctn& StHbtCorrFctn::operator=(const StHbtCorrFctn& c) {
  if (this != &c) {
    mBaseAnalysis = c.mBaseAnalysis;
    mPairCut = c.mPairCut;
  }
  return *this;
}

//________________
void StHbtCorrFctn::addRealPair(const StHbtPair* /* pair */) {
  std::cout << " StHbtCorrFctn::addRealPair - Not implemented" << std::endl;
}

//_________________
void StHbtCorrFctn::addMixedPair(const StHbtPair* /* pair */) {
  std::cout << "StHbtCorrFctn::addMixedPair - Not implemented" << std::endl;
}

//_________________
void StHbtCorrFctn::addRealTriplet(const StHbtTriplet* /* triplet */) {
  std::cout << "StHbtCorrFctn::addRealTriplet - Not implemented" << std::endl;
}

//_________________
void StHbtCorrFctn::addMixedTriplet(const StHbtTriplet* /* triplet */) {
  std::cout << "StHbtCorrFctn::addMixedTriplet - Not implemented" << std::endl;
}

//_________________
void StHbtCorrFctn::addFirstParticle(StHbtParticle* /* part */, bool /* isMixing*/) {
  std::cout << "StHbtCorrFctn::addFirstParticle -- Not implemented" << std::endl;
}

//_________________
void StHbtCorrFctn::addSecondParticle(StHbtParticle* /* part */) {
  std::cout << "StHbtCorrFctn::addSecondParticle -- Not implemented" << std::endl;
}
