#ifndef GAMES_BREAKOUT_H_
#define GAMES_BREAKOUT_H_

#include "Game.h"
#include "Paddle.h"
#include "Ball.h"
#include "LevelBoundary.h"
#include "BreakOutGameLevel.h"
#include "vector"

namespace BreakOutGameState
{
	enum BreakOutGameState
	{
		IN_PLAY = 0,
		IN_SERVE,
		IN_GAME_OVER
	};
}


class BreakOut:public Game
{
public:

	virtual void Init(GameController& controller) override;
	virtual void Update(uint32_t dt) override;
	virtual void Draw(Screen& screen) override;
	virtual const std::string& GetName() const override;


private:

	const int NUM_LIVES = 3;
	void ResetGame(size_t toLevel = 0);
	const float INITIAL_BALL_SPEED = 100;
	const Vect2D INITIAL_BALL_VEL = Vect2D(50, 100);

	
	int mLives;
	float mYCutoff;

	void SetToServeState();
	bool IsBallPassedCutoffY() const; // is ball under the paddle and if yes reduce life by one
	void ReduceLifeByOne();
	bool IsGameOver() const { return mLives < 0; }

	BreakoutGameLevel& GetCurrentLevel() { return mLevels[mCurrentLevel]; }
	Paddle mPaddle;
	Ball mBall;
	LevelBoundary mLevelBoundary;
	std::vector<BreakoutGameLevel> mLevels;
	size_t mCurrentLevel;
	BreakOutGameState::BreakOutGameState mGameState;
	
};


#endif // !GAMES_BREAKOUT_H_

