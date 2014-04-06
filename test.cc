#include "log.hpp"

class hoge {
	int some;
public:
	hoge() {
		some = 999;
		VAR_DUMP(some);
	}
};

int main() {
	int a = 8;
	std::string stringshootr = "aaa";
	VAR_DUMP(stringshootr);
	VAR_DUMP(a);
	hoge h;
	return 0;
}

