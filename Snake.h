#pragma once
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
extern long Random(int from, int to);

enum headview
{
	up = 'A',
	down = 'V',
	left = '<',
	right = '>'

};
struct Point
{
	int x, y;
};
struct Body
{
	Body* next = NULL;
	Body* prev = NULL;
	char symbol = '@';
	Point point;
	Body(int x, int y)
	{
		point.x = x;
		point.y = y;
		std::cout << point.x << "!!!!!!!!!" << point.y << std::endl;
	}
	Body(Point _point)
	{
		point = _point;
		std::cout << point.x << "!!!!!!!!!" << point.y << std::endl;
	}
};
struct Head
{
	Body* body = NULL;
	Body* last = NULL;
	Point pointToAdd;
	Point point;
	void set_head(headview direction)
	{
		symbol = direction;
	}
	headview symbol = up;
	void addbody(Point point)
	{
		if (body == NULL)
		{
			body = new Body(point.x, point.y);
			last = body;
			last->prev = NULL;
			return;
		}
		last->next = new Body(point.x, point.y);
		Body* temp = last;
		last = last->next;
		last->prev = temp;
	}
	void movebody(int x, int y)
	{
		if (body != NULL)
		{
			pointToAdd = last->point;
			body->prev = last;
			last->next = body;
			body = last;
			last = last->prev;
			last->next = NULL;
			body->point.x = x;
			body->point.y = y;
		}
		else
		{
			pointToAdd = point;
		}

	}

	bool hasbodyinpoint(int x, int y)
	{
		Body* _body = body;
		while (_body != NULL)
		{
			if (_body->point.x == x && _body->point.y == y)
			{
				return true;
			}
			_body = _body->next;
		}
		return false;
	}
};

class Snake
{
public:
	enum gameState
	{
		Win,
		Lose,
		None
	};
	gameState state = None;
	const gameState LOSE = Lose;
	const gameState WIN = Win;
	const gameState NONE = None;
	int width;
	int height;

	Head head;
	SDL_Point prevFood;
private:
	struct Text
	{
		UINT16 text[64];
		SDL_Color color;
		SDL_Rect rect = { 0, 0, 0, 0 };
		SDL_Surface* surface = NULL;
		SDL_Texture* texture = NULL;
		Text()
		{
			text[0] = '\0';// устанавливаем цвета шрифта
			color.r = 0;
			color.g = 0;
			color.b = 0;
			color.a = 255;
		}
		Text(const UINT16* t)
		{
			int i = 0;
			for (;t[i] != '\0';i++)
			{
				text[i] = t[i];
			}
			text[i] = t[i];
			color.r = 0;
			color.g = 0;
			color.b = 0;
			color.a = 255;

		}
		~Text()
		{
			if (surface != NULL)
				SDL_FreeSurface(surface);
			if (texture != NULL)
				SDL_DestroyTexture(texture);
		}
	};
	SDL_Point food;

	void eat(char** array, char** array2)
	{
		prevFood = food;
		head.addbody(head.pointToAdd);
		setrandomfood(array, array2, height, width);
		extern int score;
		score++;
	}


	void moveto(char** array, char** array2, int x, int y)
	{
		head.movebody(head.point.x, head.point.y);
		head.point.x = x;
		head.point.y = y;

		//std::cout << "!!!" << array[x][y] << "!!!" << std::endl;

		if (array[x][y] == '*')
		{
			eat(array, array2);
		}
		else if (array[x][y] == '#' || head.hasbodyinpoint(x, y))
		{
			lose();
		}

	}

	void win()
	{
		std::cout << "Вы win" << std::endl;
		std::cout << "Если хотите играть заново, нажмите Enter" << std::endl;
		std::cout << "Если хотите выйти, нажмите Escape" << std::endl;
		state = WIN;
	}

	void lose()
	{
		std::cout << "Вы проиграли" << std::endl;
		std::cout << "Если хотите играть заново, нажмите Enter" << std::endl;
		std::cout << "Если хотите выйти, нажмите Escape" << std::endl;
		state = LOSE;

	}

	
public:
	void setstartposition()
	{
		head.point.x = height/2;
		head.point.y = width/2;
		Body* cur = head.body;
		Body* temp;
		while (cur != NULL)
		{
			temp = cur->next;
			delete cur;
			cur = temp;
		}
		head.body = NULL;
		extern int score;
		score = 0;
	}
	SDL_Point getcherrypoint()
	{
		return food;
	}

	void checkwin()
	{
		extern int score;
		extern int max_score;
		if (score >= max_score)
		{
			win();
		}
	}

	void change_head(SDL_Keycode key)
	{
		switch (key)
		{
		case SDLK_DOWN:
			if (head.symbol != up)
				head.set_head(down);
			break;
		case SDLK_UP:
			if (head.symbol != down)
				head.set_head(up);
			break;
		case SDLK_LEFT:
			if (head.symbol != right)
				head.set_head(left);
			break;
		case SDLK_RIGHT:
			if (head.symbol != left)
				head.set_head(right);
			break;

		}
	}
	void setssymbols(char** array)
	{
		int x, y;
		if (head.body == NULL)
		{
			x = head.point.x;
			y = head.point.y;
			array[x][y] = head.symbol;
		}
		else
		{
			Body* body = head.body;
			x = head.point.x;
			y = head.point.y;
			array[x][y] = head.symbol;
			while (body != NULL)
			{
				x = body->point.x;
				y = body->point.y;
				std::cout << "X: " << x << "Y: " << y << std::endl;
				array[x][y] = body->symbol;
				body = body->next;
			}
		}

	}

	void move(char** array, char** array2)
	{
		switch (head.symbol)
		{
		case up:
			moveto(array, array2, head.point.x - 1, head.point.y);
			break;
		case down:
			moveto(array, array2, head.point.x + 1, head.point.y);
			break;
		case left:
			moveto(array, array2, head.point.x, head.point.y - 1);
			break;
		case right:
			moveto(array, array2, head.point.x, head.point.y + 1);
			break;

		}

		//std::cout << array[head.point.x - 1][head.point.y - 1] << array[head.point.x -1 ][head.point.y] << array[head.point.x - 1][head.point.y + 1] << std::endl;
		//std::cout << array[head.point.x][head.point.y - 1] << array[head.point.x][head.point.y] << array[head.point.x][head.point.y+1] << std::endl;
		//std::cout << array[head.point.x + 1][head.point.y-1] << array[head.point.x+1][head.point.y] << array[head.point.x + 1][head.point.y + 1] << std::endl;
	}


	void setrandomfood(char** array, char** array2, int a, int b)
	{
		int x;
		int y, temp_y;

		x = Random(1, a - 2);
		y = Random(1, b - 2);
		bool end = false;
		bool again = false;
		temp_y = y;
		for (int i = x; i < a - 1; i++)
		{
			for (int j = temp_y; j < b - 1; j++)
			{
				if (array2[i][j] == ' ')
				{
					array[i][j] = '*';
					food.x = i;
					food.y = j;
					end = true;
					break;
				}
				temp_y = 1;

			}
			if (end)
				break;
			if (i == a - 2)
			{
				if (again)
				{
					//WINGAME;
					break;
				}
				a = x + 1;
				b = y + 1;
				i = 1;
				again = true;
			}
		}
	}

	void setfood(char** array)
	{
		array[food.x][food.y] = '*';
	}

	Snake(int w, int h)
	{
		width = w;
		height = h;
		setstartposition();
	}

	Snake()
	{
		width = 11;
		height = 11;
		setstartposition();
	}

	void changewh(int w, int h)
	{
		width = w;
		height = h;
		setstartposition();
	}
};



