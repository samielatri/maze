#include <stdlib.h>
#include <stdio.h>

#include <SDL2/SDL.h>

#include "boolean.h"
#include "constants.h"

/* global variables */


SDL_Window* window = NULL;	// window of the game 
SDL_Renderer* renderer = NULL;	// graphics renderer of the game

int ticksLastFrame = 0;	// tick of last frame

int isRunning = FALSE;	// state of the game

int playerX = 0;	// poition of player on x axis
int playerY = 0;	// position of player on y axis


/* functions */

/* initialize window */
void initializeWindow() {
	// initialize SDL with everything
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error while initializing SDL.\n");
		exit(EXIT_FAILURE);
	}
	
	// creating a window
	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_BORDERLESS,
	);
	
	// verifying that window was created
	if(!window) {
		fprintf(stderr, "Error while creating SDL window.\n");
		exit(EXIT_FAILURE);
	}
	
	// creating rednderer
	renderer = SDL_CreateRenderer(
		window,
		DEFAULT_GRAPHICS_DRIVER,
		0
	)

	// veritfying that render was created
	if(!renderer) {
		fprintf(stderr, "Error creating SDL renderer.\n");
		exit(EXIT_FAILURE);
	}
	
	// setting the renderer mode to blend mode (3D)
	SDL_SetRenderDrawBlendMode(
		renderer,
		SDL_BLENDMODE_BLEND
	)


}

/* destroy window */
void destroyWindow() {
	// destroy renderer
	SDL_DestroyRenderer(renderer);
	// verifying that renderer was destroyed
	if(renderer) {
		fprintf(stderr, "Error while destroying renderer.\n");
		exit(EXIT_FAILURE);
	}

	// destroy window
	SDL_DestroyWindow(window);
	// verifying that window was destroyed
	if(window) {
		fprintf(stderr, "Error while destroying window.\n");
		exit(EXIT_FAILURE);
	}
	// quitting SDL
	SDL_Quit();
}


/* initialize player position */
void initializePlayerPosition() {
	playerX = 0;	// seeting position of player to 0 on x axis
	playerY = 0;	// seeting position of player to 0 on y axis
}


/* initiaze the game */
void initializeGame() {
	initializePlayerPosition();	// initialize player position 
	isRunning = TRUE;	// setting state of game on running mode
}


/* stop the game */
void stopGame() {
	isRunning = FALSE;	// setting state of game on stopped mode
}

/* render the scene */
void render() {
	// set color of renderer
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    	// clear renderer
	SDL_RenderClear(renderer);
	
	/* creating the player */
	
	// set color of renderer
    	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    	
	// creating rectangle that represents the player
	SDL_Rect rect = {playerX, playerY, 20, 20};
    	
	// filling the rectangle that reprensents the player
	SDL_RenderFillRect(renderer, &rect);

	// render what renderer has at the present moment
    	SDL_RenderPresent(renderer);
}

/* wait for next frame */
void waitForNextFrame() {
	int timeForNextFrame = FRAME_TIME_LENGTH - (SDL_GetTicks() - ticksLastFrame);	// time for getting next frame
	// wait for next frame only and only if time is between bounds
	if (timeForNextFrame > 0 && timeForNextFrame <= FRAME_TIME_LENGTH) {
		SDL_Delay(timeToWait);	// waiting for timeToWait ticks
	}
}


/* update the scene */
void update() {
	// wait for next frame
	waitForNextFrame();
	// delta time which is used to adjust rotation to be same on all computers
	float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;
	// getting ticks of last frame
	ticksLastFrame = SDL_GetTicks();
	// updating position of player, multiplying by deltaTime only to be same for all computers
	playerX += 50 * deltaTime;
	playerY += 50 * deltaTime;
}

/* handle events */
void handleEvents() {
	// sdl event and listener
	SDL_Event event;
    	SDL_PollEvent(&event);
	
 	// depending on type of event
    	switch (event.type) {
        	case SDL_QUIT: {	// if quit
            		stopGame();	// stop game
            		break;
        	}
        	case SDL_KEYDOWN: {	// if key pressed
            		if (event.key.keysym.sym == SDLK_ESCAPE) {	// escape key
                		stopGame();	// stop game
			}
            		break;
        	}
    	}
}

/* game loop : all logic is in this loop */
void gameLoop() {
	while (isRunning) { // while game running do
		handleEvents(); // handle events
		update(); // update 
		render(); // render
	}	
}

/* principal program */


int main(int argc, char* args[]) {
	//puts("Program is running.\n");

	// intializeWindow
	initializeWindow();
	// intializeGame
	initializeGame();

	// game loop
	gameLoop();
	
	// destroy window
	destroyWindow();
	
	//puts("Program is stopping.\n");

	return EXIT_SUCCESS;
}


