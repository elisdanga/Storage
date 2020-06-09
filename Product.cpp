#include "Product.h"
#include <iostream>

Product::Product()
{
}

Product::Product(std::string name, std::string expiring_date, std::string entry_date, std::string producer, std::string unit, std::string quantity, std::string location, std::string comment)
{
	this->name = name;
	this->expiring_date = expiring_date;
	this->entry_date = entry_date;
	this->producer = producer;
	this->unit = unit;
	this->quantity = quantity;
	this->location = location;
	this->comment = comment;
}


std::string Product::get_name() {
	return this->name;
}

std::string Product::get_expiring_date() {
	return this->expiring_date;
}

std::string Product::get_entry_date() {
	return this->entry_date;
}

std::string Product::get_producer() {
	return this->producer;
}

std::string Product::get_unit() {
	return this->unit;
}

std::string Product::get_quantity() {
	return this->quantity;
}

std::string Product::get_location() {
	return this->location;
}

std::string Product::get_comment() {
	return this->comment;
}

void Product::set_name(std::string name)
{
	this->name = name;
}

void Product::set_expiring_date(std::string expiring_date)
{
	this->expiring_date = expiring_date;
}

void Product::set_entry_date(std::string entry_date)
{
	this->entry_date = entry_date;
}

void Product::set_producer(std::string producer)
{
	this->producer = producer;
}

void Product::set_unit(std::string unit)
{
	this->unit = unit;
}

void Product::set_quantity(std::string quantity)
{
	this->quantity = quantity;
}

void Product::set_location(std::string location)
{
	this->location = location;
}

void Product::set_comment(std::string comment)
{
	this->comment = comment;
}

void Product::add(Product p, std::string& buffer)
{
	std::string tmp = Product::toString(p);
	buffer.append(tmp);
}

Product* Product::create_from_file(std::string buffer)
{
	std::cout << buffer;
	return nullptr;
}
std::string Product::toString(Product p)
{
	std::string line;
	line.append(p.get_name());
	line.append(" ");

	line.append(p.get_expiring_date());
	line.append(" ");

	line.append(p.get_entry_date());
	line.append(" ");

	line.append(p.get_producer());
	line.append(" ");

	line.append(p.get_unit());
	line.append(" ");

	line.append(p.get_quantity());
	line.append(" ");

	line.append(p.get_location());
	line.append(" ");

	line.append("\"");
	line.append(p.get_comment());
	line.append("\"");
	
	return line;
}

Product Product::fromString(std::string input)
{

	Product p;
	std::string params[8];
	int delimiter_pos = 0;
	int i = 0;

	std::string delimiter = " ";

	/*int pos = 0;
	std::string param;
	while ((pos = input.find(delimiter)) != -1) {
		param = input.substr(0, pos);
		std::cout << param << std::endl;
		params[i] = param; i++;
		input.erase(0, pos + delimiter.length());
	}*/

	while (!input.empty()) {
		delimiter_pos = (input.find(" ") != -1) ? input.find(" ") : input.size();
		params[i] = input.substr(0, delimiter_pos);
		input.erase(0, delimiter_pos + 1);
		i++;
	}
	p.set_name(params[0]);
	p.set_expiring_date(params[1]);
	p.set_entry_date(params[2]);
	p.set_producer(params[3]);
	p.set_unit(params[4]);
	p.set_quantity(params[5]);
	p.set_location(params[6]);
	p.set_comment(params[7]);

	return p;
}

void Product::load_products(std::string buffer, Product* pr_array)
{
	int n = 0;
	int pos = 0;
	//std::cout << buffer.find("\n");
	//while ((pos = buffer.find("\n")) != std::string::npos) {
	while (!buffer.empty()) {
		pos = (buffer.find("\n") != -1) ? buffer.find("\n") : buffer.size();
		std::string line = buffer.substr(0, pos);
		pr_array[n] = fromString(line);
		buffer.erase(0, pos + 1);
		n++;
	}
}
void Product::remove(std::string& buffer, std::string product_name)
{
	Product tmp_product;
	std::string tmp_buffer = buffer;
	std::string new_buffer;
	int pos = 0;

	while (!tmp_buffer.empty())
	{
		pos = (tmp_buffer.find("\n") != -1) ? tmp_buffer.find("\n") : tmp_buffer.size();
		std::string line = tmp_buffer.substr(0, pos);
		tmp_product = fromString(line);
		if (tmp_product.get_name().compare(product_name) == 0) {

		}
		else {
			new_buffer.append(line);
			new_buffer.append("\n");
		}
		tmp_buffer.erase(0, pos + 1);

	}
	// new_buffer.pop_back();
	buffer = new_buffer;
}