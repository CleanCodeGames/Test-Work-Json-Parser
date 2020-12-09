#include "EasyJsonPars.h"

int main() {

	ejp::EasyJsonPars pars;
	pars.Read("test");
	pars.Print();
	return 0;
}