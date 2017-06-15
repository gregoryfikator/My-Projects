#pragma once

class Obstacle
{
	int		X1;
	int		Y1;
	int		X2;
	int		Y2;	

public:
	Obstacle(int newX1, int newY1, int newX2, int newY2)
	{
		X1 = newX1;
		Y1 = newY1;
		X2 = newX2;
		Y2 = newY2;
	}
	Obstacle(Obstacle &copied)
	{
		X1 = copied.X1;
		Y1 = copied.Y1;
		X2 = copied.X2;
		Y2 = copied.Y2;
	}
	~Obstacle(){}
	
	int GetX1Pos() { return X1; }
	int GetY1Pos() { return Y1; }
	int GetX2Pos() { return X2; }
	int GetY2Pos() { return Y2; }
};