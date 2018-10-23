#ifndef StHbtTrackCutCollection_h
#define StHbtTrackCutCollection_h

/// C++ headers
#include <list>
#if !defined(ST_NO_NAMESPACES)
using std::list;
#endif

/// StHbtMaker headers
#include "StHbtTrackCut.h"

#ifdef ST_NO_TEMPLATE_DEF_ARGS
typedef list<StHbtTrackCut*, allocator<StHbtTrackCut*> >            StHbtTrackCutCollection;
typedef list<StHbtTrackCut*, allocator<StHbtTrackCut*> >::iterator  StHbtTrackCutIterator;
#else
typedef list<StHbtTrackCut*>            StHbtTrackCutCollection;
typedef list<StHbtTrackCut*>::iterator  StHbtTrackCutIterator;
#endif

#endif // #define StHbtTrackCutCollection_h
