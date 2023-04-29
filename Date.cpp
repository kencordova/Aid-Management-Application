#include <iostream>
#include "Date.h"
using namespace std;
namespace aid {
	int Date::mdays(int year, int mon) {
		int days[] = {31,28,31,30,31,30,31,31,30,31,30,31,-1};
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

	void Date::errCode(int err) {
		this->m_err = err;
	}

	int Date::errCode() const{
		return (this->m_err);
	}

	bool Date::bad() const{
		return (this->m_err); 
	}

	Date::Date() {
		this->m_year = 0;
		this->m_day = 0;
		this->m_month = 0;
		this->m_compare = 0;
		this->errCode(NO_ERROR);
	}

	Date::Date(int year, int month, int day) {
		int comp = year*372 + month * 31 + day;
		if ( year < min_year || year > max_year ||
			 month > 12 || month < 1 ||
			 day < 1 || day > mdays(year, month) ||
			 comp < min_date ){
			*this = Date();
		}
		else {
			this->m_year = year;
			this->m_day = day;
			this->m_month = month;
			this->m_compare = comp;
			this->errCode(NO_ERROR);
		}
	}

	istream& Date::read(istream& istr) {
		int year, mon, day;
		char dim = '/';
		istr >> year >> dim >> mon >> dim >> day;
		if(istr.fail()){
			this->errCode(CIN_FAILED);
			istr.ignore(2000);
		}
		else if (year > max_year || year < min_year) {
			this->errCode(YEAR_ERROR);
		}
		else if (mon > 12 || mon < 1) {
			this->errCode(MON_ERROR);
		}
		else if (day > Date::mdays(year, mon) || day < 1) {
			this->errCode(DAY_ERROR);
		}
		else if (!Date::isValid(year, mon, day)) {
			this->errCode(PAST_ERROR);
		}
		else {
			*this = Date(year, mon, day);
		}
		return istr;
	}
	istream& operator>>(istream& is, Date& rhs) {
		rhs.read(is);
		return is;
	}
	ostream& Date::write(ostream& ostr) const{
		if (this->m_compare == 0) { 
			ostr << "0/00/00";
		}
		else {

			ostr << this->m_year << '/';
			ostr.width(2);
			ostr.fill('0');
			ostr << this->m_month << '/' << this->m_day;
		}
		return ostr;
	}
	ostream& operator<<(ostream& os, const Date& rhs) {
		rhs.write(os);
		return os;
	}


	bool Date::operator!=(const Date & rhs) const{
		return (this->m_compare != rhs.m_compare) && this->m_compare && rhs.m_compare;
	}
	bool Date::operator==(const Date & rhs) const
	{
		return (this->m_compare == rhs.m_compare) && this->m_compare && rhs.m_compare;
	}
	bool Date::operator<(const Date & rhs) const
	{
		return (this->m_compare < rhs.m_compare) && this->m_compare && rhs.m_compare;
	}
	bool Date::operator>(const Date & rhs) const
	{
		return (this->m_compare > rhs.m_compare) && this->m_compare && rhs.m_compare;
	}
	bool Date::operator<=(const Date & rhs) const
	{
		return (this->m_compare <= rhs.m_compare) && this->m_compare && rhs.m_compare;
	}
	bool Date::operator>=(const Date & rhs) const
	{
		return (this->m_compare >= rhs.m_compare) && this->m_compare && rhs.m_compare;
	}

	bool Date::isValid(int year, int mon, int day)const { 
		return  (year * 372 + mon * 31 + day) >= min_date;
	}
}