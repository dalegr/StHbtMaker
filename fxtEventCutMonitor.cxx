#include "StHbtEvent.h"
#include "StHbtTypes.h"
#include "fxtEventCutMonitor.h"
#include <cstdio>
#include <cmath>

#ifdef __ROOT__ 
ClassImp(fxtEventCutMonitor)
#endif

//_________________
fxtEventCutMonitor::fxtEventCutMonitor(){
  mVertexYvsVertexX = new TH2F("VertexYvsVertexX",
				       "VertexYvsVertexX;x (cm);y (cm)", 
				       300, -6.,6., 300, -6.,6.);
  mVertexZ = new TH1F("VertexZ", "VertexZ; z (cm)",
			      320, -80., 80.);
  mRefMult = new TH1F("RefMult", "RefMult;RefMult",
			      600, -0.5, 599.5);
  mVpdVzDiff = new TH1F("VpdVzDiff", "mVpdVzDiff",
				40, -20., 20.);
}

//_________________
fxtEventCutMonitor::fxtEventCutMonitor(const char* title1, const char* title2){
  char tit1[100];

  sprintf(tit1,"%s%s_VertexYvsVertexX",title1,title2);
  mVertexYvsVertexX = new TH2F(tit1, "VertexYvsVertexX;x (cm);y (cm)", 
				       300, -6.,6., 300, -6.,6.);

  sprintf(tit1,"%s%s_VertexZ",title1,title2);
  mVertexZ = new TH1F(tit1, "VertexZ;z (cm)", 
			      320, -80., 80.);

  sprintf(tit1,"%s%s_RefMult",title1,title2);
  mRefMult = new TH1F(tit1, "RefMult;RefMult", 600, 0., 600.);

  sprintf(tit1,"%s%s_VpdVzDiff",title1,title2);
  mVpdVzDiff = new TH1F(tit1, "VpdVzDiff", 40, -20., 20.);
}

//_________________
fxtEventCutMonitor::~fxtEventCutMonitor(){
//  delete mScaler;
  delete mVertexYvsVertexX;
  delete mVertexZ;
  delete mRefMult;
  delete mVpdVzDiff;
}

//_________________
void fxtEventCutMonitor::fill(const StHbtEvent* event){

  mVertexYvsVertexX->Fill( event->primaryVertex().x(),
			   event->primaryVertex().y() );
  mVertexZ->Fill( event->primaryVertex().z() );
  mRefMult->Fill( event->refMult() );
  mVpdVzDiff->Fill( event->vpdVzDiff() );
}

//_________________
void fxtEventCutMonitor::finish(){
  std::cout << " entries in histogram mVertexYvsVertexX : "
	    << mVertexYvsVertexX->Integral() << std::endl;
  std::cout << " entries in histogram mVertexZ : "
	    << mVertexZ->Integral() << std::endl;
  std::cout << " entries in histogram mRefMult : "
	    << mRefMult->Integral() << std::endl;
  std::cout << " entries in histogram mVpdVzDiff : "
	    << mVpdVzDiff->Integral() << std::endl;
}

//_________________
StHbtString fxtEventCutMonitor::report(){
  string Stemp;
  char Ctemp[100];
  sprintf(Ctemp," fxtEventCutMonitor");
  Stemp=Ctemp;
  StHbtString returnThis = Stemp;
  return returnThis;
}


