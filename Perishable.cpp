#include <iostream>
#include <fstream>
#include "Perishable.h"
#include "iGood.h"
#include "Date.h"
using namespace std;


namespace aid {
	Perishable::Perishable() : Good('P') {
	}

	fstream& Perishable::store(fstream& file, bool newLine) const {
		Good::store(file, false);
		file << ',';
		file << this->m_expireDate;
		if (newLine == true) {
			file << endl;
		}
		return file;
	}

	fstream& Perishable::load(std::fstream& file) {
		Good::load(file);
		file.ignore(); 
		this->m_expireDate.read(file);
		file.get();
		return file;
	}

	ostream& Perishable::write(ostream& os, bool linear) const {
		Good::write(os, linear);
		if (!this->isEmpty() && this->isClear()) {
			if (linear == true) {
				os << this->m_expireDate;
			}
			else {
				os << endl;
				os << " Expiry date: " << this->m_expireDate;
			}
		}
		return os;
	}

	istream& Perishable::read(istream& is) {
		Good::read(is);
		if (is.good()) {
			cout << " Expiry date (YYYY/MM/DD): ";
			Date tmp;
			tmp.read(is);
			if (!tmp.bad()) {
				this->m_expireDate = tmp;
				tmp.errCode(NO_ERROR);
				this->message(nullptr);
				
			}
			else if (tmp.errCode() == 5) {
				this->message("Invalid Expiry in Date Entry");
				is.setstate(ios::failbit);
			}
			else if (tmp.errCode() == 4) {
				this->message("Invalid Year in Date Entry");
				is.setstate(ios::failbit);
			}
		}
		return is;
	}

	const Date& Perishable::expiry() const {
		return this->m_expireDate;
	}

	iGood* CreateProduct(char tag) {
		iGood *ig = nullptr;
		if (tag == 'N' || tag == 'n') {
			ig = new Good();
		}
		if (tag == 'P' || tag == 'p') {
			ig = new Perishable();
		}
		return ig;
	}

}

