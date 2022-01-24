#include "Game.h"


Game::Game(const char* Name, int w, int h) : Window::Window(Name, w, h)
{
	forWall.x = 0;
	forWall.y = 0;
	forWall.w = w;
	forWall.h = h;//задаем размеры заднего фона
	SDL_Surface* wall = IMG_Load("zmeya-v-lentax-izobrazhenie-s-pitom.jpg");//подгружаем картинку
	wally = SDL_CreateTextureFromSurface(renderer, wall);//создаем текстуру
	SDL_FreeSurface(wall);
	
	field = new char* [controlfield1];
	int i;
	for (i = 0;i < controlfield1;i++)
	{
		field[i] = new char[controlfield2+1];
	}
}

void Game::DrawingText()
{
	for (int i = 0;i < countOfButtons;i++)
	{
		SDL_RenderCopy(renderer, text[i]->texture, NULL, &text[i]->rect);

		//std::cout << text->texture << "  " << text->rect.x << " " << text->rect.y << std::endl;
	}
}
void Game::Render()
{
	SDL_RenderCopy(renderer, wally, NULL, &forWall);//закидываем текстуру в рендер
	SDL_SetRenderDrawColor(Game::renderer, 184, 134, 11, 255);
	DrawingText();
	DrawSnake();
}
void Game::DoAction(int index)
{
	std::cout << index << std::endl;
	(functions[index])();
}

void Game::CustomLogic()
{
	int i;
	int j;

	SDL_Keycode view = SDLK_0;
	char** tempArray = new char* [controlfield1];
	for (int i = 0; i < controlfield1; i++)
	{
		tempArray[i] = new char[controlfield2 + 1];
	}
	setborders();
	fillarray();
	copytoarray(tempArray);
	snake.setstartposition();
	snake.setssymbols(field);
	snake.setrandomfood(field, tempArray, controlfield1, controlfield2);
	extern int max_score;
	max_score = 5;//controlfield1 * controlfield2 - 1;
	extern int score;
	score = 0;
	std::cout << "hihihaha" << std::endl;
	snake.changewh(controlfield1, controlfield2);
	snake.state = snake.NONE;
	

	while (snake.state == snake.NONE)
	{
		ClickOnButton();
		SDL_PollEvent(&event);
		if (event.type == SDL_KEYDOWN)
		{
			//std::cout << "Input" << std::endl;
			if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT)
			{
				view = event.key.keysym.sym;
			}

			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				snake.state = snake.LOSE;
			}
		}
		//std::cout << "!!!!!!!!!!!!!!!!" << std::endl;
		if (TimeLeft(0.3))//0.2
		{
			continue;
		}
		copytoarray(tempArray);
		setborders();
		fillarray();
		

		snake.change_head(view);
		snake.setfood(field);
		snake.move(field, tempArray);
		
		if (snake.state == snake.LOSE)
		{
			SDL_Color color;
			color.a = 255;
			color.r = 255;
			color.g = 0;
			color.b = 0;
			Text** text = new Text * [3];
			int sizeOfFont = 20;
			int maxWidth = 0;
			text[0] = new Text((UINT16*)L"Вы ПРОИГРАЛИ(((");
			text[1] = new Text((UINT16*)L"Играть заново, нажмите Enter");
			text[2] = new Text((UINT16*)L"Выйти, нажмите Escape");

			text[0]->rect.y = 40;
			for (int i = 1; i < 3; i++)
			{
				text[i]->rect.y = text[i - 1]->rect.y + 60;
			}

			for (int i = 0; i < 3; i++)
			{
				std::cout << i << std::endl;
				text[i]->color = color;
				text[i]->rect.x = 850;
				text[i]->rect.w = LenghtOf(text[i]->text) * (sizeOfFont - 5);
				maxWidth < text[i]->rect.w ? maxWidth = text[i]->rect.w : maxWidth;
				text[i]->rect.h = sizeOfFont;
				text[i]->surface = TTF_RenderUNICODE_Blended(font, text[i]->text, text[i]->color);
				text[i]->texture = SDL_CreateTextureFromSurface(renderer, text[i]->surface);
			}
			Render();
			int i;
			for (i = 0;i < 3;i++)
			{
				SDL_RenderCopy(renderer, text[i]->texture, NULL, &text[i]->rect);
			}
			SDL_RenderPresent(renderer);
			while (true)
			{
				ClickOnButton();
				SDL_PollEvent(&event);
				if (event.type == SDL_KEYDOWN)
				{
					if (event.key.keysym.sym == SDLK_ESCAPE)
					{
						snake.setstartposition();
						break;
					}
					if (event.key.keysym.sym == SDLK_RETURN)
					{
						std::cout << "ENTER" << std::endl;
					
						snake.setstartposition();
						snake.state = snake.NONE;
						break;
					}
				}
			}
		}
		snake.setssymbols(field);
		SDL_RenderClear(renderer);
		Render();
		SDL_RenderPresent(renderer);

		system("cls");
		for (i = 0;i < controlfield1;i++)
		{
			for (j = 0;j < controlfield2+1;j++)
			{
				std::cout << field[i][j];
			}
		}
		std::cout << score << "/" << max_score << std::endl;
		snake.checkwin();
		if (snake.state == snake.WIN)
		{
			SDL_Color color;
			color.a = 255;
			color.r = 255;
			color.g = 0;
			color.b = 0;
			Text** text = new Text * [3];
			int sizeOfFont = 20;
			int maxWidth = 0;
			text[0] = new Text((UINT16*)L"Вы ВЫИГРАЛИ!!!");
			text[1] = new Text((UINT16*)L"Играть заново, нажмите Enter");
			text[2] = new Text((UINT16*)L"Выйти, нажмите Escape");

			text[0]->rect.y = 40;
			for (int i = 1; i < 3; i++)
			{
				text[i]->rect.y = text[i - 1]->rect.y + 60;
			}

			for (int i = 0; i < 3; i++)
			{
				std::cout << i << std::endl;
				text[i]->color = color;
				text[i]->rect.x = 850;
				text[i]->rect.w = LenghtOf(text[i]->text) * (sizeOfFont - 5);
				maxWidth < text[i]->rect.w ? maxWidth = text[i]->rect.w : maxWidth;
				text[i]->rect.h = sizeOfFont;
				text[i]->surface = TTF_RenderUNICODE_Blended(font, text[i]->text, text[i]->color);
				text[i]->texture = SDL_CreateTextureFromSurface(renderer, text[i]->surface);
			}
			Render();
			int i;
			for (i = 0;i < 3;i++)
			{
				SDL_RenderCopy(renderer, text[i]->texture, NULL, &text[i]->rect);
			}
			SDL_RenderPresent(renderer);
			while (true)
			{
				ClickOnButton();
				SDL_PollEvent(&event);
				if (event.type == SDL_KEYDOWN)
				{
					if (event.key.keysym.sym == SDLK_ESCAPE)
					{
						snake.setstartposition();
						break;
					}
					if (event.key.keysym.sym == SDLK_RETURN)
					{
						std::cout << "ENTER" << std::endl;

						snake.setstartposition();
						snake.state = snake.NONE;
						break;
					}
				}
			}
		}
		
	}
}

void Game::DrawSnake()
{
	SDL_Rect fieldRect;
	fieldRect.w = sizeOfSnake;
	fieldRect.h = sizeOfSnake;
	for (int i = 0; i < controlfield1; i++)
	{
		for (int j = 0; j < controlfield2; j++)
		{
			if (field[i][j] == '#')
			{
				SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
				fieldRect.x = x_offset + j * sizeOfSnake;
				fieldRect.y = y_offset + i * sizeOfSnake;
				SDL_RenderFillRect(Game::renderer, &fieldRect);
			}
			else if (field[i][j] == '@')
			{
				SDL_SetRenderDrawColor(Game::renderer, 194, 144, 21, 255);
				fieldRect.x = x_offset + j * sizeOfSnake;
				fieldRect.y = y_offset + i * sizeOfSnake;
				SDL_RenderFillRect(Game::renderer, &fieldRect);
			}
			else if (field[i][j] == '*')
			{
				SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
				fieldRect.x = x_offset + j * sizeOfSnake;
				fieldRect.y = y_offset + i * sizeOfSnake;
				SDL_RenderFillRect(Game::renderer, &fieldRect);
			}
			else if (field[i][j] == ' ')
			{
				SDL_SetRenderDrawColor(Game::renderer, 168, 168, 168, 255);
				fieldRect.x = x_offset + j * sizeOfSnake;
				fieldRect.y = y_offset + i * sizeOfSnake;
				SDL_RenderFillRect(Game::renderer, &fieldRect);
			}
			else if (field[i][j] == '<' || field[i][j] == 'A' || field[i][j] == 'V' || field[i][j] == '>')
			{
				SDL_SetRenderDrawColor(Game::renderer, 139, 69, 19, 255);
				fieldRect.x = x_offset + j * sizeOfSnake;
				fieldRect.y = y_offset + i * sizeOfSnake;
				SDL_RenderFillRect(Game::renderer, &fieldRect);
			}
		}
	}
}
