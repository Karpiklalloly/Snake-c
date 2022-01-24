// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Window.h"
Window::Window()//������ �����������
{

}
Window::Window(const char* Name, int w, int h)
{
	window = SDL_CreateWindow(Name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_OPENGL);//�������� ����
	renderer = SDL_CreateRenderer(window, -1, 0);//�������� ������� ����

}
void Window::Update()
{
	SDL_RenderClear(renderer);//������� ������
	Render();//��������� ��, ��� ���������� ����������
	SDL_RenderPresent(renderer);//������������ ������
	CustomLogic();//��������� 
}
void Window::Render()
{
	SDL_RenderCopy(renderer, wally, NULL, &forWall);//���������� �������� � ������
}
Window::~Window()
{
	SDL_DestroyTexture(wally);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);//������� ������

}

void Window::SetButton(SDL_Rect** rect, int x, int y)
{
	SDL_Point point{};
	point.x = x;
	point.y = y;
	*rect = NULL;
	for (int i = 0; i < countOfButtons; i++)
	{
		if (SDL_PointInRect(&point, &buttonsRect[i]))
		{
			*rect = &buttonsRect[i];
		}

	}
}

void Window::ClickOnButton()
{
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			SetButton(&leftDowned, event.button.x, event.button.y);
		}
	}
	else if (event.type == SDL_MOUSEBUTTONUP)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			SetButton(&leftUpped, event.button.x, event.button.y);
			if (leftDowned != NULL && leftDowned == leftUpped)
			{
				//std::cout << "Clecked" << std::endl;
				int index = leftDowned - buttonsRect;
				DoAction(index);
				leftDowned = NULL;
				leftUpped = NULL;
			}
		}
	}
	event.type = SDL_FIRSTEVENT;
}
