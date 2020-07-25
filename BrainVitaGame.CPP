/*

*/


#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <process.h>

#define RADIUS 10

int circleData[45];
int xAxis[] = {25,25,25,50,50,50,75,75,75,100,100,100,100,100,100,100,100,100,125,125,125,125,125,125,125,125,125,
					150,150,150,150,150,150,150,150,150,175,175,175,200,200,200,225,225,225};
int yAxis[] = {225,250,275,225,250,275,225,250,275,150,175,200,225,250,275,300,325,350,150,175,200,225,250,275,300,
					325,350,150,175,200,225,250,275,300,325,350,225,250,275,225,250,275,225,250,275};

void gameDashBoard();
void drawGamePlatform();
void startGame();

int getXCordinate(int , char);
int getYCordinate(int , char);
void fillCircle(int , int);
void emptyCircle(int , int);
void fillCircleData(int ,int,int);

//Whether to check move is valid or not
int commonValidMoves(int , int);
int allSideToMiddleSideMoves(int , char , int , char*);
int middleSideToAllSideMoves(int , int , char , char*);

//For finding Middle Point
int commonMiddlePoints(int , int);

void moveMarble(int , char , int , char);
void convertToUpperCase(char* , char*);
int checkOutOfRangePointAndDirection(int , char , int , char);



void main()
{
	int gdriver = DETECT, gmode;

	initgraph(&gdriver, &gmode, "c:\\turboc3\\bgi");

	gameDashBoard();

	getch();

	closegraph();

}

void gameDashBoard()
{
	int choice = 0;
	do
	{
		printf("\n\t    _____     _______        .        ________               ");
		printf("\n\t    |    \\    |     /       / \\          |       |\\     | ");
		printf("\n\t    |     \\   |    /       /   \\         |       | \\    | ");
		printf("\n\t    |______\\  |  /        /     \\        |       |  \\   | ");
		printf("\n\t    |      /  | \\        /-------\\       |       |   \\  | ");
		printf("\n\t    |     /   |   \\     /         \\      |       |    \\ | ");
		printf("\n\t    |____/    |     \\  /           \\  ___|____   |     \\| ");

		printf("\n\n");
		printf("\n\t        \\           /  _______   ________       .       ");
		printf("\n\t         \\         /      |         |          / \\     ");
		printf("\n\t          \\       /       |         |         /   \\    ");
		printf("\n\t           \\     /        |         |        /-----\\   ");
		printf("\n\t            \\   /         |         |       /       \\  ");
		printf("\n\t             \\./       ___|___      |      /         \\ ");


		printf("\n\n\n\n");
		printf("\n\t   Press 1 for Start the Game ");
		printf("\n\t   Press 2 for Exit           ");

		printf("\n\n\n\t   Enter your choice : ");
		scanf("%d",&choice);

		if(choice == 1)
		{
			clrscr();
			cleardevice();
			startGame();
		}
		else if(choice == 2)
		{
			exit(0);
		}
		else
		{
			printf("\n\t   Invalid Choice ");
			getch();
			clrscr();
			cleardevice();
		}
	}while(choice != 2);
}

void startGame()
{
	for(int i=0 ; i<45 ; i++)
	{
		circleData[i] = 0;
	}

	circleData[22] = 1;

	int fromValue,toValue;
	char fromDirection,toDirection;

	while(fromValue != 10)
	{
		drawGamePlatform();
		//printf("\t\t\t\t Enter the marble value which you want to pick : ");
		scanf("%d",&fromValue);
		fflush(stdin);
		//printf("\n\t\t\t\t Enter the Direction of marble which you want to pick : ");
		scanf("%c",&fromDirection);
		//printf("\n\t\t\t\t Enter to place value where you want to move your marble : ");
		scanf("%d",&toValue);
		fflush(stdin);
		//printf("\n\t\t\t\t Enter to Direction of place where you want to move your marble : ");
		scanf("%c",&toDirection);

		moveMarble(fromValue , fromDirection , toValue , toDirection);
		clrscr();
		cleardevice();
	}

}

void drawGamePlatform()
{
	for(int i=0 ; i<45 ; i++)
	{
		if(circleData[i] == 0)
		{
			fillCircle(xAxis[i] , yAxis[i]);
		}
		else
		{
			circle(xAxis[i] , yAxis[i] , RADIUS);
		}
	}
}

void moveMarble(int fromPoint , char fromDirection , int toPoint , char toDirection)
{
	int midPoint = 0;
	char midDirection = '0';

	int toXCordinate = 0;
	int toYCordinate = 0;
	int fromXCordinate = 0;
	int fromYCordinate = 0;
	int midXCordinate = 0;
	int midYCordinate = 0;

	int toCircle = -1;
	int fromCircle = -1;
	int midCircle = -1;

	convertToUpperCase(&fromDirection , &toDirection);

	if(checkOutOfRangePointAndDirection(fromPoint , fromDirection , toPoint , toDirection))
	{
		if(fromDirection == toDirection)
		{
			midDirection = fromDirection;
			midPoint  = commonValidMoves(fromPoint , toPoint);
		}
		else if(fromDirection == 'M')
		{
			midPoint = middleSideToAllSideMoves(fromPoint , toPoint, toDirection , &midDirection);
		}
		else
		{
			midPoint = allSideToMiddleSideMoves(fromPoint , fromDirection , toPoint , &midDirection);
		}

		if(midPoint != 0)
		{
			toXCordinate = getXCordinate(toPoint , toDirection);
			toYCordinate = getYCordinate(toPoint , toDirection);
			fromXCordinate = getXCordinate(fromPoint , fromDirection);
			fromYCordinate = getYCordinate(fromPoint , fromDirection);
			midXCordinate = getXCordinate(midPoint , midDirection);
			midYCordinate = getYCordinate(midPoint , midDirection);


			toCircle = getpixel(toXCordinate+1 , toYCordinate+1);
			fromCircle = getpixel(fromXCordinate+1 , fromYCordinate+1);
			midCircle = getpixel(midXCordinate+1 , midYCordinate+1);

			if(fromCircle == 15 && midCircle == 15 && toCircle == 0)
			{
				fillCircleData(toXCordinate , toYCordinate , 0);
				fillCircleData(fromXCordinate , fromYCordinate , 1);
				fillCircleData(midXCordinate , midYCordinate , 1);
			}
			else
			{
				printf("\n\t\t\t\t Invalid Move");
				getch();
			}
		}
	}
}


int checkOutOfRangePointAndDirection(int fromPoint , char fromDirection , int toPoint , char toDirection)
{
	if(fromPoint == 10)
	{
		exit(0);
		return 0;
	}
	else if( (fromPoint >= 1 && fromPoint <= 9) && (toPoint >= 1 && toPoint <= 9))
	{
		if(fromDirection != 'M' && fromDirection != 'L' && fromDirection != 'R' &&
			fromDirection != 'U' && fromDirection != 'D')
		{
			printf("\n From Direction is out of Range");
			getch();
			return 0;
		}
		else if(toDirection != 'M' && toDirection != 'L' && toDirection != 'R' &&
				toDirection != 'U' && toDirection != 'D')
		{
			printf("\n To Direction is out of Range");
			getch();
			return 0;
		}
		return 1;
	}
	else
	{
		printf("\n Point is Out Of Range");
		getch();
		return 0;
	}
}

void convertToUpperCase(char* fromDirectionPointer , char* toDirectionPointer)
{
	if(*(fromDirectionPointer) >= 'a' && *(fromDirectionPointer) <= 'z')
	{
		*(fromDirectionPointer) = *(fromDirectionPointer) - 32;
	}

	if( *(toDirectionPointer) >= 'a' && *(toDirectionPointer) <= 'z')
	{
		*(toDirectionPointer) = *(toDirectionPointer) - 32;
	}

}


void fillCircle(int x , int y)
{
		setfillstyle(SOLID_FILL , WHITE);

		circle(x , y , RADIUS);

		floodfill(x , y , WHITE);
}

void emptyCircle(int x , int y)
{
	setfillstyle(SOLID_FILL , BLACK);

	circle(x , y , RADIUS);

	floodfill(x , y , BLACK);

	circle(x , y , RADIUS);
}

int commonValidMoves(int fromPoint , int toPoint)
{
	int destination[10][2] = {{0,0}, {3,7}, {8,0}, {1,9}, {6,0}, {0,0}, {4,0}, {1,9}, {2,0}, {3,7}};
	int middlePoint[10][2] = {{0,0}, {2,4}, {5,0}, {2,6}, {5,0}, {0,0}, {5,0}, {4,8}, {5,0}, {6,8}};

	if(destination[fromPoint][0] == toPoint)
	{
		return middlePoint[fromPoint][0];
	}
	else if(destination[fromPoint][1] == toPoint)
	{
		return middlePoint[fromPoint][1];
	}
	else
	{
		return 0;
	}
}

int allSideToMiddleSideMoves(int fromPoint , char fromDirection , int toPoint , char* middlePointDirection)
{
	int leftSideToMidSide[10] = {0, 0, 1, 2, 0, 4, 5, 0, 7, 8};
	int leftSideMiddlePoint[10] = {0, 0, 3, 1, 0, 6, 4, 0, 9, 7};
	char leftSideMiddlePointDirection[] = "00LM0LM0LM";


	int rightSideToMidSide[10] = {0, 2, 3, 0, 5, 6, 0, 8, 9, 0};
	int rightSideMiddlePoint[10] = {0, 3, 1, 0, 6, 4, 0, 9, 7, 0};
	char rightSideMiddlePointDirection[] = "0MR0MR0MR0";

	int downSideToMidSide[10]    = {0, 4, 5, 6, 7, 8, 9, 0, 0, 0};
	int downSideMiddlePoint[10] = {0, 7, 8, 9, 1, 2, 3, 0, 0, 0};
	char downSideMiddlePointDirection[] = "0MMMDDD000";

	int upperSideToMidSide[10]    = {0, 0, 0, 0, 1, 2, 3, 4, 5, 6};
	int upperSideMiddlePoint[10] = {0, 0, 0, 0, 7, 8, 9, 1, 2, 3};
	char upperSideMiddlePointDirection[] = "0000UUUMMM";

	if(fromDirection == 'L')
	{
		if(leftSideToMidSide[fromPoint] == toPoint)
		{
			*middlePointDirection = leftSideMiddlePointDirection[fromPoint];
			return leftSideMiddlePoint[fromPoint];
		}
	}
	else if(fromDirection == 'R')
	{
		if(rightSideToMidSide[fromPoint] == toPoint)
		{
			*middlePointDirection = rightSideMiddlePointDirection[fromPoint];
			return rightSideMiddlePoint[fromPoint];
		}
	}
	else if(fromDirection == 'U')
	{
		if(upperSideToMidSide[fromPoint] == toPoint)
		{
			*middlePointDirection = upperSideMiddlePointDirection[fromPoint];
			return upperSideMiddlePoint[fromPoint];
		}
	}
	else
	{
		if(downSideToMidSide[fromPoint] == toPoint)
		{
			*middlePointDirection = downSideMiddlePointDirection[fromPoint];
			return downSideMiddlePoint[fromPoint];
		}
	}

	*middlePointDirection = '0';
	return 0;
}

int middleSideToAllSideMoves(int fromPoint , int toPoint , char toDirection , char* midPointDirection)
{
	int middleToAllSidePoint[10][4] = {{0,0,0,0}, {2,4,0,0}, {3,5,1,0}, {6,2,0,0}, {5,7,1,0},
							{6,8,4,2}, {9,5,3,0}, {8,4,0,0}, {5,7,9,0}, {6,8,0,0}};

	int middleToAllSideDirection[10][4] = {{0,0,0,0}, {76,85,0,0}, {76,85,82,0}, {85,82,0,0}, {76,85,68,0},
											{76,85,82,68}, {85,82,68,0}, {76,68,0,0}, {68,82,76,0}, {68,82,0,0}};


	int middleSideToMidPoint[10][4] = {{0,0,0,0}, {3,7,0,0}, {1,8,3,0}, {9,1,0,0}, {6,1,7,0},
										{4,2,6,8}, {3,4,9,0}, {9,1,0,0}, {2,9,7,0}, {3,7,0,0}};

	int middleSideToMidPointDirection[10][4] = {{0,0,0,0}, {76,85,0,0}, {77,85,77,0}, {85,82,0,0},
												{76,77,77,0}, {77,77,77,77}, {77,82,77,0}, {76,68,0,0},
												{68,77,77,0}, {68,82,0,0}};
	for(int i=0 ; i<4 ; i++)
	{
		if(middleToAllSidePoint[fromPoint][i] == toPoint && middleToAllSideDirection[fromPoint][i] == toDirection)
		{
			*midPointDirection = middleSideToMidPointDirection[fromPoint][i];
			return middleSideToMidPoint[fromPoint][i];
		}
	}

	*midPointDirection = '0';
	return 0;
}


int getXCordinate(int point , char direction)
{
	int leftSide[] = {25, 50, 75};
	int rightSide[] = {175, 200, 225};
	int upperMiddleDownSide[] = {100, 125, 150};

	if(direction == 'R')
	{
		return rightSide[(point-1) % 3];
	}
	else if(direction == 'L')
	{
		return leftSide[(point-1) % 3];
	}
	else
	{
		return upperMiddleDownSide[(point-1) % 3];
	}
}

int getYCordinate(int point , char direction)
{
	int upperSide[] = {150, 175, 200};
	int leftMiddleRightSide[] = {225, 250, 275};
	int lowerSide[] = {300, 325, 350};

	if(direction == 'U')
	{
		return upperSide[(point-1) / 3];
	}
	else if(direction == 'D')
	{
		return lowerSide[(point-1) / 3];
	}
	else
	{
		return leftMiddleRightSide[(point-1) / 3];
	}
}

void fillCircleData(int xPoint , int yPoint , int num)
{
	for(int i=0 ; i<45 ; i++)
	{
		if(xPoint == xAxis[i] && yPoint == yAxis[i])
		{
			circleData[i] = num;
		}
	}
}
