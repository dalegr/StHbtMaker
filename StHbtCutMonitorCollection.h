#ifndef StHbtCutMonitorCollection_hh
#define StHbtCutMonitorCollection_hh

/// C++ headers
#include <vector>
#if !defined(ST_NO_NAMESPACES)
using std::vector;
#endif

/// Forward declaration
class StHbtCutMonitor;

#ifdef ST_NO_TEMPLATE_DEF_ARGS
typedef vector<StHbtCutMonitor*, allocator<StHbtCutMonitor*> >            StHbtCutMonitorCollection;
typedef vector<StHbtCutMonitor*, allocator<StHbtCutMonitor*> >::iterator  StHbtCutMonitorIterator;
#else
typedef vector<StHbtCutMonitor*>            StHbtCutMonitorCollection;
typedef vector<StHbtCutMonitor*>::iterator  StHbtCutMonitorIterator;
#endif

#endif
