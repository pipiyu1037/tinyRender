#include "MessageOut.h"

#include <ctime>
#include <chrono>
#include <iomanip>

std::ofstream MessageOut::logFile;
MessageOut MessageOut::Console(std::cout);
MessageOut MessageOut::Log(logFile);

void MessageOut::OpenLog(std::string fileName) {
	logFile.open(fileName, std::ofstream::app);
	if (!logFile) {
		Console << "Open " << fileName << " failed!\n";
	}

	time_t nowTime = time(0);
	tm t;
	localtime_s(&t, &nowTime);
	Log << "\n=================\n";
	Log << t.tm_year + 1900 << "/" << t.tm_mon + 1 << "/" << t.tm_mday << " "
		<< t.tm_hour << ":" << t.tm_min << ":" << t.tm_sec << std::endl;
}