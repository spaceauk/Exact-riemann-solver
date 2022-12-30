// Purpose: To sample the solution throughout the wave pattern. 
// Pressure PM and velocity UM in the Star Region are known. Sampling is performed in terms of the 'speed' S=X/T. Sampled values are D, U, P.
// Input variables: PM, UM, S
// Output variables: D, U, P

#include<cstdlib>
#include<math.h>
#include<iostream>
using namespace std;
#include "defs.hpp"

void SAMPLE(Real PM,Real UM, Real S, 
		Real *D,Real *U,Real *P,probtype& PT) {
        Real dL=PT.flowP[1],uL=PT.flowP[2],pL=PT.flowP[3],cL=PT.flowP[4];
        Real dR=PT.flowP[5],uR=PT.flowP[6],pR=PT.flowP[7],cR=PT.flowP[8];
	
	if (S<=UM) { // Sampling point lies to the left of contact discontinuity
		// (a) Left rarefaction
		if (PM<=pL) {
			Real SHL=uL-cL; // Eq. 4.55
			// (ai) Sampled point is left data state
			if (S<=SHL) {
				*D=dL;
				*U=uL;
				*P=pL;
			} else {
				Real CML=cL*pow((PM/pL),PT.G[1]);
				Real STL=UM-CML; // Eq. 4.55
				// (aii) Sampled point is Star left state
				if (S>STL) {
					*D=dL*pow(PM/pL,(1.0/PT.G[0])); // Eq. 4.53
					*U=UM;
					*P=PM;
				// (aiii) Sampled point is inside left fan
				} else {
					*U=PT.G[5]*(cL+PT.G[7]*uL+S); // Eq. 4.56
					Real C=PT.G[5]*(cL+PT.G[7]*(uL-S));
					*D=dL*pow((C/cL),PT.G[4]);
					*P=pL*pow((C/cL),PT.G[3]);
				}
			}
		// (b) Left shock
		} else {			
			Real PML=PM/pL;
			Real SL=uL-cL*sqrt(PT.G[2]*PML+PT.G[1]);
			// (bi) Sampled point is left data state
			if (S<=SL) {
				*D=dL;
				*U=uL;
				*P=pL;
			// (bii) Sampled point is Star Left state
			} else {
				*D=dL*(PML+PT.G[6])/(PML*PT.G[6]+1.0);
				*U=UM;
				*P=PM;
			}
		}
	//-----------------------------------------------------------------------------------
	} else { // Sampling point lies to the right of the contact discontinuity
		// (a) Right shock 
		if (PM>pR) {
			Real PMR=PM/pR;
			Real SR=uR+cR*sqrt(PT.G[2]*PMR+PT.G[1]); // Eq. 4.59
			// (ai) Sampled point is right data state
			if (S>=SR) {
				*D=dR;
				*U=uR;
				*P=pR;
			// (aii) Sampled point is Star right state
			} else {
				*D=dR*(PMR+PT.G[6])/(PMR*PT.G[6]+1.0); // Eq. 4.57
				*U=UM;
				*P=PM;
			}
		// (b) Right rarefaction
                } else {
			Real SHR=uR+cR; // Eq. 4.62
			// (bi) Sampled point is right data state
			if (S>=SHR) {
				*D=dR;
				*U=uR;
				*P=pR;
			} else {
				Real CMR=cR*pow((PM/pR),PT.G[1]);
				Real STR=UM+CMR;
				// (bii) Sampled point is Star right state
				if (S<=STR) {
					*D=dR*pow((PM/pR),1.0/PT.G[0]); // Eq. 4.60
					*U=UM;
					*P=PM;
				// (biii) Sampled point is inside left fan
				} else {
					*U=PT.G[5]*(-cR+PT.G[7]*uR+S); // Eq. 4.63
					Real C=PT.G[5]*(cR-PT.G[7]*(uR-S));
					*D=dR*pow((C/cR),PT.G[4]);
					*P=pR*pow((C/cR),PT.G[3]);
				}
			}
		}
	}
}
