// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#pragma once
#include "Window.h"
class AboutGame :
    public Window
{
    SDL_Rect back;
    void CustomLogic() override;
    void Render() override;
    void DrawingText() override;
    void DoAction(int index) override;
public:
    AboutGame(const char* name, int w, int h);
};

