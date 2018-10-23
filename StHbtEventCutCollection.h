#ifndef StHbtEventCutCollection_h
#define StHbtEventCutCollection_h

/// C++ headers
#include <list>
#if !defined(ST_NO_NAMESPACES)
using std::list;
#endif

/// Forward declaration
class StHbtEventCut;

#ifdef ST_NO_TEMPLATE_DEF_ARGS
typedef list<StHbtEventCut*, allocator<StHbtEventCut*> >            StHbtEventCutCollection;
typedef list<StHbtEventCut*, allocator<StHbtEventCut*> >::iterator  StHbtEventCutIterator;
#else
typedef list<StHbtEventCut*>            StHbtEventCutCollection;
typedef list<StHbtEventCut*>::iterator  StHbtEventCutIterator;
#endif

#endif // #define StHbtEventCutCollection_h
