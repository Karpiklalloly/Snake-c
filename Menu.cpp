#include "Menu.h"

void Menu::Render()
{
	SDL_RenderCopy(renderer, wally, NULL, &forWall);//закидываем текстуру в рендер
	SDL_SetRenderDrawColor(Menu::renderer, 184, 134, 11, 255);
	SDL_RenderFillRect(Menu::renderer, &(Menu::buttonsRect[0]));
	SDL_RenderFillRect(Menu::renderer, &(Menu::buttonsRect[1]));
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawLine(renderer, buttonsRect[0].x, buttonsRect[0].y, buttonsRect[0].x, buttonsRect[0].y + buttonsRect[0].h); //лево
	SDL_RenderDrawLine(renderer, buttonsRect[0].x, buttonsRect[0].y + buttonsRect[0].h, buttonsRect[0].x + buttonsRect[0].w, buttonsRect[0].y + buttonsRect[0].h); //низ
	SDL_RenderDrawLine(renderer, buttonsRect[0].x + buttonsRect[0].w, buttonsRect[0].y + buttonsRect[0].h, buttonsRect[0].x + buttonsRect[0].w, buttonsRect[0].y); //право
	SDL_RenderDrawLine(renderer, buttonsRect[0].x + buttonsRect[0].w, buttonsRect[0].y, buttonsRect[0].x, buttonsRect[0].y); //верх
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawLine(renderer, buttonsRect[1].x, buttonsRect[1].y, buttonsRect[1].x, buttonsRect[1].y + buttonsRect[1].h); //лево
	SDL_RenderDrawLine(renderer, buttonsRect[1].x, buttonsRect[1].y + buttonsRect[1].h, buttonsRect[1].x + buttonsRect[1].w, buttonsRect[1].y + buttonsRect[1].h); //низ
	SDL_RenderDrawLine(renderer, buttonsRect[1].x + buttonsRect[1].w, buttonsRect[1].y + buttonsRect[1].h, buttonsRect[1].x + buttonsRect[1].w, buttonsRect[1].y); //право
	SDL_RenderDrawLine(renderer, buttonsRect[1].x + buttonsRect[1].w, buttonsRect[1].y, buttonsRect[1].x, buttonsRect[1].y); //верх
	DrawingText();


}

Menu::Menu(const char* name, int w, int h) : Window(name, w, h)
{
	forWall.x = 0;
	forWall.y = 0;
	forWall.w = w;
	forWall.h = h;//задаем размеры заднего фона
	SDL_Surface* wall = IMG_Load("zmeya-v-lentax-izobrazhenie-s-pitom.jpg");//подгружаем картинку
	wally = SDL_CreateTextureFromSurface(renderer, wall);//создаем текстуру
	SDL_FreeSurface(wall);

	countOfButtons = 2;
	buttonsRect = new SDL_Rect[countOfButtons];
	buttonsRect[0].w = 150;
	buttonsRect[0].h = 100;
	buttonsRect[0].x = w / 2 - buttonsRect[0].w - buttonsRect[0].w / 2;
	buttonsRect[0].y = h / 2 - buttonsRect[0].h / 2;
	buttonsRect[1].w = 150;
	buttonsRect[1].h = 100;
	buttonsRect[1].x = w / 2 + buttonsRect[0].w - buttonsRect[0].w / 2;
	buttonsRect[1].y = h / 2 - buttonsRect[0].h / 2;

	text = new Text * [countOfButtons];
	text[0] = new Text((UINT16*)L"Играть");
	//CatArray(text[0].text, (UINT16*)L"Меню");
	text[0]->rect.x = buttonsRect[0].x + 5;
	text[0]->rect.y = buttonsRect[0].y + 40;
	text[0]->rect.w = buttonsRect[0].w - 10;
	text[0]->rect.h = buttonsRect[0].h - 76;
	text[0]->surface = TTF_RenderUNICODE_Blended(font, text[0]->text, text[0]->color);
	text[0]->texture = SDL_CreateTextureFromSurface(renderer, text[0]->surface);


	if (text[0]->surface == NULL || text[0]->texture == NULL)
	{
		perror(TTF_GetError());
	}

	text[1] = new Text((UINT16*)L"Об игре");
	text[1]->rect.x = buttonsRect[1].x + 5;
	text[1]->rect.y = buttonsRect[1].y + 40;
	text[1]->rect.w = buttonsRect[1].w - 10;
	text[1]->rect.h = buttonsRect[1].h - 76;
	text[1]->surface = TTF_RenderUNICODE_Blended(font, text[1]->text, text[1]->color);
	text[1]->texture = SDL_CreateTextureFromSurface(renderer, text[1]->surface);


	if (text[1]->surface == NULL || text[1]->texture == NULL)
	{
		perror(TTF_GetError());
	}


}

void Menu::DrawingText()
{
	for (int i = 0;i < countOfButtons;i++)
	{
		SDL_RenderCopy(renderer, text[i]->texture, NULL, &text[i]->rect);

		//std::cout << text->texture << "  " << text->rect.x << " " << text->rect.y << std::endl;
	}
}

void Menu::DoAction(int index)
{
	(functions[index])();
}


void Menu::CustomLogic()
{
	ClickOnButton();
}