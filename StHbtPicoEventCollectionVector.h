/**
 * Description:
 * Collection and analysis for vertex dependent event mixing.
 */

#ifndef StHbtPicoEventCollectionVector_h
#define StHbtPicoEventCollectionVector_h

/// C++ headers
#include <vector>
#include <list>
#if !defined(ST_NO_NAMESPACES)
using std::vector;
using std::list;
#endif

/// StHbtMaker header
#include "StHbtPicoEventCollection.h"

#ifdef ST_NO_TEMPLATE_DEF_ARGS
typedef vector<StHbtPicoEventCollection*, allocator<StHbtPicoEventCollection*> >            StHbtPicoEventCollectionVector;  //!
typedef vector<StHbtPicoEventCollection*, allocator<StHbtPicoEventCollection*> >::iterator  StHbtPicoEventCollectionIterator;//!
#else
typedef vector<StHbtPicoEventCollection*>            StHbtPicoEventCollectionVector;//!
typedef vector<StHbtPicoEventCollection*>::iterator  StHbtPicoEventCollectionIterator;//!
#endif

#endif // #define StHbtPicoEventCollectionVector_h
