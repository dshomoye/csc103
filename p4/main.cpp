#include "triangles.h"

int main(void) {
	// TODO: write some code to test out your program.
	// This won't be graded- it is just for your benefit
	// and to aid your testing / debugging.
    int main(){
        
    Triangle t1 = new Triangle;
    Triangle t2 = new Triangle;
    t1.s1=3; t1.s2=4; t1.s3=5;
    t2.s1=4; t2.s2=5; t2.s3= 3;
    bool cong = congruent(t1,t2);
    bool simi = similar(t1,t2);
    
    
    }

    
    
	return 0;
}