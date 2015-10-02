#ifndef HELPER_H
#define HELPER_H

#include <string>

class Helper {
public:
	static void logError(const std::string text);
	static int  random(int min, int max);
};

#endif // HELPER_H
