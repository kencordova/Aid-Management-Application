#include <iostream>
#include <cstring>
#include "Error.h"
using namespace std;
namespace aid {


	Error::Error(const char* errorMessage) {
		if (errorMessage == nullptr || errorMessage[0] == '\0') {
			this->m_errorMessage = nullptr;
		}
		else {
			int len = strlen(errorMessage);
			this->m_errorMessage = new char[len+1];
			strncpy(this->m_errorMessage, errorMessage, len+1);
		}
	}

	Error::~Error() {
		delete[] this->m_errorMessage;
	}

	void Error::clear() {
		delete[] this->m_errorMessage;
		this->m_errorMessage = nullptr;
	}

	bool Error::isClear() const {
		return (this->m_errorMessage == nullptr || this->m_errorMessage[0] == '\0');
	}

	void Error::message(const char* str) {
		this->clear();
		if (str == nullptr || str[0] == '\0') {
			this->m_errorMessage = nullptr;
		}
		else {
			int len = strlen(str);
			this->m_errorMessage = new char[len + 1];
			strncpy(this->m_errorMessage, str, len + 1);
		}
	}

	const char* Error::message() const {
		return (this->isClear() ? nullptr : this->m_errorMessage);
	}

	ostream& operator<<(ostream& os, const Error& rhs) {
		if (!rhs.isClear()) {
			os << rhs.message();
		}
		return os;
	}


}