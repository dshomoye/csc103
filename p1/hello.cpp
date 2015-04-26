/*
 * CSc103 Project 1: (hello_world++)
 * See readme.html for details.
 * Please list all references you made use of in order to complete the
 * assignment: your classmates, websites, etc.  Aside from the lecture notes
 * and the book, please list everything.  And remember- citing a source does
 * NOT mean it is okay to COPY THAT SOURCE.  What you submit here **MUST BE
 * YOUR OWN WORK**.
 * References:
 *
 */
#include <iostream>
 using std::cin; using std::cout;
 #include <string>
 using std::string;

 int main()
 {
 	string aName, relName;
 	/* code */
 	cout << "What is your name?\n";
 	std::getline(cin,aName);

 	cout << "\nAnd what relative are you avenging?\n";
 	cin >> relName;

 	cout << "\nMy name is " << aName << ". You killed my " << relName << ". Prepare to die! \n";

 	return 0;
 }

