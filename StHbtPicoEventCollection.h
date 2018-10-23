/**
 * Description:
 * A Collection of PicoEvents is what makes up the EventMixingBuffer
 * of each Analysis
 */

#ifndef StHbtPicoEventCollection_h
#define StHbtPicoEventCollection_h

/// C++ headers
#include <list>
#if !defined(ST_NO_NAMESPACES)
using std::list;
#endif

/// StHbtMaker headers
#include "StHbtPicoEvent.h"

#ifdef ST_NO_TEMPLATE_DEF_ARGS
typedef list<StHbtPicoEvent*, allocator<StHbtPicoEvent*> >            StHbtPicoEventCollection;
typedef list<StHbtPicoEvent*, allocator<StHbtPicoEvent*> >::iterator  StHbtPicoEventIterator;
#else
typedef list<StHbtPicoEvent*>            StHbtPicoEventCollection;
typedef list<StHbtPicoEvent*>::iterator  StHbtPicoEventIterator;
#endif

#endif // #define StHbtPicoEventCollection_h
