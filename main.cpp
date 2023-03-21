// Exact Riemann solver

#include<math.h>
#include<iostream>    // std::cout
#include<exception>   // call error exception
#include<fstream>     // input and output
#include<iomanip>     // std::setw		 
using namespace std;		    
#include "defs.hpp"

Real STARPU(Real *P,Real *U,probtype &PT);
void SAMPLE(Real PM,Real UM, Real S, 
		Real *D,Real *U,Real *P,probtype& PT);

int main() {
	int n;
	Real domLEN,diaph;
	Real timeout;
	Real gammaa,dL,uL,pL,dR,uR,pR;

	probtype PT;
	// Initial data and parameters to read in
	ifstream initfile;
	initfile.open ("input.txt");
	initfile>>PT.testcase; cout<<PT.testcase<<"\n";
	initfile>>PT.itertype;     // Iteration type
	if (PT.itertype=="1st") {
		cout<<"Newton-Raphson method"<<endl;
	} else if (PT.itertype=="2nd") {
		cout<<"Halley's method"<<endl;
	}		
	initfile>>domLEN;          // Domain length 
	initfile>>diaph;           // Initial disontinuity position
	initfile>>n;               // # of computing cells
	initfile>>gammaa;          // Ratio of specific heats
	initfile>>timeout;         // Output time
	initfile>>dL;              // Initial density on left state
	initfile>>uL;              // Initial velocity on left state
	initfile>>pL;              // Initial pressure on left state
	initfile>>dR;              // Initial density on right state
	initfile>>uR;              // Initial velocity on right state
	initfile>>pR;              // Initial pressure on right state
	initfile>>PT.MPA;          // Normalizing constant
	initfile.close();

	// Compute gamma related constants
	PT.G[0]=gammaa;
	PT.G[1]=(gammaa-1.)/(2.*gammaa);
	PT.G[2]=(gammaa+1.)/(2.*gammaa);
	PT.G[3]=2.*gammaa/(gammaa-1.);
	PT.G[4]=2./(gammaa-1.);
	PT.G[5]=2./(gammaa+1.);
	PT.G[6]=(gammaa-1.)/(gammaa+1.);
	PT.G[7]=(gammaa-1.)/2.;
	PT.G[8]=gammaa-1.;

	// Compute sound speeds
	Real cL=sqrt(gammaa*pL/dL);
	Real cR=sqrt(gammaa*pR/dR);
	PT.flowP[0]=domLEN; PT.flowP[1]=dL;PT.flowP[2]=uL;
	PT.flowP[3]=pL;PT.flowP[4]=cL;PT.flowP[5]=dR;
	PT.flowP[6]=uR;PT.flowP[7]=pR;PT.flowP[8]=cR;

	// Test pressure positivity condition:
	if (PT.G[4]*(cL+cR)<=(uR-uL)) {
		cout<<"\n ***Vacuum is generated by data*** \n";
		cout<<"***Program is stopped*** \n \n";
		throw std::exception();
	}

	// Exact solution for pressure & velocity in star region is found
	Real PM,UM;
	STARPU(&PM,&UM,PT);

	Real dx=domLEN/n, x, s;
	Real DS,US,PS;
	int lw=20; // Line-width for outputting data

	// Complete solution at time=timeout is found
	string fname;
	stringstream ss;
	ss<<setw(4)<<setfill('0')<<timeout;
	string time=ss.str();
	fname = "./data/"+PT.testcase+"_t"+time+".dat";
	ofstream Wdata;
	Wdata.open(fname);
	for (int i=0;i<n;i++) {
		x=((i+1)-0.5)*dx;
		s=(x-diaph)/timeout; // Sampling in terms of spedd s=x/t
		// Solution at point (x,t)=(x-diaph,timeout) is found
		SAMPLE(PM,UM,s,&DS,&US,&PS,PT);
		
		Wdata<<setw(lw)<<x<<setw(lw)<<DS<<setw(lw)<<
			US<<setw(lw)<<PS/PT.MPA<<setw(lw)<<PS/DS/PT.G[8]/PT.MPA<<" \n";		
	}
	Wdata.close ();

	// Plot data
	string command="python3 plotdata.py " + to_string(n);
        cout<<command<<endl;
        system(command.c_str());

}
