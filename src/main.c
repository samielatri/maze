#include <stdlib.h>
#include <stdio.h>

#include <SDL2/SDL.h>

#include "boolean.h"
#include "constants.h"

/* global variables */


SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int ticksLastFrame = 0;

int isRunning = FALSE;

int playerX = 0;
int playerY = 0;


/* functions */

/* initialize window */
void initializeWindow() {
	
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error while initializing SDL.\n");
		exit(EXIT_FAILURE);
	}
	
	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_BORDERLESS,
	);
	
	if(!window) {
		fprintf(stderr, "Error while creating SDL window.\n");
		exit(EXIT_FAILURE);
	}
	
	renderer = SDL_CreateRenderer(
		window,
		DEFAULT_GRAPHICS_DRIVER,
		0
	)
	
	if(!renderer) {
		fprintf(stderr, "Error creating SDL renderer.\n");
		exit(EXIT_FAILURE);
	}
	
	SDL_SetRenderDrawBlendMode(
		renderer,
		SDL_BLENDMODE_BLEND
	)


}

/* destroy window */
void destroyWindow() {
	SDL_DestroyRenderer(renderer);
	if(renderer) {
		fprintf(stderr, "Error while destroying renderer.\n");
		exit(EXIT_FAILURE);
	}

	SDL_DestroyWindow(window);
	if(window) {
		fprintf(stderr, "Error while destroying window.\n");
		exit(EXIT_FAILURE);
	}

	SDL_Quit();
}


/* initialize player position */
void initializePlayerPosition() {
	playerX = 0;
	playerY = 0;
}


/* initiaze the game */
void initializeGame() {
	initializePlayerPosition();
	isRunning = TRUE;
}


/* stop the game */
void stopGame() {
	isRunning = FALSE;
}

/* render the scene */
void render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_Rect rect = {playerX, playerY, 20, 20};
    SDL_RenderFillRect(renderer, &rect);

    SDL_RenderPresent(renderer);
}

/* wait for next frame */
void waitForNextFrame() {
	int timeForNextFrame = FRAME_TIME_LENGTH - (SDL_GetTicks() - ticksLastFrame);

	if timeForNextFrame > 0 && timeForNextFrame <= FRAME_TIME_LENGTH) {
		SDL_Delay(timeToWait);
	}
}


/* update the scene */
void update() {


	waitForNextFrame();

	float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

	ticksLastFrame = SDL_GetTicks();

	playerX += 50 * deltaTime;
	playerY += 50 * deltaTime;
}

/* handle events */
void handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT: {
            stopGame();
            break;
        }
        case SDL_KEYDOWN: {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                stopGame();
			}
            break;
        }
    }
}

/* principal program */


int main(int argc, char* args[]) {
	puts("Program is running.\n");

	initializeWindow();
	
	initializeGame();
	
	while (isRunning) {
		handleEvents();
		update();
		render();
	}
	
	destroyWindow();
	
	puts("Program is stopping.\n");

	return EXIT_SUCCESS;
}


