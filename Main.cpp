#include <iostream>
#include "App.h"
#include "Star.h"

using namespace std;

const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGTH = 288;
const int MAGNIFICATION = 2;

int main(int argc, char* argv[])
{
	if (App::Singleton().Init(SCREEN_WIDTH, SCREEN_HEIGTH, MAGNIFICATION))
	{
		App::Singleton().Run();
	}
	return 0;
}



