#include "Game.h"



int main(int argc, char* argv[]) {
	Game().play(argc,argv);
	//for some reason using colors the way instructed
	//carries the last loaded color to the next program
	//and if the next program is chosen to be B&W
	//the entire program is printed in the last color.
	// a naive solution is to set the last color in the console to be white.
	SetTextColor(HDC(), RGB(255, 255, 255));
	
	return 0;
}

