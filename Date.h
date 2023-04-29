#ifndef _AID_DATE_H
#define _AID_DATE_H

#define NO_ERROR 0
#define CIN_FAILED 1
#define DAY_ERROR 2
#define MON_ERROR 3
#define YEAR_ERROR 4
#define PAST_ERROR 5

namespace aid {
	const int min_year = 2018;
	const int max_year = 2038;
	const int min_date = 751098;
	class Date {
		int m_year;
		int m_month;
		int m_day;
		int m_compare;
		int m_err;
		bool isValid(int day, int mon, int year) const;
	public:
		void errCode(int errorCode); 
		int errCode() const; 
		bool bad() const;
		int mdays(int year, int month);
		Date();
		Date(int year, int month, int day);
		bool operator!=(const Date &rhs) const;
		bool operator==(const Date &rhs) const;
		bool operator<(const Date &rhs) const;
		bool operator>(const Date &rhs) const;
		bool operator<=(const Date &rhs) const;
		bool operator>=(const Date &rhs) const;
		std::istream& read(std::istream&);
		std::ostream& write(std::ostream&) const;
	};
	std::istream& operator>>(std::istream& is, Date& rhs);
	std::ostream& operator<<(std::ostream& os, const Date& rsh);
}

#endif