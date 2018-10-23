#ifndef StHbtParticleCollection_h
#define StHbtParticleCollection_h

/// C++ headers
#include <list>
#if !defined(ST_NO_NAMESPACES)
using std::list;
#endif

/// StHbtMaker headers
#include "StHbtParticle.h"

#ifdef ST_NO_TEMPLATE_DEF_ARGS
typedef list<StHbtParticle*, allocator<StHbtParticle*> >            StHbtParticleCollection;
typedef list<StHbtParticle*, allocator<StHbtParticle*> >::iterator  StHbtParticleIterator;
#else
typedef list<StHbtParticle*>            StHbtParticleCollection;
typedef list<StHbtParticle*>::iterator  StHbtParticleIterator;
#endif

#endif
