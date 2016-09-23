#include "Obj.h"
#include <iostream>

Obj::Obj(){
	x = 0;
	y = 0;
	width = 0;
	height = 0;
	srand (time(NULL));
	int ran = rand()%20 + 1;
	int temp;

	//decide type
	switch (temp = ran/4){
		case 1:
		type = L;
		break;
		case 2:
		type = T;
		break;
		case 3:
		type = I;
		break;
		case 4:
		type = SQUARE;
		break;
		case 0:
		type = Z;
		break;
	}

	//decide direction
	switch (temp = ran/5){
		case 1:
		dirc = LEFT;
		break;
		case 2:
		dirc = RIGHT;
		break;
		case 3:
		dirc = UP;
		break;
		case 0:
		dirc = DOWN;
		break;
	}
}

int Obj::getX(){return x;}
int Obj::getY(){return y;}
int Obj::getWidth(){return width;}// distance from x to the leftmost
int Obj::getHeight(){return height;}// distance from y to the upmost

Type Obj::getType(){return type;}
Direction Obj::getDirc(){return dirc;}

void Obj::setX(int mx){x = mx;}
void Obj::setY(int my){y = my;}

void Obj::setType(Type t){ type = t;}
void Obj::setDirc(Direction d){dirc = d;}

std::vector<int> Obj::self(){
	std::vector<int> v;
	switch (type){
		case L:
		switch(dirc){
			//  ***
			//    o
			case LEFT:  
			v.push_back(x-2);
			v.push_back(y-1);
			v.push_back(x-1);
			v.push_back(y-1);
			v.push_back(x);
			v.push_back(y-1);
			v.push_back(x);
			v.push_back(y);
			width = 2;
			height = 1;
			break;   

			//  *
			//  **o
			case RIGHT:
			v.push_back(x-2);
			v.push_back(y-1);
			v.push_back(x-2);
			v.push_back(y);
			v.push_back(x-1);
			v.push_back(y);
			v.push_back(x);
			v.push_back(y);
			width = 2;
			height = 1;
			break;

			//   *
			//   *
			//  *o
			case UP:
			v.push_back(x-1);
			v.push_back(y);
			v.push_back(x);
			v.push_back(y);
			v.push_back(x);
			v.push_back(y-1);
			v.push_back(x);
			v.push_back(y-2);
			width = 1;
			height = 2;
			break;

			//  *o
			//  *
			//  *
			case DOWN:
			v.push_back(x);
			v.push_back(y);
			v.push_back(x-1);
			v.push_back(y);
			v.push_back(x-1);
			v.push_back(y+1);
			v.push_back(x-1);
			v.push_back(y+2);
			width = 1;
			height = 0;
			break;
		}
		break;

		case T:
		switch(dirc){
			//   *
			//  **
			//   o
			case LEFT:  
			v.push_back(x-1);
			v.push_back(y-1);
			v.push_back(x);
			v.push_back(y-2);
			v.push_back(x);
			v.push_back(y-1);
			v.push_back(x);
			v.push_back(y);
			width = 1;
			height = 2;
			break;   

			//  *
			//  *o
			//  *
			case RIGHT:
			v.push_back(x);
			v.push_back(y);
			v.push_back(x-1);
			v.push_back(y);
			v.push_back(x-1);
			v.push_back(y+1);
			v.push_back(x-1);
			v.push_back(y-1);
			width = 1;
			height = 1;
			break;

			//    *
			//   **o
			case UP:
			v.push_back(x-2);
			v.push_back(y);
			v.push_back(x-1);
			v.push_back(y);
			v.push_back(x-1);
			v.push_back(y-1);
			v.push_back(x);
			v.push_back(y);
			width = 2;
			height = 1;
			break;

			// **o
			//  *
			case DOWN:
			v.push_back(x);
			v.push_back(y);
			v.push_back(x-1);
			v.push_back(y);
			v.push_back(x-1);
			v.push_back(y+1);
			v.push_back(x-2);
			v.push_back(y);
			width = 1;
			height = 0;
			break;
		}
		break;

		case SQUARE:
			// **
			// *o
		v.push_back(x);
		v.push_back(y-1);
		v.push_back(x-1);
		v.push_back(y-1);
		v.push_back(x-1);
		v.push_back(y);
		v.push_back(x);
		v.push_back(y);
		width = 1;
		height = 1;
		break;


		case I:
		switch(dirc){

			//   *
			//   *
			//   *
			//   o
			case LEFT:  
			case RIGHT:
			v.push_back(x);
			v.push_back(y-3);
			v.push_back(x);
			v.push_back(y-2);
			v.push_back(x);
			v.push_back(y-1);
			v.push_back(x);
			v.push_back(y);
			width = 0;
			height = 3;
			break;

			//  ***o
			case DOWN:
			case UP:
			v.push_back(x-3);   
			v.push_back(y);
			v.push_back(x-2);
			v.push_back(y);
			v.push_back(x-1);   
			v.push_back(y);
			v.push_back(x);
			v.push_back(y);
			width = 3;
			height = 0;
			break;
		}
		break;

		case Z:
		switch(dirc){
			//  **
			//   *o
			case LEFT:
			case RIGHT: 
			v.push_back(x-2);
			v.push_back(y-1);
			v.push_back(x-1);
			v.push_back(y-1);
			v.push_back(x-1);
			v.push_back(y);
			v.push_back(x);
			v.push_back(y);
			width = 2;
			height = 1;
			break;   

			//   *
			//  *o
			//  *
			case UP:
			case DOWN:
			v.push_back(x);
			v.push_back(y-1);
			v.push_back(x);
			v.push_back(y);
			v.push_back(x-1);
			v.push_back(y);
			v.push_back(x-1);
			v.push_back(y+1);
			width = 1;
			height = 1;
			break;
		}
		break;

		default:
		std::cout << "default in Obj::self\n"; 
		break;
	}
	return v;


}





