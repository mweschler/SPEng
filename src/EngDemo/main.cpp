#include "engdemo.h"

int main(int argc, char* argv[]){
	EngDemoApp app;
	int rv = app.run(argc, argv);
	std::getchar();
	return rv;
}