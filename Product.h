#pragma once
#include <string>

class Product
{
private:
	std::string name;
	std::string expiring_date;
	std::string entry_date;
	std::string producer;
	std::string unit;
	double quantity = 0;
	std::string location;
	std::string comment;
public:
	Product();
	Product(
		std::string name,
		std::string expiring_date,
		std::string entry_date,
		std::string producer,
		std::string unit,
		double quantity,
		std::string location,
		std::string comment
	);

	std::string get_name();
	std::string get_expiring_date();
	std::string get_entry_date();
	std::string get_producer();
	std::string get_unit();
	double get_quantity();
	std::string get_location();
	std::string get_comment();

	void set_name(std::string);
	void set_expiring_date(std::string);
	void set_entry_date(std::string);
	void set_producer(std::string);
	void set_unit(std::string);
	void set_quantity(double);
	void set_location(std::string);
	void set_comment(std::string);

	void add(Product p, std::string& buffer);
	static Product* create_from_file(std::string buffer);
	static std::string toString(Product p);
	static Product fromString(std::string);
};
