#include "App.h"
#include "SDL.h"
#include "Triangle.h"
#include "LINE2D.h"
#include "Vec2D.h"
#include "AARectangle.h"
#include "Utils.h"
#include "Timer.h"
#include "Star.h"
#include <iostream>
#include "ArcadeScene.h"
#include <assert.h>
#include "GameScene.h"
#include "BreakOut.h"
#include "Tetris.h"


App& App::Singleton()
{
	static App theApp;
	return theApp;
}


//CHOSE WHICH GAME TO PLAY
bool App::Init(uint32_t width, uint32_t heigth, uint32_t mag)
{
	//Init a Window
	mnoptrWindow = mScreen.Init(width, heigth, mag);

	//ArcadeScene:
	/*std::unique_ptr<ArcadeScene> arcadeScene = std::make_unique<ArcadeScene>();
	PushScene(std::move(arcadeScene));*/

	//BreakOut
	/*{
		std::unique_ptr<BreakOut> breakoutGame = std::make_unique<BreakOut>();
		std::unique_ptr<GameScene> breakoutScene = std::make_unique<GameScene>(std::move(breakoutGame));
		PushScene(std::move(breakoutScene));
	}*/
	//Tetris
	{
		std::unique_ptr<Tetris> tetrisGame = std::make_unique<Tetris>();
		std::unique_ptr<GameScene> tetrisScene = std::make_unique<GameScene>(std::move(tetrisGame));
		PushScene(std::move(tetrisScene));
	}
	return mnoptrWindow != nullptr;
}


void App::Run()
{
	if (mnoptrWindow)
	{
		bool running = true;

		uint32_t lastTick = SDL_GetTicks();
		uint32_t currentTick = lastTick;

		uint32_t dt = 10; //Default delta time
		//uint32_t dt = 100; //Tetris
		uint32_t accumulator = 0;

		mInputController.Init([&running](uint32_t dt, InputState state)
			{
				running = false;
			});

		while (running)
		{
			currentTick = SDL_GetTicks();
			uint32_t frametime = currentTick - lastTick;
			if (frametime > 300)
			{
				frametime = 300;
			}
			lastTick = currentTick;
			accumulator += frametime;
			
			//Input
			mInputController.Update(dt);

			Scene* topScene = App::TopScene();
			assert(topScene && "Why don't we have a scene");
			if (topScene)
			{
				while (accumulator >= dt)
				{
					//update current scene by dt
					topScene->Update(dt);
					accumulator -= dt;
				}
				//Render
				topScene->Draw(mScreen);
			}
			mScreen.SwapScreens();
		}
	}
}

void App::PushScene(std::unique_ptr<Scene> scene)
{
	assert(scene && "don't push nullptr");
	if (scene)
	{
		scene->Init();
		mInputController.SetGameController(scene->GetGameController());
		mSceneStack.emplace_back(std::move(scene));
		SDL_SetWindowTitle(mnoptrWindow, TopScene()->GetSceneName().c_str());
	}

}
void App::PopScene()
{
	if (mSceneStack.size() > 1)
	{
		mSceneStack.pop_back();

	}
	if (TopScene())
	{
		mInputController.SetGameController(TopScene()->GetGameController());
		SDL_SetWindowTitle(mnoptrWindow, TopScene()->GetSceneName().c_str());
	}
	
}

Scene* App::TopScene()	// current scene
{
	if (mSceneStack.empty())
	{
		return nullptr;
	}
	return mSceneStack.back().get();
}

const std::string& App::GetBasePath()
{
	static std::string basePath = SDL_GetBasePath();

	return basePath;
}








vector<Star> CreateStars()
{
	vector<Star> starVec;
	for (int i = 0; i < 5; i++)
	{
		Star star;
		starVec.push_back(star);
	}
	return starVec;
}

void DrawChessBoard(Screen& theScreen)
{
	int x = 0;
	int y = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			AARectangle rect = { Vect2D(x,y), 50,50 };
			theScreen.Draw(rect, Color::Red(), true, Color::White());
			x += 50;
			AARectangle rect2 = { Vect2D(x,y), 50,50 };
			theScreen.Draw(rect2, Color::Red(), true, Color::Black());
			x += 50;
		}

		x = 0;
		y += 50;

		for (int j = 0; j < 4; j++)
		{
			AARectangle rect = { Vect2D(x,y), 50,50 };
			theScreen.Draw(rect, Color::Red(), true, Color::Black());
			x += 50;
			AARectangle rect2 = { Vect2D(x,y), 50,50 };
			theScreen.Draw(rect2, Color::Red(), true, Color::White());
			x += 50;
		}
		x = 0;
		y += 50;
	}
}
