#include <iostream>
#include "FileSystem.h"
using namespace std;

int main() {
	
	FileSystem fs;
	string buffer;
	string main_filename;

	while (true) {
		cout << '>';
		string input;
		string command;
		string args[4];
		int i = 0;
		getline(cin, input);

		int delimiter_pos = input.find(' ');
		command = input.substr(0, delimiter_pos);

		input.erase(0, delimiter_pos + 1);

		if (delimiter_pos != -1) {
			while (!input.empty()) {
				delimiter_pos = (input.find(" ") != -1) ? input.find(" ") : input.size();
				args[i] = input.substr(0, delimiter_pos);
				input.erase(0, delimiter_pos + 1);
				i++;
			}
		}

		if (command.compare("exit") == 0) {
			break;
		}

		if (command.compare("help") == 0) {
			cout << "The following commands are supported: \n\n";

			cout << "open <file>\t\topens <file> \n";
			cout << "close\t\t\tcloses currently opened file\n";
			cout << "save\t\t\tsaves the currently open file\n";
			cout << "saveas <file>\t\tsaves the currently open file in <file>\n";
			cout << "help\t\t\tprints this information\n";
			cout << "exit\t\t\texit program\n";
		}
	}
	
	return 0;
}