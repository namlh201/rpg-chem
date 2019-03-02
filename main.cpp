#include "init.h"
#include "close.h"
#include "loadTexture.h"
#include "loadMedia.h"
#include <SDL.h>
#include "variable.h"

int main(int argc, char** args) {

    //Start up SDL and create window
	if(!init())
		printf("Failed to initialize!\n");

	else {
		/*//Load media
		if(!loadMedia())
			printf("Failed to load media!\n");*/

		//else {
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while(!quit) {
				//Handle events on queue
				while(SDL_PollEvent(&e) != 0)
					//User requests quit
					if(e.type == SDL_QUIT) quit = true;

				//Clear screen
				SDL_RenderClear(gRenderer);

				//Render texture to screen
				SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		//}
	}

	//Free resources and close SDL
	close();

	return 69;
}
