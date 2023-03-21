// Purpose: To evaluate pressure functions FL & FR in exact RS

#include<math.h>
#include<iostream>
using namespace std;
#include "defs.hpp"

void PREFUN(Real *F,Real *FD,Real *FDD,Real P,Real DK,Real PK,Real CK
		,probtype& PT) {
	if (P<=PK) {
		Real PRAT=P/PK;
		*F=PT.G[4]*CK*(pow(PRAT,PT.G[1])-1.0); // Eq. 4.6 or 4.7
		*FD=(1.0/(DK*CK))*pow(PRAT,(-PT.G[2])); // 1st derivative
		*FDD=-(((PT.G[0]+1)*CK)/(2*pow(PT.G[0],2)*pow(PK,2)))*pow(P/PK,-(3*PT.G[0]+1)/(2*PT.G[0]));
	} else {
		Real AK=PT.G[5]/DK;          // Eq. 4.8
		Real BK=PT.G[6]*PK;          // Eq. 4.6
		Real QRT=sqrt(AK/(BK+P));
		*F=(P-PK)*QRT;              // Eqs. 4.6 or 4.7
		*FD=(1.0-0.5*(P-PK)/(BK+P))*QRT; // 1st derivative
		*FDD=-0.25*QRT*((4*BK+3*P+PK)/(pow(BK+P,2)));
	}
}
