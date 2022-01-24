// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#ifndef IO
#define IO
#include <iostream> 
#endif
#ifndef FUNCTIONAL
#define FUNCTIONAL
#include <functional>
#endif
#ifndef VECTOR
#define VECTOR
#include <vector>
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
#ifndef WINDOW
#define WINDOW
#include "Window.h"
#endif
#ifndef SNAKE
#define SNAKE
#include "Snake.h"
#endif

Snake* snake;
#include "Menu.h"
#include "Game.h"
#include "AboutGame.h"

Window* window = NULL;
Menu* menu = NULL;
Game* game = NULL;
AboutGame* aboutGame = NULL;


static void BackToMenu()
{
    SDL_DestroyWindow(window->window);
    window = menu;
    SDL_ShowWindow(window->window);
    //snake.state = snake.LOSE;////////////////////
}

static void InitInfo()
{
    aboutGame = new AboutGame(u8"Информация", 1280, 720);
    SDL_HideWindow(menu->window);
    window = aboutGame;
    aboutGame->functions.push_back(std::bind(BackToMenu));
}

static void InitGame()
{
    game = new Game(u8"Змейка", 1280, 720);
    SDL_HideWindow(menu->window);
    window = game;
    game->functions.push_back(std::bind(BackToMenu));
}

void InfoAction()
{
    std::cout << "Action of Info" << std::endl;
    InitInfo();
}

void PlayAction()
{
    std::cout << "Action of Play" << std::endl;
    InitGame();
}

static bool Init()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    SDL_Init(SDL_INIT_VIDEO);
    //Подгружаем ПНГ картинки
    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        perror(IMG_GetError());
        return false;
    }
    //ЖПГ
    if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG)
    {
        perror(IMG_GetError());

        return false;
    }
    //ТТФ(Шрифт)
    if (!TTF_WasInit() && TTF_Init() == -1)
    {
        perror(TTF_GetError());

        return false;
    }
    //Чтобы в конце программы все отключалось
    atexit(TTF_Quit);
    atexit(IMG_Quit);
    atexit(SDL_Quit);
    //Добавление фукнций в массивы

    snake = NULL;
    return true;
}

static void InitMenu()
{
    menu = new Menu(u8"Меню", 1000, 600);//Создаем окно
    menu->functions.push_back(std::bind(PlayAction));
    menu->functions.push_back(std::bind(InfoAction));
    window = menu;
}



int main(int argc, char* argv[])
{
    srand(time(0));
    if (!Init())
    {
        SDL_Quit();
        return -1; // проверяем на корректность подгружение библиотек
    }
    snake = new Snake(1, 1);
    InitMenu();
    
    while (true)//главный цикл, в котором обрабатываются все действия
    {
        window->event.type = SDL_FIRSTEVENT;
        SDL_PollEvent(&window->event);//отлавливаем событие
        if (window->event.type == SDL_KEYDOWN)
        {
            if (window->event.key.keysym.sym == SDLK_ESCAPE)
            {
                break;
            }
        }
        if (window->event.type == SDL_QUIT)
            break;//закрытие окна
        window->Update();//обновление картинки в окне
        if (snake->state != snake->NONE)
        {
            snake->state = snake->NONE;
            SDL_DestroyWindow(game->window);
            window = menu;
            SDL_ShowWindow(menu->window);
        }

    }
    //delete window;
    //SDL_Quit();//отгружаем библиотеку SDL
    return 0;
}