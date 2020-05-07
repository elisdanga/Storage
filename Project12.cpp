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
		if (command.compare("open") == 0) {
			if (args[0].size()) {
				main_filename = args[0];
				bool is_open = fs.read(main_filename, buffer);
				if (is_open) {
					cout << "Successfuly opened file: " << main_filename << endl;
				}
				else {
					cout << "Can't open file";
					main_filename = "";
					buffer = "";
				}
			}
			else {
				cout<<"Please use format: \"open file.txt\" ";
			}
		}

		if (command.compare("close") == 0) {
			main_filename = "";
			buffer = "";
		}

		if (command.compare("save") == 0) {
			if (main_filename.size()) {
				fs.write(main_filename, buffer);
				cout << "File saved!\n";
			}
			else {
				cout << "Open file first!\n";
			}
		}

		if (command.compare("saveas") == 0) {
			if (main_filename.size()) {
				fs.write(args[0], buffer);
				cout << "File saved as " << args[0] << endl;
				//todo: дали има аргумент
			}
			else {
				cout << "Open file first!\n";
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