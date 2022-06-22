#include "Game.h"
#include <iostream>

auto main(int argc, char* argv[]) -> int {
	try
	{
		Game::GetInstance().Run();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << "\n";
	}
	catch (...)
	{
		std::cerr << "FATAL UNKNOWN ERROR HAS OCCURED!" << "\n";
	}
    return 0;
}
