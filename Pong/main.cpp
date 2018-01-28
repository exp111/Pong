#include <iostream>
#include <time.h>

#include "pong.h"
using namespace std;

int main()
{
	srand(time(NULL)); //Generate random seed
	Pong* pong = new Pong;
	pong->init();

	while (pong->isRunning())
		pong->run();

	system("PAUSE");
	return 0;
}