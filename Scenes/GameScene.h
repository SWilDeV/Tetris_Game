#ifndef SCENE_GAMESCENE_H_
#define SCENE_GAMESCENE_H_
#include "Scene.h"
#include "Game.h"
#include <memory>

class GameScene : public Scene
{
public:
	virtual~GameScene() {}
	GameScene(std::unique_ptr<Game> optrGame);
	virtual void Init() override;
	virtual void Update(uint32_t dt) override;
	virtual void Draw(Screen& screen) override;

	virtual const std::string& GetSceneName() const override;


private:
	std::unique_ptr<Game> mGame;
};

#endif // !SCENE_GAMESCENE_H_

