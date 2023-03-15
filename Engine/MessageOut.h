#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <utility>

class MessageOut
{
private:
	MessageOut(std::ostream& _os) : os(_os) {}

public:
	static MessageOut Console;
	static MessageOut Log;

	static void OpenLog(std::string fileName);

	template<typename T>
	MessageOut& operator<< (T&& message) {
		os << std::forward<T>(message);
		return *this;
	}

	MessageOut& operator<<(std::ostream& (*pf)(std::ostream&)) {
		os << pf;
		return *this;
	}

private:
	static std::ofstream logFile;

	std::ostream& os;
};

