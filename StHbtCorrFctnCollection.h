/**
 * Description: part of STAR HBT Framework: StHbtMaker package
 *   The CorrFctnCollection contains pointers to all Correlation Functions
 *   that are associated with a particular Analysis object.
 */

#ifndef StHbtCorrFctnCollection_h
#define StHbtCorrFctnCollection_h

/// C++ headeres
#include <list>
#if !defined(ST_NO_NAMESPACES)
using std::list;
#endif

/// Forward declaration
class StHbtCorrFctn;

#ifdef ST_NO_TEMPLATE_DEF_ARGS
typedef list<StHbtCorrFctn*, allocator<StHbtCorrFctn*> >            StHbtCorrFctnCollection;
typedef list<StHbtCorrFctn*, allocator<StHbtCorrFctn*> >::iterator  StHbtCorrFctnIterator;
#else
typedef list<StHbtCorrFctn*>            StHbtCorrFctnCollection;
typedef list<StHbtCorrFctn*>::iterator  StHbtCorrFctnIterator;
#endif

#endif // #define StHbtCorrFctnCollection_h
