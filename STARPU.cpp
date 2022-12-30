// Purpose: Compute solution for pressure and velocity in the Star region.
// Exact RS required iterative method like Newton-Raphson iteration to solve for pressure. 
// This is not practical for more complex system and thus, approximate RS should be used.

#include<cstdlib>
#include<math.h>
#include<iostream>
using namespace std;

#include "defs.hpp"
Real GUESSP(probtype& PT);
void PREFUN(Real *F,Real *FD,Real P,Real DK,Real PK,Real CK
                ,probtype& PT);


void STARPU(Real *P, Real *U, probtype& PT) {
        Real dL=PT.flowP[1],uL=PT.flowP[2],pL=PT.flowP[3],cL=PT.flowP[4];
        Real dR=PT.flowP[5],uR=PT.flowP[6],pR=PT.flowP[7],cR=PT.flowP[8];
	Real MPA=PT.MPA;

	// Guessed value PSTART is computed
	Real pStart;
	pStart=GUESSP(PT);

	Real pOld=pStart;
	Real Udiff=uR-uL;

	cout<<"---------------------------------------\n";
	cout<<"   Iteration number Change \n";
	cout<<"---------------------------------------\n";

	int NRiter=20; // Newton-Raphson iteration for pressure
	Real FL,FLD,FR,FRD,Change;
	for (int i=0;i<NRiter;i++) {
		PREFUN(&FL,&FLD,pOld,dL,pL,cL,PT);
		PREFUN(&FR,&FRD,pOld,dR,pR,cR,PT);
		*P=pOld-(FL+FR+Udiff)/(FLD+FRD);    // Eq. 4.44
		Change=2.0*abs((*P-pOld)/(*P+pOld)); // Eq. 4.45
		cout<<"NR at i="<<i<<" where change="<<Change<<"\n";
		if (Change<=eps) {break;}
		if (i>=NRiter-1 && Change>eps) {
        	        cout<<"Divergence in Newton-Raphson iteration!";
	        }
		if (*P<0.0) {
			cout<<"Negative pressure("<<P<<")! Will be corrected to zero. \n";
			*P=eps;
		}
		pOld=*P;
	}

	// Compute velocity in Star Region
	*U=0.5*(uL+uR+FR-FL); // Eq. 4.9
	cout<<"--------------------------------------\n";		 
	cout<<" Pressure & Velocity \n";
	cout<<"--------------------------------------\n";
	cout<<"P="<<*P/MPA<<" U="<<*U<<"\n";
	cout<<"--------------------------------------\n";	

}
