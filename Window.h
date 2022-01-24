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
extern void CatArray(UINT16* arr1, const UINT16* const arr2, const char* divider = "\0", bool debug = 0);
extern int LenghtOf(const UINT16* arr, const UINT16 symbol = '\0');

typedef std::_Binder<std::remove_cv<std::_Unforced>::type, void(&)()> FuncPtr;
#pragma once
class Window
{
public:
	SDL_Event event;//переменная события
protected:

	struct Text
	{
		UINT16 text[32];
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
	int countOfButtons = 0;
	SDL_Rect* buttonsRect;
	int countOfAnotherText = 0;
	Text** text;
public:
	SDL_Window* window;//переменна окна
	std::vector<FuncPtr> functions;
protected:
	SDL_Rect forWall;// размер картинки
	SDL_Texture* wally;//текстура в которой загружена картинка(задний фон)
	SDL_Renderer* renderer;//переменная рендера
	TTF_Font* font = TTF_OpenFont("appetite.ttf", 72);
	SDL_Rect* leftDowned;
	SDL_Rect* leftUpped;
	Window(); //конструктор(находится в привате, чтоб не могли вызвать)
	void SetButton(SDL_Rect** rect, int x, int y);
	virtual void DrawingText() = 0;
	virtual void Render() = 0; //метод , в который закидывается все что нужно отрисовать
	virtual void DoAction(int index) = 0;
	virtual void CustomLogic() = 0;
	void ClickOnButton();


public:
	void Update();// метод обновления картинки
	Window(const char* Name, int w, int h);// конструктор с параметрами окна
	~Window(); // деструктор 
};

