/*
 * CSc103 Project 2: prime numbers.
 * See readme.html for details.
 * Please list all references you made use of in order to complete the
 * assignment: your classmates, websites, etc.  Aside from the lecture notes
 * and the book, please list everything.  And remember- citing a source does
 * NOT mean it is okay to COPY THAT SOURCE.  What you submit here **MUST BE
 * YOUR OWN WORK**.
 * References:
 *
 */
 /* The primality test algorithm is fairly common, 
 the version below was adapted from Wikipedia 
 */

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

bool isPrime(unsigned long n) {
	//check if 2 or 3
    if (n <= 3) {
        return n > 1;
        //check if even
    } else if (n % 2 == 0) {
        return false;
    } else {
    	//check for other divisors less than square root (multipliers flip beyond this ie - 1x7,2x7...7x7...7x2,7x1)
        for (unsigned short i = 3; i * i <= n; i += 2) {
            if (n % i == 0) {
                return false;
            }
        }
        return true;
    }
}

int main()
{
	unsigned long input_int;
	while(cin >> input_int){	
	if(isPrime(input_int)){
		cout << 1 << endl;
	} else { cout << 0 << endl;}}

	return 0;
} 	
