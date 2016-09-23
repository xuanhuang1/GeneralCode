#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "enums.h"

class Obj{
private:
	int x;
	int y;
	Type type;
	Direction dirc;
	int width;
	int height;

public:
	Obj();
	int getX();
	int getY();
	void setX(int);
	void setY(int);
	int getWidth();
	int getHeight();
	Type getType();
	Direction getDirc();
	void setType(Type);
	void setDirc(Direction);
	std::vector<int> self();
	std::vector<int> below();
	std::vector<int> left();
	std::vector<int> right();

};