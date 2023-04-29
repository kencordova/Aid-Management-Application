#ifndef _AID_ERROR_H
#define _AID_ERROR_H
#include <iostream>
namespace aid {
	class Error {
		char* m_errorMessage;
	public:
		explicit Error(const char * errorMessage = nullptr);
		~Error();
		void clear();
		bool isClear() const;
		void message(const char* str);
		const char* message() const;
	};
	std::ostream& operator<<(std::ostream& os, const Error& rhs);
}

#endif