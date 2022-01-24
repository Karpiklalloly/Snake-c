#pragma once
#ifndef WINDOW
#define WINDOW
#include "Window.h"
#endif
#ifndef IO
#define IO
#include <iostream> 
#endif
#ifndef SDL
#define SDL
#include <SDL.h>
#endif
#ifndef TTF
#define TTF
#include<SDL_ttf.h>
#endif
#ifndef IMAGE
#define IMAGE
#include<SDL_image.h>
#endif
#ifndef WINDOWSH
#define WINDOWSH
#include <Windows.h>
#endif
#ifndef FUNCTIONAL
#define FUNCTIONAL
#include <functional>
#endif
#ifndef VECTOR
#define VECTOR
#include <vector>
#endif
#ifndef SNAKE
#define SNAKE
#include "Snake.h"
#endif

extern Snake snake;

class Game :
    public Window
{
   

	char** field;
	int x_offset = 450;
	int y_offset = 100;
	int sizeOfSnake = 30;
	int controlfield1 = 16;
	int controlfield2 = 12;

	void DrawingText() override;
	void Render() override;
	void DoAction(int index) override;

	void fillarrayinpoints(int x1, int y1, int x2, int y2)
	{
		field[x1][y1] = ' ';
		field[x2][y2] = ' ';

	}
	void fillarray()
	{
		int i, j;
		for (i = 1;i < controlfield1-1;i++)
		{
			for (j = 1;j < controlfield2-1;j++)
			{
				field[i][j] = ' ';
			}
		}
	}
	void setborders()
	{
		//walls
		int i;
		for (i = 0;i < controlfield2;i++)
		{
			field[0][i] = '#';
		}
		field[0][controlfield2] = '\n';
		for (i = 0;i < controlfield2;i++)
		{
			field[controlfield1-1][i] = '#';
		}
		field[controlfield1-1][controlfield2] = '\n';
		for (i = 0;i < controlfield1;i++)
		{
			field[i][0] = '#';
		}
		for (i = 0;i < controlfield1;i++)
		{
			field[i][controlfield2-1] = '#';
			field[i][controlfield2] = '\n';
		}
	}
	void CustomLogic() override;
	int TimeLeft(double time)
	{
		static int nextTime = 0;
		int nowTime = SDL_GetTicks();
		time *= 1000;
		//std::cout << (nextTime - nowTime) / 1000 << std::endl;
		if (nextTime <= nowTime)
		{
			nextTime = nowTime + time;
			return 0;
		}
		return nextTime - nowTime;

	}
	void DrawSnake();
	void copytoarray(char** array)
	{
		for (int i = 0; i < controlfield1; i++)
		{
			for (int j = 0; j < controlfield2; j++)
			{
				array[i][j] = field[i][j];
			}
		}
	}
public:
	Game(const char* Name, int w, int h);
};

