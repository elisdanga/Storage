#include <iostream>
#include "FileSystem.h"
#include "Product.h"
#include <ctime>

int main() {
	
	FileSystem fs;
	std::string buffer;
	std::string main_filename;
	Product* products = new Product();

	while (true) {
		std::cout << '>';
		std::string input;
		std::string command;
		std::string args[4];
		int i = 0;
		std::getline(std::cin, input);

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
					int number_of_product_in_buffer = std::count(buffer.begin(), buffer.end(), '\n');
					products = new Product[number_of_product_in_buffer];
					Product::load_products(buffer, products);

					std::cout << "Successfuly opened file: " << main_filename << std::endl;
				}
				else {
					std::cout << "Can't open file";
					main_filename = "";
					buffer = "";
				}
			}
			else {
				std::cout<<"Please use format: \"open file.txt\" ";
			}
		}

		if (command.compare("close") == 0) {
			main_filename = "";
			buffer = "";
			std::cout << "Successfuly closed file!" << std::endl;
		}

		if (command.compare("save") == 0) {
			if (main_filename.size()) { //проверява дали има отворен файл
				fs.write(main_filename, buffer);
				std::cout << "File saved!\n";
			}
			else {
				std::cout << "Open file first!\n";
			}
		}

		if (command.compare("saveas") == 0) {
			if (main_filename.size()) {
				if (args[0].size()) {
					fs.write(args[0], buffer);
					std::cout << "File saved as " << args[0] << std::endl;
				}
				else {
					std::cout << "Please use format: \"saveas file.txt\" ";
				}
 			}
			else {
				std::cout << "Open file first!\n";
			}
		}

		if (command.compare("exit") == 0) {
			std::cout << "Exiting the program...\n";
			break;
		}

		if (command.compare("help") == 0) {
			std::cout << "The following commands are supported: \n\n";

			std::cout << "open <file>\t\topens <file> \n";
			std::cout << "close\t\t\tcloses currently opened file\n";
			std::cout << "save\t\t\tsaves the currently open file\n";
			std::cout << "saveas <file>\t\tsaves the currently open file in <file>\n";
			std::cout << "help\t\t\tprints this information\n";
			std::cout << "exit\t\t\texit program\n";
		}
		
		if (command.compare("add") == 0) {
			if (main_filename.size()) {
				
				std::string name;
				std::string expiring_date; // 2020-12-01
				std::string entry_date;
				std::string producer;
				std::string unit; // kg, l, count
				std::string quantity; //  12.5
				std::string location;
				std::string comment;

				std::cout << "Enter name\n";
				std::cin >> name;
				std::cout << "Enter expiring date (yyyy-mm-dd)\n";
				std::cin >> expiring_date;
				std::cout << "Enter entry_date (yyyy-mm-dd)\n";
				std::cin >> entry_date;
				std::cout << "Enter producer\n";
				std::cin >> producer;
				std::cout << "Enter unit (kg, l, count)\n";
				std::cin >> unit;
				std::cout << "Enter quantity\n";
				std::cin >> quantity;
				std::cout << "Enter location(x/x/x)\n";
				std::cin >> location;
				std::cout << "Enter comment\n";
				std::cin >> comment;
				std::cin.ignore();

				Product p(name, expiring_date, entry_date, producer, unit, quantity, location, comment);
				int number_of_product_in_buffer = std::count(buffer.begin(), buffer.end(), '\n');

				for (int i = 0; i < number_of_product_in_buffer; i++) {   /////////////////////////////////////////////skalda!!
					if ((products[i].get_name() == name) && (products[i].get_expiring_date() == expiring_date)) {
							location = products[i].get_location();
					
					}
				}

				p.add(p, buffer);
												
				//delete products; !!!!!!!!!!!!! TODO:

				products = new Product[number_of_product_in_buffer + 1];
				Product::load_products(buffer, products);
				std::cout << number_of_product_in_buffer << std::endl;
				std::cout << "Successfuly added!" << std::endl;
			}
			else {
				std::cout << "Open file first!" << std::endl;
			}
			
		}

		if (command.compare("print") == 0) {
			if (main_filename.size()) {
				//number of new lines is equal to number of products
				//if file has no new empty line at the end
				int number_of_product_in_buffer = std::count(buffer.begin(), buffer.end(), '\n');

				for (int i = 0; i < number_of_product_in_buffer; i++) {

					std::cout << Product::toString(products[i])<< std::endl;

				}
			}
			else {
				std::cout << "Open file first!" << std::endl;
			}
		}
		
		if (command.compare("remove") == 0) {
			if (main_filename.size()) {
				if (args[0].size()) {
					Product::remove(buffer, args[0]);
					Product::load_products(buffer, products);
					std::cout << "Successfuly remove!\n";
				}
				else {
					std::cout << "Please use format \"remove product_name\"" << std::endl;
				}
			}
			else {
				std::cout << "Open file first!" << std::endl;
			}
		}

		if (command.compare("log <from> <to>") == 0) { /////////////////////////////////////////////////

		}
		
		if (command.compare("clean") == 0) {
			if (main_filename.size()) {
				std::string current_date;
				std::cout << "Enter current date: ";
				std::cin >> current_date;

				int number_of_product = std::count(buffer.begin(), buffer.end(), '\n');
				std::cout << "Expired products:" << std::endl;
				for (int i = 0; i < number_of_product; i++) {
					if (current_date >= products[i].get_expiring_date()) {
						Product::remove(buffer, products[i].get_name());
						std::cout << Product::toString(products[i]) << std::endl;
					}
				}
				Product::load_products(buffer, products);
				std::cout << "Successfuly remove!\n";
			}
			else {
				std::cout << "Open file first!" << std::endl;
			}
		}
	}
	
	return 0;
}