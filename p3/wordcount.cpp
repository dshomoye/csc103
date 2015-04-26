/*
 * CSc103 Project 3: wordcount++
 * See readme.html for details.
 * Please list all references you made use of in order to complete the
 * assignment: your classmates, websites, etc.  Aside from the lecture notes
 * and the book, please list everything.  And remember- citing a source does
 * NOT mean it is okay to COPY THAT SOURCE.  What you submit here **MUST BE
 * YOUR OWN WORK**.
 * All lines were self-written
 * Finally, please indicate approximately how many hours you spent on this:
 * 1.5 hours to complete: 
 */

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <string>
#include <sstream>
using std::string;
#include <set>
using std::set;



string lineStr;
int wordCount, charCount, lineCount, uWords, uLines;
std::set<string> uWordSet;
std::set<string> uLineSet;

unsigned long countWords(const string&, set<string>&, int&);

int main()
{
    while(getline(cin,lineStr)){
        lineCount++;
        charCount += lineStr.length()+1;
        countWords(lineStr, uWordSet, wordCount);
        uLineSet.insert(lineStr);
    }
    cout << lineCount << "\t" << wordCount << "\t" << charCount << "\t" << uLineSet.size() << "\t" << uWordSet.size();
	return 0;
}

unsigned long countWords(const string& lineS, set<string>& wl, int& words){
	string temp_word; bool last_char=false;

	for(size_t i = 0; i < lineS.size(); i++) {
		//check for whitespace and start new word
		if (isspace(lineS[i])){
			if (last_char){
				words++;
				wl.insert(temp_word);
			}
		last_char=false;
		temp_word="";	
		}
		else{
			temp_word+=lineS[i];
			last_char=true;
			//check if end of line
			if (i==lineS.size()-1){
				words++;
				wl.insert(temp_word);
			}
		}
	}
}
