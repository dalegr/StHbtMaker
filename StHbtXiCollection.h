#ifndef StHbtXiCollection_h
#define StHbtXiCollection_h

/// C++ headers
#include <list>
#if !defined(ST_NO_NAMESPACES)
using std::list;
#endif

/// StHbtMaker headers
#include "StHbtXi.h"

#ifdef ST_NO_TEMPLATE_DEF_ARGS
typedef list<StHbtXi*, allocator<StHbtXi*> >            StHbtXiCollection;
typedef list<StHbtXi*, allocator<StHbtXi*> >::iterator  StHbtXiIterator;
#else
typedef list<StHbtXi*>            StHbtXiCollection;
typedef list<StHbtXi*>::iterator  StHbtXiIterator;
#endif

#endif // #define StHbtXiCollection_h

