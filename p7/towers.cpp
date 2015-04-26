/*
 * CSc103 Project 7: Towers of Hanoi
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
 * 0.5 hour: 
 */

// TODO: write the program.
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <getopt.h> // to parse long arguments.
#include <cstdlib> // for atoi function


void sortDisks(int start_peg, int end_peg, int disk_num, bool verbose_b){
	if (disk_num == 1)
	{
		if (!verbose_b)
		{
			cout << start_peg << "\t" << end_peg << "\n";
		}
		else cout << "Move a disk from peg " << start_peg << " to peg " << end_peg << "\n";

		return;
	}
	// more than one disk, sort for one less disk ending at different peg
	int nEnd_peg = (6 - (start_peg + end_peg));
	sortDisks(start_peg, nEnd_peg, disk_num-1, verbose_b);
	sortDisks(start_peg, end_peg, 1, verbose_b);
	sortDisks(nEnd_peg, end_peg, disk_num-1, verbose_b);
}



/* Here's a skeleton main function for processing the arguments. */
int main(int argc, char *argv[]) {
	// define long options
	int start_peg; int end_peg; int disk_num;
	bool verbose_b = false;
	bool inter_b = false; 

	static struct option long_opts[] = {
		{"start",        required_argument, 0, 's'},
		{"end",          required_argument, 0, 'e'},
		{"num-disks",    required_argument, 0, 'n'},
		{"interactive",  no_argument,       0, 'i'},
		{"verbose",      no_argument,       0, 'v'},
		{0,0,0,0} // this denotes the end of our options.
	};
	// now process the options:
	char c; // to hold the option
	int opt_index = 0;
	while ((c = getopt_long(argc, argv, "s:e:n:iv", long_opts, &opt_index)) != -1) {
		switch (c) {
			case 's': // TODO: process option 
				start_peg = atoi(optarg);
				break;
			case 'e': // TODO: process option e
				end_peg = atoi(optarg);
				break;
			case 'n': // TODO: process option n
				disk_num = atoi(optarg);
				break;
			case 'i': // TODO: process option i
				inter_b = true;
				break;
			case 'v': // TODO: process option v
				verbose_b = true;
				break;
			case '?': // this will catch unknown options.
				// here is where you would yell at the user.
				// although, getopt will already print an error message.
				return 1;
		}
	}

	/* TODO: now that you have the options and arguments,
	 * solve the puzzle. */
	if (inter_b)
	{
		cout << "how many disks? "; cin >> disk_num ;
		cout << "from which peg? "; cin >> start_peg;
		cout << "to which peg? "; cin >> end_peg; 
	}

	sortDisks(start_peg,end_peg, disk_num, verbose_b);

	return 0;
}
