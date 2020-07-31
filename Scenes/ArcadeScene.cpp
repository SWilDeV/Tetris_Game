#include "ArcadeScene.h"
#include "Screen.h"
#include "App.h"
#include "SDL.h"
#include "Triangle.h"
#include "LINE2D.h"
#include "AARectangle.h"
#include "Circle.h"
#include "Color.h"
#include "Vec2D.h"
#include "Utils.h"
#include "Star.h"
#include <iostream>
#include "Gamecontroller.h"

ArcadeScene::ArcadeScene()
{

}
void ArcadeScene::Init()
{
	ButtonAction action;
	action.key = GameController::ActionKey();
	action.action = [](uint32_t dt, InputState state)
	{
		if (GameController::IsPressed(state))
		{
			std::cout << "Action button was pressed!" << endl;
		}
	};
	mGameController.AddInputActionForKey(action);
	MouseButtonAction mouseAction;
	mouseAction.mouseButton = GameController::LeftMouseButton();
	mouseAction.mouseInputAction = [](InputState state, const MousePosition& position)
	{
		if (GameController::IsPressed(state))
		{
			std::cout << "Left Mouse button pressed!" << endl;
		}
	};
	mGameController.AddMouseButtonAction(mouseAction);

	mGameController.SetMouseMovedAction([](const MousePosition& MousePosition)
		{
			std::cout << "Mouse position x: " << MousePosition.xPos << ", y: " << MousePosition.Ypos << std::endl;
	});
}
void ArcadeScene::Update(uint32_t dt)
{

}
void ArcadeScene::Draw(Screen& theScreen)
{
	Triangle triangle = { Vect2D(60, 10), Vect2D(10, 110), Vect2D(110, 110) };
	theScreen.Draw(triangle, Color::Red(), true, Color::Red());

	AARectangle rect = { Vect2D(theScreen.Width() / 2 - 25, theScreen.Heigth() / 2 - 25), 50,50 };
	theScreen.Draw(rect, Color(0, 0, 255, 150), true, Color(0, 0, 255, 150));

	Circle circle = { Vect2D(300,125), 50.0f };
	theScreen.Draw(circle, Color(0, 255, 0, 150), true, Color(0, 255, 0, 150));
}
const std::string& ArcadeScene::GetSceneName() const
{
	static std::string sceneName = "Arcade Scene";
	return sceneName;
}

std::unique_ptr<Scene> ArcadeScene::GetScene(eGame game)
{
	switch (game)
	{
		case TETRIS: 
		{

		}
		break;

		case BREAK_OUT:
		{

		}
		break;

		case ASTEROIDS:
		{

		}
		break;

		case PACMAN:
		{

		}
		break;

		default: 
		{

		}
		break;
	}
	return nullptr;
}