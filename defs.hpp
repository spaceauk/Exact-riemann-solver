// All math/cpu-related constants
#define eps 1.0E-6
using Real=double;//float;


// Related to fluid/flow
class probtype{
	public:
		string testcase;
		Real flowP[9];
		Real G[9];	
		Real MPA;	
};



// All functions
#define MIN(a, b) ((a)<(b) ? (a):(b))
#define MAX(a, b) ((a)>(b) ? (a):(b))
#define SQR(x) (x*x)





