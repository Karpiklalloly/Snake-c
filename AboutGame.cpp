// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "AboutGame.h"

void AboutGame::CustomLogic()
{
	ClickOnButton();
	
}

void AboutGame::Render()
{
	SDL_RenderCopy(renderer, wally, NULL, &forWall);//закидываем текстуру в рендер
	SDL_SetRenderDrawColor(AboutGame::renderer, 184, 134, 11, 255);
	SDL_RenderFillRect(AboutGame::renderer, &(AboutGame::buttonsRect[0]));
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawLine(renderer, buttonsRect[0].x, buttonsRect[0].y, buttonsRect[0].x, buttonsRect[0].y + buttonsRect[0].h); //лево
	SDL_RenderDrawLine(renderer, buttonsRect[0].x, buttonsRect[0].y + buttonsRect[0].h, buttonsRect[0].x + buttonsRect[0].w, buttonsRect[0].y + buttonsRect[0].h); //низ
	SDL_RenderDrawLine(renderer, buttonsRect[0].x + buttonsRect[0].w, buttonsRect[0].y + buttonsRect[0].h, buttonsRect[0].x + buttonsRect[0].w, buttonsRect[0].y); //право
	SDL_RenderDrawLine(renderer, buttonsRect[0].x + buttonsRect[0].w, buttonsRect[0].y, buttonsRect[0].x, buttonsRect[0].y); //верх
	SDL_SetRenderDrawColor(renderer, 0, 0, 51, 255);
	SDL_RenderFillRect(AboutGame::renderer, &back);
	DrawingText();
}
AboutGame::AboutGame(const char* name, int w, int h): Window(name,w,h)
{
	forWall.x = 0;
	forWall.y = 0;
	forWall.w = w;
	forWall.h = h;//задаем размеры заднего фона
	SDL_Surface* wall = IMG_Load("zmeya-v-lentax-izobrazhenie-s-pitom.jpg");//подгружаем картинку
	wally = SDL_CreateTextureFromSurface(renderer, wall);//создаем текстуру
	SDL_FreeSurface(wall);

	countOfButtons = 1;
	buttonsRect = new SDL_Rect[countOfButtons];
	buttonsRect[0].w = 180;
	buttonsRect[0].h = 50;
	buttonsRect[0].x = 5;
	buttonsRect[0].y = 5;

	countOfAnotherText = 8;
	text = new Text * [countOfButtons + countOfAnotherText];
	text[0] = new Text((UINT16*)L"Выйти в Меню");
	text[0]->rect.x = buttonsRect[0].x + 5;
	text[0]->rect.y = buttonsRect[0].y + 5;
	text[0]->rect.w = buttonsRect[0].w - 10;
	text[0]->rect.h = buttonsRect[0].h - 5;
	text[0]->surface = TTF_RenderUNICODE_Blended(font, text[0]->text, text[0]->color);
	text[0]->texture = SDL_CreateTextureFromSurface(renderer, text[0]->surface);

	int sizeOfFont = 35;
	int maxWidth = 0;
	SDL_Color color;
	color.a = 255;
	color.r=184;
	color.g=134;
	color.b=11;
	text[1] = new Text((UINT16*)L"Автор:");


	text[2] = new Text((UINT16*)L"Студент группы И904Б");
	text[3] = new Text((UINT16*)L"Газтдинов Рамиль");
	text[4] = new Text((UINT16*)L"Задача игры:");
	text[5] = new Text((UINT16*)L"заполнить все поле телом змейки");
	text[6] = new Text((UINT16*)L"Управление:");
	text[7] = new Text((UINT16*)L"клавишами на клавиатуре");
	text[8] = new Text((UINT16*)L"в виде стрелок");

	text[1]->rect.y = 5;

	for (int i = countOfButtons + 1; i < countOfAnotherText + countOfButtons; i++)
	{
		text[i]->rect.y = text[i - 1]->rect.y + 60;
	}

	for (int i = countOfButtons; i < countOfAnotherText + countOfButtons; i++)
	{
		std::cout << i << std::endl;
		text[i]->color = color;
		text[i]->rect.x = 300;
		text[i]->rect.w = LenghtOf(text[i]->text) * (sizeOfFont - 5);
		maxWidth < text[i]->rect.w ? maxWidth = text[i]->rect.w : maxWidth;
		text[i]->rect.h = sizeOfFont;
		text[i]->surface = TTF_RenderUNICODE_Blended(font, text[i]->text, text[i]->color);
		text[i]->texture = SDL_CreateTextureFromSurface(renderer, text[i]->surface);
	}
	back.x = text[countOfButtons]->rect.x - 2;
	back.y = text[countOfButtons]->rect.y - 2;
	back.w = maxWidth + 4;
	back.h = 60 * (countOfAnotherText);
	
}
void AboutGame::DrawingText()
{
	int i;
	for (i = 0;i < countOfButtons + countOfAnotherText;i++)
	{
		SDL_RenderCopy(renderer, text[i]->texture, NULL, &text[i]->rect);

		//std::cout << text->texture << "  " << text->rect.x << " " << text->rect.y << std::endl;
	}
}

void AboutGame::DoAction(int index)	
{
	std::cout << index << std::endl;
	(functions[index])();
}