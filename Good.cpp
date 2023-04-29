#include <iostream>
#include <fstream>
#include <cstring>
#include "Good.h"
using namespace std;
namespace aid {

	void Good::name(const char* inputname) {
		if (inputname != nullptr) {
			delete[] this->m_name; 
			this->m_name = new char[max_name_length + 1];
			strncpy(this->m_name, inputname, max_name_length + 1);
		}
		else {

			this->m_name = nullptr;
		}
	}

	const char* Good::name() const {
		return (this->isEmpty() ? nullptr : this->m_name);
	}

	const char* Good::sku() const {
		return this->m_sku;
	}

	const char* Good::unit() const {
		return this->m_unit;
	}

	bool Good::taxed() const {
		return this->m_taxed;
	}

	double Good::itemPrice() const {
		return this->m_price;
	}

	double Good::itemCost() const {
		return this->m_price*(tax_rate + 1);
	}

	void Good::message(const char* errMess) {
		this->m_error.message(errMess);
	}

	bool Good::isClear() const {
		return this->m_error.isClear();
	}
	
	Good::Good(char type) {
		this->m_type = type;
		this->m_name = nullptr; 
		this->m_sku[0] = '\0';
		this->m_unit[0] = '\0';
		this->m_qty = 0;
		this->m_taxed = false;
		this->m_price = 0;
		this->m_need = 0;
		this->m_error.message(nullptr); 
	}

	Good::Good(const char* sku, const char* name, const char* unit, int qty, bool taxed, double price, int need) {
		if (name != nullptr && name[0] != '\0' ) {
			strncpy(this->m_sku, sku, max_sku_length + 1);
			this->name(nullptr);
			this->name(name);
			strncpy(this->m_unit, unit, max_unit_length + 1);
			this->m_qty = qty;
			this->m_taxed = taxed;
			this->m_price = price;
			this->m_need = need;
		}
		else {
			this->m_name = nullptr;
			*this = Good();
		}
	}

	Good::Good(const Good& other) {
		this->m_name = nullptr;
		*this = other; 
	}

	Good& Good::operator=(const Good& other){
		if (this != &other) {
			strncpy(this->m_unit, other.m_unit, max_unit_length + 1);
			strncpy(this->m_sku, other.m_sku, max_sku_length + 1);
			this->m_qty = other.m_qty;
			this->m_taxed = other.m_taxed;
			this->m_price = other.m_price;
			this->m_need = other.m_need;
			delete[] this->m_name;
			this->m_error.clear();
			if (other.m_name != nullptr) {
				this->m_name = nullptr;
				this->name(other.m_name);
			}
			else {
				this->m_name = nullptr;
			}
			if ( !other.m_error.isClear() ) {
				this->m_error.message(other.m_error.message());
			}
			else {
				this->m_error.message(nullptr);
			}
		}
		return *this;
	}

	Good::~Good() {
		delete[] this->m_name;
	}



	istream& Good::read(istream& is) {
		char sku[max_sku_length + 1], unit[max_unit_length], name[max_name_length + 1];
		char taxed; 
		double price; 
		int qty, need;
		bool tax;

		cout << " Sku: ";
		cin.getline(sku, max_sku_length, '\n');
		cout << " Name (no spaces): ";
		cin.getline(name, max_name_length, '\n');
		cout << " Unit: ";
		cin.getline(unit, max_unit_length, '\n');
		cout << " Taxed? (y/n): ";
		cin.get(taxed); 
		if (taxed == 'y' || taxed == 'Y'  ) {
			tax = true;
		}
		else if (taxed == 'n' || taxed == 'N') {
			tax = false;
		}
		else {
			this->m_error.message("Only (Y)es or (N)o are acceptable");
			cin.setstate(ios::failbit);
		}
		if (!cin.fail()) {
			cout << " Price: ";
			cin >> price;
			cin.ignore(2000, '\n');
			if (cin.fail()) { 
				this->m_error.message("Invalid Price Entry");
			}
		}
		if (!cin.fail()) {
			cout << " Quantity on hand: ";
			cin >> qty;
			cin.ignore(2000, '\n');
			if (cin.fail()) {
				this->m_error.message("Invalid Quantity Entry");
			}
		}
		if (!cin.fail()) {
			cout << " Quantity needed: ";
			cin >> need;
			cin.ignore(2000, '\n');
			if (cin.fail()) {
				this->m_error.message("Invalid Quantity Needed Entry");
			}
			else {
				this->m_error.clear();
			}
		}
		if (this->m_error.isClear()) { 
			*this = Good(sku, name, unit, qty, tax, price, need);
		}
		return is;
	}

	ostream& Good::write(ostream& os, bool linear) const{
		if (!this->isEmpty() && this->m_error.isClear()) {
			if (linear == true) {
				os.fill(' ');
				os.width(max_sku_length);
				os.setf(ios::left);
				os << this->m_sku << "|";
				os.width(20);
				os << this->m_name << "|";
				os.unsetf(ios::left);
				os.width(7);
				os.setf(ios::fixed);
				os.precision(2);
				if (this->taxed() == true) {
					os << this->itemCost() << "|";
				}
				else {
					os << this->itemPrice() << "|";
				}
				os.unsetf(ios::fixed);
				os.width(4);
				os << this->m_qty << "|";
				os.width(10);
				os.setf(ios::left);
				os << this->m_unit << "|";
				os.unsetf(ios::left);
				os.width(4);
				os << this->m_need << "|";
			}
			if (linear != true) {
				os << " Sku: " << this->m_sku << endl;
				os << " Name (no spaces): " << this->m_name << endl;
				os.setf(ios::fixed);
				os.precision(2);
				os << " Price: " << this->itemPrice() << endl;
				os << " Price after tax: ";
				if (this->m_taxed == true) {
					os << this->itemCost();
				}
				else {
					os << " N/A";
				}
				os.unsetf(ios::fixed);
				os << endl;
				os << " Quantity on Hand: " << this->m_qty << " " << this->m_unit << endl;
				os << " Quantity needed: " << this->m_need;
			}
			if(!this->m_error.isClear()) {
				os << this->m_error.message() << endl;
			}
		}
		
		if (!this->m_error.isClear()) {
			os << this->m_error.message();
		}
		return os;
	}

	fstream& Good::store(fstream& file, bool newLine = true) const {
		file << this->m_type << ",";
		file << m_sku << "," << m_name << "," << m_unit << "," <<m_taxed << "," << m_price << "," <<
			 m_qty << "," << m_need;
		if (newLine == true) {
			file << '\n';
		}
		return file;
	}

	fstream& Good::load(fstream& file) {
		Good tmp;
		file.getline(tmp.m_sku, max_sku_length, ',');
		char name[75];
		int len = strlen(name);
		file.getline(name, max_name_length, ',');
		tmp.m_name = new char[len + 1];
		strncpy(tmp.m_name, name, len + 1);
		file.getline(tmp.m_unit, max_sku_length, ',');
		file >> tmp.m_taxed;
		file.ignore();
		file >> tmp.m_price;
		file.ignore(); 
		file >> tmp.m_qty;
		file.ignore();
		file >> tmp.m_need;
		*this = tmp;
		return file;

	}

	bool Good::isEmpty() const {
		return ( (this->m_name == nullptr) || (this->m_name[0] == '\0') );
	}

	bool Good::operator==(const char* value) const{
		int ret = strcmp(this->m_sku, value);
		return (ret == 0 ? 1 : 0);
	}

	double Good::total_cost() const {
		return (this->quantity() * this->itemCost());
	}

	void Good::quantity(int num) {
		if (num > 0) {
			this->m_qty = num;
		}
	}

	int Good::qtyNeeded() const {
		return this->m_need;
	}

	int Good::quantity() const {
		return this->m_qty;
	}

	bool Good::operator>(const char* value) const {
		int cmpres = strcmp(this->m_sku, value);
		return (cmpres > 0 ? 1 : 0);
	}

	bool Good::operator>(const iGood& rhs)const { 
		int cmpres = strcmp(this->m_name, rhs.name());
		return (cmpres > 0 ? 1 : 0);
	}

	int Good::operator+=(int num) {
		if (num > 0) {
			this->m_qty += num;
		}
		return this->m_qty;
	}

	ostream& operator<<(ostream& os, const iGood& rhs) {
		bool flag = true;
		if ( rhs.name() == nullptr ) {
			flag = false;
		}
		rhs.write(os, flag);
		return os;
	}
	istream& operator>>(istream& is, iGood& rhs) { 
		rhs.read(is);
		return is;
	}

	double operator+=(double& dvalue, const iGood& rhs) { 
		return rhs.total_cost() + dvalue;
	}

}
