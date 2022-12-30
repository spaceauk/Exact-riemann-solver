// Purpose: To evaluate pressure functions FL & FR in exact RS

#include<math.h>
#include<iostream>
using namespace std;
#include "defs.hpp"

void PREFUN(Real *F,Real *FD,Real P,Real DK,Real PK,Real CK
		,probtype& PT) {
	if (P<=PK) {
		Real PRAT=P/PK;
		*F=PT.G[4]*CK*(pow(PRAT,PT.G[1])-1.0); // Eq. 4.6 or 4.7
		*FD=(1.0/(DK*CK))*pow(PRAT,(-PT.G[2]));
	} else {
		Real AK=PT.G[5]/DK;          // Eq. 4.8
		Real BK=PT.G[6]*PK;          // Eq. 4.6
		Real QRT=sqrt(AK/(BK+P));
		*F=(P-PK)*QRT;              // Eqs. 4.6 or 4.7
		*FD=(1.0-0.5*(P-PK)/(BK+P))*QRT;
	}
}
