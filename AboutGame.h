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

