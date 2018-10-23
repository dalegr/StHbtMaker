/**
* Description: The pure virtual base class for the event cut
*
* All event cuts must inherit from this one and implement the ::pass and
* ::report methods. The ::clone() function simply returns nullptr, so if users
* want their cuts to behave as expected, they should also write their own.
*/

#ifndef StHbtEventCut_h
#define StHbtEventCut_h

/// Forward declarations
class StHbtEvent;
class StHbtBaseAnalysis;

/// StHbtMaker headers
#include "StHbtCutMonitorHandler.h"
#include "StHbtString.h"

/// ROOT headers
#include "TList.h"
#include "TString.h"

//_________________
class StHbtEventCut : public StHbtCutMonitorHandler {

 public:
  /// Default constructor
  StHbtEventCut();
  /// Copy constructor
  StHbtEventCut(const StHbtEventCut& copy);
  /// Assignment operator
  StHbtEventCut& operator=(const StHbtEventCut& copy);
  /// Default destructor
  virtual ~StHbtEventCut()               { /* no-op */ }

  /// True if event has passed the cut and false if not
  virtual bool pass(const StHbtEvent* event) = 0;

  /// Return new settings list.
  ///
  /// This method creates a new list of TObjStrings describing cut parameters.
  /// The default implementation automatically calls the AppendSettings method
  /// to fill the list, so users only need to overload that method.
  virtual TList* listSettings() const;

  /// Appends cut settings to a TList
  ///
  /// This method should be overloaded by the user to add any relevent settings
  /// of the cut to the list
  ///
  /// No settings are added by this class. Simply returns the incoming TList.
  ///
  /// \param A list to append settings to.
  /// \param prefix An optional prefix to prepend to the beginning of each setting
  /// \return The same pointer as the parameter
  virtual TList* appendSettings(TList*, const TString& prefix="") const;
  
  /// User-written method to return string describing cuts
  virtual StHbtString report() = 0;
  /// Default clone
  virtual StHbtEventCut* clone()         { return nullptr; }

  /// The following allows "back-pointing" from the CorrFctn
  ///to the "parent" Analysis
  friend class StHbtBaseAnalysis;
  StHbtBaseAnalysis* hbtAnalysis()       { return mBaseAnalysis; }
  void setAnalysis(StHbtBaseAnalysis* a) { mBaseAnalysis = a; }

 protected:
  StHbtBaseAnalysis* mBaseAnalysis;

#ifdef __ROOT__
  ClassDef(StHbtEventCut, 0)
#endif
};

inline StHbtEventCut::StHbtEventCut() : StHbtCutMonitorHandler(), mBaseAnalysis(nullptr) { /* empty */ }
inline StHbtEventCut::StHbtEventCut(const StHbtEventCut& c) :
		     StHbtCutMonitorHandler(), mBaseAnalysis( c.mBaseAnalysis )	         { /* empty */ }
inline StHbtEventCut& StHbtEventCut::operator=(const StHbtEventCut& c) {
  if ( this != &c ) {
    mBaseAnalysis = c.mBaseAnalysis;
  }
  return *this;
}
inline TList* StHbtEventCut::listSettings() const { return appendSettings( new TList() ); }
inline TList* StHbtEventCut::appendSettings(TList *listOfSettings, const TString &prefix) const
{ return listOfSettings; }

#endif // #define StHbtEventCut_h
