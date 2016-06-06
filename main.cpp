#include "problemd.h"

using namespace std;

int main(){

	ProblemD myproblem;

	try{
		myproblem.run();
	}
	catch(const std::exception&){
		PAUSE
		return EXIT_FAILURE;
	}

	PAUSE
	return 0;
}