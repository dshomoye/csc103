/*
 * CSc103 Project 5: Syntax highlighting, part two.
 * See readme.html for details.
 * Please list all references you made use of in order to complete the
 * assignment: your classmates, websites, etc.  Aside from the lecture notes
 * and the book, please list everything.  And remember- citing a source does
 * NOT mean it is okay to COPY THAT SOURCE.  What you submit here **MUST BE
 * YOUR OWN WORK**.
 * References:
 *
 *
 * Finally, please indicate approximately how many hours you spent on this:
 * #hours: 
 */

#include "fsm.h"
using namespace cppfsm;
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <set>
using std::set;
#include <map>
using std::map;
#include <initializer_list> // for setting up maps without constructors.

// enumeration for our highlighting tags:
enum {
	hlstatement,  // used for "if,else,for,while" etc...
	hlcomment,    // for comments
	hlstrlit,     // for string literals
	hlpreproc,    // for preprocessor directives (e.g., #include)
	hltype,       // for datatypes and similar (e.g. int, char, double)
	hlnumeric,    // for numeric literals (e.g. 1234)
	hlescseq,     // for escape sequences
	hlerror,      // for parse errors, like a bad numeric or invalid escape
	hlident       // for other identifiers.  Probably won't use this.
};

// usually global variables are a bad thing, but for simplicity,
// we'll make an exception here.
// initialize our map with the keywords from our list:
map<string, short> hlmap = {
#include "res/keywords.txt"
};
// note: the above is not a very standard use of #include...

// map of highlighting spans:
map<int, string> hlspans = {
	{hlstatement, "<span class='statement'>"},
	{hlcomment, "<span class='comment'>"},
	{hlstrlit, "<span class='strlit'>"},
	{hlpreproc, "<span class='preproc'>"},
	{hltype, "<span class='type'>"},
	{hlnumeric, "<span class='numeric'>"},
	{hlescseq, "<span class='escseq'>"},
	{hlerror, "<span class='error'>"}
};
// note: initializing maps as above requires the -std=c++0x compiler flag,
// as well as #include<initializer_list>.  Very convenient though.
// to save some typing, store a variable for the end of these tags:
string spanend = "</span>";

string translateHTMLReserved(char c) {
	switch (c) {
		case '"':
			return "&quot;";
		case '\'':
			return "&apos;";
		case '&':
			return "&amp;";
		case '<':
			return "&lt;";
		case '>':
			return "&gt;";
		case '\t': // make tabs 4 spaces instead.
			return "&nbsp;&nbsp;&nbsp;&nbsp;";
		default:
			char s[2] = {c,0};
			return s;
	}
}



string printLine(string);

string idConvert(string str){
	map<string, short>::iterator it;  // for searches in our map.
	it = hlmap.find(str);
	if (it != hlmap.end()) {
		return hlspans[hlmap[str]] + str + spanend;
		}
	else return str;
	}


int main() {
	// TODO: write the main program.
	// It may be helpful to break this down and write
	// a function that processes a single line, which
	// you repeatedly call from main().
	string line;
	while(getline(cin,line)){
		cout << printLine(line+"\n") << endl;	
	}
	
	return 0;
}

string printLine(string line){
	string htmlTrans =""; 
	int currentState = start; 
	string strTrans ="";
	for (unsigned long i = 0; i < line.length(); i++) {
		 int oldState = updateState(currentState,line[i]);
		 if(oldState != currentState){
			 switch (oldState) {
				case scanid:
					if (currentState==start)
					{
						htmlTrans += idConvert(strTrans) + translateHTMLReserved(line[i]);
						strTrans = "";
					}
					else{
						htmlTrans += idConvert(strTrans);
						strTrans = translateHTMLReserved(line[i]);
					}
					break;
				case scannum:
					htmlTrans+=hlspans[hlnumeric]+strTrans+spanend;
					strTrans = translateHTMLReserved(line[i]);
					break;
				case comment:
					htmlTrans+=hlspans[hlcomment]+strTrans+spanend;
					strTrans = translateHTMLReserved(line[i]);
					break;
				case strlit:
					if (currentState==start)
					{
						htmlTrans+=hlspans[hlstrlit]+strTrans+spanend+ translateHTMLReserved(line[i]);
						strTrans = "";
					}
					else{
						htmlTrans+=hlspans[hlstrlit]+strTrans+spanend;
						strTrans = translateHTMLReserved(line[i]);
					}
					break;
				case readesc:
					if (currentState==strlit)
					{
						htmlTrans+=hlspans[hlescseq]+strTrans +translateHTMLReserved(line[i])+spanend;
						strTrans="";
					}
					else{
					htmlTrans+=hlspans[hlerror]+strTrans+spanend;
					strTrans = translateHTMLReserved(line[i]);
					}
					break;
				case readfs:
					if(currentState!=comment){
						htmlTrans+=strTrans;
						strTrans = translateHTMLReserved(line[i]);
						}
						else htmlTrans+=hlspans[hlcomment]+translateHTMLReserved(line[i-1])+spanend;
					break;
				case error:
					htmlTrans+=hlspans[hlerror]+strTrans+spanend;
					strTrans = translateHTMLReserved(line[i]);
					break;
				case start:
					htmlTrans+=strTrans;
					strTrans = translateHTMLReserved(line[i]);
					break;
				}
			}

		else{
			if (i==line.length()-1)
			{
				htmlTrans+=strTrans;
				strTrans += translateHTMLReserved(line[i]);
			}
			else strTrans += translateHTMLReserved(line[i]);
		}

		 }
	return htmlTrans;
	}

