#ifndef StHbtEventWriterCollection_h
#define StHbtEventWriterCollection_h

#include "StHbtEventWriter.h"

/// C++ headers
#include <list>
#if !defined(ST_NO_NAMESPACES)
using std::list;
#endif

#ifdef ST_NO_TEMPLATE_DEF_ARGS
typedef list<StHbtEventWriter*, allocator<StHbtEventWriter*> >            StHbtEventWriterCollection;
typedef list<StHbtEventWriter*, allocator<StHbtEventWriter*> >::iterator  StHbtEventWriterIterator;
#else
typedef list<StHbtEventWriter*>            StHbtEventWriterCollection;
typedef list<StHbtEventWriter*>::iterator  StHbtEventWriterIterator;
#endif

#endif // #define StHbtEventWriterCollection_h
