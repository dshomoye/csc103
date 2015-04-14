#include "triangles.h"
#include <iostream>
#include <vector>
using std::endl;
using std::cout;

int main(void) {
	// TODO: write some code to test out your program.
	// This won't be graded- it is just for your benefit
	// and to aid your testing / debugging.
        
    triangle t1(3,4,5);
    triangle t2(4,5,3);
    bool cong = congruent(t1,t2);
    bool simi = similar(t1,t2);
    std::cout << "the area of t is " << t1.area() << "\n";
    std::cout << "similar is " << simi << "\n congruent is " << cong << endl;    
    
    std::cout << "test for tri finding "<< endl ;
    std::vector<triangle> fTri = findRightTriangles(1, 100);
    cout << "tri made " << endl;
    for (std::vector<triangle>::iterator it = fTri.begin() ; it != fTri.end(); ++it){
        triangle nT = *it;
        std::cout << "[ " << nT.s1 << nT.s2 << nT.s3 << " ]" << endl;
    }
    
    
	return 0;
}