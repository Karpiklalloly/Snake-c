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




//buttonsRect[0] - play, 1 - info
class Menu :
    public Window
{
    
    void DrawingText() override;
    void DoAction(int index) override;
    void CustomLogic() override;
protected:
    void Render() override;
public:
    Menu(const char* name, int w, int h);
};

