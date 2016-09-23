#include <iostream>
#include <vector> 
#include "Obj.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <string>
#include <cmath>


using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;


//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image as texture
SDL_Texture* loadTexture( std::string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

bool init()
{
	//Initialization flag
	bool success = true;


	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Tetris Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Nothing to load
	return success;
}

void close()
{
	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* loadTexture( std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}



void vanish(vector<vector<int> >& a, int &score){
	for(int i=0; i<10; i++)    //This loops on the rows.
	{
		int rowSum = 0;
		for(int j=0; j<10; j++){ //This loops on the columns
			if(a[i][j] == 1){ // if the cell is occupied, sum+1
				rowSum ++;
			}
		}
		
		if(rowSum == 10){  // if the row is full

			// set the top row to all 0s
			for(int j=0; j<10; j++){ 
				a[0][j] = 0;
			}

			//move everything above down a level
			for(int k=i; k>1; k--){    
				for(int j=0; j<10; j++){ 
					a[k][j] = a[k-1][j];
				}
			}

			score += 100;

			cout <<endl;
			cout << "score : " << score << endl;
			cout <<endl;
		}
	}
}

//if the bottom touch anything to cause it stop
bool objTouch(vector<vector<int> >& board, Obj* tit){
	for (int i = 0 ; i< tit->self().size(); i+=2){
		if (tit->self()[i+1]>8){
			return true;
		}

		if(board[tit->self()[i+1]+1][tit->self()[i]] == 1){
			return true;
		}
	}

	return false;
}

void generateObj(Obj* tit, int t){
	srand (time(NULL)+t);
	int ran = rand()%20 + 1;
	int temp;

	//decide type
	switch (temp = ran/4){
		case 1:
		tit->setType(L);
		break;
		case 2:
		tit->setType(T);
		break;
		case 3:
		tit->setType(I);
		break;
		case 4:
		tit->setType(SQUARE);
		break;
		case 0:
		tit->setType(Z);
		break;
	}

	//decide direction
	switch (temp = ran/5){
		case 1:
		tit->setDirc(LEFT);
		break;
		case 2:
		tit->setDirc(RIGHT);
		break;
		case 3:
		tit->setDirc(UP);
		break;
		case 0:
		tit->setDirc(DOWN);
		break;
	}
}

bool ifEmpty(Obj* titr, vector<vector<int> >& grid){
	for (int i = 0 ; i< titr->self().size(); i+=2){
		if(grid[titr->self()[i]][titr->self()[i]+1] == 1){
			return false;
		}
	}
	return true;
}

bool ifInBound(Obj* titr, vector<vector<int> > grid){
	for (int i = 0 ; i< titr->self().size(); i+=2){
		if(titr->self()[i+1] < 0 || titr->self()[i+1] > 9){
			return false;
		}
		if(titr->self()[i] < 0 || titr->self()[i] > 9){
			return false;
		}
	}
	return true;
}

bool rightAvail(Obj* titr, vector<vector<int> > grid){
	for (int i = 0 ; i< titr->self().size(); i+=2){
		if(grid[titr->self()[i+1]][titr->self()[i]+1] == 1){
			return false;
		}
	}
	return true;
}

bool leftAvail(Obj* titr, vector<vector<int> > grid){
	for (int i = 0 ; i< titr->self().size(); i+=2){
		if(grid[titr->self()[i+1]][titr->self()[i]-1] == 1){
			return false;
		}
	}
	return true;
}


void rotate(Obj* titr, vector<vector<int> >& grid){
	switch (titr->getDirc()){
		case LEFT:
		titr->setDirc(UP);
		titr->self();
		if( ifInBound(titr, grid) && ifEmpty(titr, grid) ){

		}else{
			titr->setDirc(LEFT);
			titr->self();
		}
		break;
		case UP:
		titr->setDirc(RIGHT);
		titr->self();
		if( ifInBound(titr, grid) && ifEmpty(titr, grid) ){

		}else{
			titr->setDirc(UP);
			titr->self();
		}
		break;
		case RIGHT:
		titr->setDirc(DOWN);
		titr->self();
		if( ifInBound(titr, grid) && ifEmpty(titr, grid) ){

		}else{
			titr->setDirc(RIGHT);
			titr->self();
		}
		break;
		case DOWN:
		titr->setDirc(LEFT);
		titr->self();
		if( ifInBound(titr, grid) && ifEmpty(titr, grid) ){

		}else{
			titr->setDirc(DOWN);
			titr->self();
		}
		break;
	}
}


int main(int argc, char const *argv[])
{
		//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	

			//Event handler
			SDL_Event e;

			int t = 0;	
			int score = 0;
			bool objAppear = true;

			// size of grid
			int size = 10;

			//init grid
			vector<vector<int> > grid;
			vector<vector<int> > grid2;// temperory for each movement 


			grid.resize(size);
			//set empty grid
			for(int i = 0; i < size; i++){
				for(int j = 0; j < size; j++){
					grid[i].push_back(0);
				}
			}

			grid2 = grid;
			Obj* titr;

			int k = 6;
			int first = 0;

			//loop start
			while(k>0){

				first ++;

				vanish(grid, score);
				grid2 = grid;
				SDL_Delay( 700);

				//if there is a new one falling
				if(objAppear == true){
					titr = new Obj();
					generateObj(titr, t);
					titr->self();
					t++;
					titr->setX(5);
					titr->setY(titr->getHeight());

					for (int i = 0 ; i< titr->self().size(); i+=2){
						if(titr->self()[i+1] > -1 && titr->self()[i] > -1){
							if(grid2[titr->self()[i+1]][titr->self()[i]] == 1){
								k = -1;;
							}
						}
					}
					first = 0;
					objAppear = false;
				}

				if(k == -1){
					cout << "\n";
					cout << " YOU LOSE" << endl;
					cout << "\n";
					

				}

				while( SDL_PollEvent( &e ) != 0 )
				{

					if( e.type == SDL_QUIT )
					{
						k = -1;
					}

					else if( e.type == SDL_KEYDOWN )
					{
						//Select surfaces based on key press
						for (int i = 0 ; i< titr->self().size(); i+=2){
							if(titr->self()[i+1] > -1 && titr->self()[i] > -1 && titr->self()[i+1] < 10 && titr->self()[i] < 10 ){
								grid2[titr->self()[i+1]][titr->self()[i]] = 0;
							}

						}

						switch( e.key.keysym.sym )
						{
							case SDLK_RIGHT: //right
							if(titr->getX() < 9){
								if(rightAvail(titr, grid)){
									titr->setX(titr->getX()+1);

									for (int i = 0 ; i< titr->self().size(); i+=2){
										if(titr->self()[i+1] > -1 && titr->self()[i] > -1 && titr->self()[i+1] < 10 && titr->self()[i] < 10 ){
											grid2[titr->self()[i+1]][titr->self()[i]] = 1;
										}
									}
								}
							}
							break;

							case SDLK_LEFT: // left
							if(titr->getX()-titr->getWidth() > 0){
								if(leftAvail(titr, grid)){
									titr->setX(titr->getX()-1);

									for (int i = 0 ; i< titr->self().size(); i+=2){
										if(titr->self()[i+1] > -1 && titr->self()[i] > -1 && titr->self()[i+1] < 10 && titr->self()[i] < 10 ){
											grid2[titr->self()[i+1]][titr->self()[i]] = 1;
										}
									}
								}
							}
							break;

							case SDLK_DOWN: // down
							while(objTouch(grid, titr) == false)
								titr->setY(titr->getY()+1);

							for (int i = 0 ; i< titr->self().size(); i+=2){
								if(titr->self()[i+1] > -1 && titr->self()[i] > -1 && titr->self()[i+1] < 10 && titr->self()[i] < 10 ){
									grid2[titr->self()[i+1]][titr->self()[i]] = 1;
								}
							}

							break;
							
							case SDLK_UP: // up
							rotate(titr, grid2);

							for (int i = 0 ; i< titr->self().size(); i+=2){
								if(titr->self()[i+1] > -1 && titr->self()[i] > -1 && titr->self()[i+1] < 10 && titr->self()[i] < 10 ){
									grid2[titr->self()[i+1]][titr->self()[i]] = 1;
								}
							}


						}
					}
				}

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//if touch, stop and set it to existing background
				if(objTouch(grid, titr) == true){
					for (int i = 0 ; i< titr->self().size(); i+=2)
						grid2[titr->self()[i+1]][titr->self()[i]] = 1;
					grid = grid2;
					objAppear = true;
					delete titr;
				}else{

					for (int i = 0 ; i< titr->self().size(); i+=2)
						grid2[titr->self()[i+1]][titr->self()[i]] = 0;

					if(first > 0){
						//else move it a level down
						titr->setY(titr->getY()+1);
					}

					for (int i = 0 ; i< titr->self().size(); i+=2){
						grid2[titr->self()[i+1]][titr->self()[i]] = 1;
					}

					for (int i = 0 ; i< 10; ++i){
						for (int j = 0 ; j< 10; ++j){
							if (grid2[i][j] == 1){
								SDL_Rect fillRect = { j*60, i*60, 60, 60 };
								SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );		
								SDL_RenderFillRect( gRenderer, &fillRect );
							}
						}
					}

					//pGrid(grid2);
					SDL_RenderPresent( gRenderer );
				}

					//reset temperory grid 
				for(int i = 0; i < size; i++){
					for(int j = 0; j < size; j++){
						grid2[i][j] = 0;
					}
				}
			//loop end

			}
		}
	}

	close();
	return 0;
}
