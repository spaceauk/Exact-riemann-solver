// Purpose: To provide a guess value for pressure PM in the Star Region.
// The choice is made according to the adaptive Riemann solver using the PVRS, TRRS and TSRS approximate Riemann solvers. 
// See Sect. 9.5 of Chapt. 9 of Ref. 1

#include<cstdlib> // For min & max
#include<math.h>
#include<iostream>
using namespace std;

#include "defs.hpp"

Real GUESSP(probtype& PT) {
	Real domLEN=PT.flowP[0];
	Real dL=PT.flowP[1],uL=PT.flowP[2],pL=PT.flowP[3],cL=PT.flowP[4];
	Real dR=PT.flowP[5],uR=PT.flowP[6],pR=PT.flowP[7],cR=PT.flowP[8];
	Real PM;

	Real QUSER=2.0;

	// Complete guess pressure from PVRS Riemann solver
	Real CUP=0.25*(dL+dR)*(cL+cR);
	Real PPV=0.5*(pL+pR)+0.5*(uL-uR)*CUP; // Eq. 4.47
	PPV=MAX(eps,PPV);					      
	Real pMIN=MIN(pL,pR);
	Real pMAX=MAX(pL,pR);
	Real qMAX=pMAX/pMIN;

	if (qMAX<=QUSER && (pMIN<=PPV && PPV<=pMAX)) {
		PM=PPV;
	} else {
		if (PPV<pMIN) {
			Real pQ=pow((pL/pR),PT.G[1]);
			Real uM=(pQ*uL/cL + uR/cR + PT.G[4]*(pQ-1.0))/
				(pQ/cL + 1.0/cR);
			Real ptL=1.0+PT.G[7]*(uL-uM)/cL;
			Real ptR=1.0+PT.G[7]*(uM-uR)/cR;
			PM=0.5*(pL*pow(ptL,PT.G[3])+pR*pow(ptR,PT.G[3])); // Eq. 4.46
		} else {
			Real GEL=sqrt((PT.G[5]/dL)/(PT.G[6]*pL+PPV));
			Real GER=sqrt((PT.G[5]/dR)/(PT.G[6]*pR+PPV));
			PM=(GEL*pL+GER*pR-(uR-uL))/(GEL+GER);
		}
	}

	return PM;
}
