#ifndef APP_APP_H_
#define APP_APP_H_

#include"Screen.h"
#include <stdint.h>
#include "SDL.h"
#include <vector>
#include <memory>
#include "Scene.h"
#include "InputController.h"

struct SDL_Window;

class App
{
public:
	static App& Singleton();
	bool Init(uint32_t width, uint32_t heigth, uint32_t mag);
	void Run();

	inline uint32_t Width() const { return mScreen.Width(); }
	inline uint32_t Heigth() const { return mScreen.Heigth(); }

	void PushScene(std::unique_ptr<Scene> scene);
	void PopScene();
	Scene* TopScene(); // current scene

	static const std::string& GetBasePath();

private:
	Screen mScreen;
	SDL_Window * mnoptrWindow;
	std::vector<std::unique_ptr<Scene>> mSceneStack;
	InputController mInputController;
};


#endif //APP_APP_H_
