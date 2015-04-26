/*
 * CSc103 Project 4: Triangles
 * See readme.html for details.
 * Please list all references you made use of in order to complete the
 * assignment: your classmates, websites, etc.  Aside from the lecture notes
 * and the book, please list everything.  And remember- citing a source does
 * NOT mean it is okay to COPY THAT SOURCE.  What you submit here **MUST BE
 * YOUR OWN WORK**.
 * References:
 *** Check for triangle ratios: http://stackoverflow.com/questions/19340607/congruence-similarity-and-right-triangles
 *
 *
 * Finally, please indicate approximately how many hours you spent on this:
 * 3hours: 
 */

#include "triangles.h" // import the prototypes for our triangle class.
#include <iostream>
using std::cout;
#include <vector>
using std::vector;
#include <algorithm>
using std::sort;

// note the "triangle::" part.  We need to specify the function's
// FULL name to avoid confusion.  Else, the compiler will think we
// are just defining a new function called "perimeter"
unsigned long triangle::perimeter() {
	return s1+s2+s3;
}

unsigned long triangle::area() {
	// Note: why is it okay to return an integer here?  Recall that
	// all of our triangles have integer sides, and are right triangles...
    unsigned long area;
    unsigned long sides[3] = {s1,s2,s3};
    sort(sides, sides+3);
    area = (sides[0]*sides[1])/2;
	return area;
}

void triangle::print() {
	cout << "[" << s1 << "," << s2 << "," << s3 << "]";
}

bool congruent(triangle t1, triangle t2) {
    unsigned long t1sides[3] = {t1.s1,t1.s2,t1.s3};
    sort(t1sides, t1sides+3);
    unsigned long t2sides[3] = {t2.s1,t2.s2,t2.s3};
    sort(t2sides, t2sides+3);
    //check if ratio of sides are similar
    if (t1sides[0] == t2sides[0] && t1sides[1] == t2sides[1] && t1sides[2] == t2sides[2] ){
        return true;}
    else{	return false;}
}

bool similar(triangle t1, triangle t2) {
    unsigned long t1sides[3] = {t1.s1,t1.s2,t1.s3};
    sort(t1sides, t1sides+3);
    unsigned long t2sides[3] = {t2.s1,t2.s2,t2.s3};
    sort(t2sides, t2sides+3);
    //check if sides are same
    if((t1sides[0]*t2sides[1])==(t1sides[1]*t2sides[0])&&(t1sides[2]*t2sides[1])==(t1sides[1]*t2sides[2])){
        return true;
    }else{ 
	return false;}
}

vector<triangle> findRightTriangles(unsigned long l, unsigned long h) {
	vector<triangle> retval; // storage for return value.
    for (int hy = 5; hy < h; hy++){
        for(int opp = 4; opp < hy; opp ++){
            for(int adj =3; adj < opp; adj ++){
            if((hy*hy==((opp*opp)+(adj*adj)))){
                unsigned long peri = hy+opp+adj;
                if(peri <= h && peri >= l){
                    triangle tri(adj,opp,hy);
                    retval.push_back(tri);
                }            
            } 
          }    
       } 
    }
  
	return retval;
}