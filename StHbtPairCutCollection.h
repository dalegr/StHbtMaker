#ifndef StHbtPairCutCollection_h
#define StHbtPairCutCollection_h

/// C++ headers
#include <list>
#if !defined(ST_NO_NAMESPACES)
using std::list;
#endif

/// Forward declarations
class StHbtPairCut;

#ifdef ST_NO_TEMPLATE_DEF_ARGS
typedef list<StHbtPairCut*, allocator<StHbtPairCut*> >            StHbtPairCutCollection;
typedef list<StHbtPairCut*, allocator<StHbtPairCut*> >::iterator  StHbtPairCutIterator;
#else
typedef list<StHbtPairCut*>            StHbtPairCutCollection;
typedef list<StHbtPairCut*>::iterator  StHbtPairCutIterator;
#endif

#endif
