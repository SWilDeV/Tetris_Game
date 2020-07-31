#include "BreakOut.h"
#include <iostream>
#include "Gamecontroller.h"
#include "App.h"
#include "Vec2D.h"
#include "BoundaryEdge.h"
#include "Circle.h"



void BreakOut::Init(GameController& controller)
{
	//init
	controller.ClearAll();
	ResetGame();

	//set action key
	ButtonAction serveAction;
	serveAction.key = GameController::ActionKey();
	serveAction.action = [this](uint32_t dt, InputState state)
	{
		if (mGameState == BreakOutGameState::IN_SERVE)
		{
			if (GameController::IsPressed(state))
			{
				mGameState = BreakOutGameState::IN_PLAY;
				if (mPaddle.IsMovingLeft())
				{
					mBall.SetVelocity(Vect2D(-INITIAL_BALL_SPEED, -INITIAL_BALL_SPEED));
				}
				else
				{
					mBall.SetVelocity(Vect2D(INITIAL_BALL_SPEED, -INITIAL_BALL_SPEED));
				}
			}
		}
		else if (mGameState == BreakOutGameState::IN_GAME_OVER)
		{
			if (GameController::IsPressed(state))
			{
				ResetGame();
			}
		}
	};
	//add Serve action key
	controller.AddInputActionForKey(serveAction);

	//move paddle left action key
	ButtonAction leftKeyAction;
	leftKeyAction.key = GameController::LeftKey();
	leftKeyAction.action = [this](uint32_t dt, InputState state)
	{
		if (mGameState == BreakOutGameState::IN_PLAY || mGameState == BreakOutGameState::IN_SERVE)
		{
			if (GameController::IsPressed(state))
			{
				mPaddle.SetMovementDirection(paddleSpace::PaddleDirection::LEFT);
			}
			else
			{
				mPaddle.UnsetMovementDirection(paddleSpace::PaddleDirection::LEFT);
			}
		}
	};
	controller.AddInputActionForKey(leftKeyAction);

	// move paddle right action key
	ButtonAction rightKeyAction;
	rightKeyAction.key = GameController::RightKey();
	rightKeyAction.action = [this](uint32_t dt, InputState state)
	{
		if (mGameState == BreakOutGameState::IN_PLAY || mGameState == BreakOutGameState::IN_SERVE)
		{
			if (GameController::IsPressed(state))
			{
				mPaddle.SetMovementDirection(paddleSpace::PaddleDirection::RIGHT);
			}
			else
			{
				mPaddle.UnsetMovementDirection(paddleSpace::PaddleDirection::RIGHT);
			}
		}
		
	};
	controller.AddInputActionForKey(rightKeyAction);
}


void BreakOut::Update(uint32_t dt)
{
	if (mGameState == BreakOutGameState::IN_SERVE)
	{
		mPaddle.Update(dt, mBall);
		SetToServeState();
	}
	else if (mGameState == BreakOutGameState::IN_PLAY)
	{
		mBall.Update(dt);
		mPaddle.Update(dt, mBall);
		BoundaryEdge edge;

		if (mPaddle.Bounce(mBall))
		{
			return;
		}

		if (mLevelBoundary.HasCollided(mBall, edge))
		{
			mBall.Bounce(edge);
			return;
		}
		GetCurrentLevel().Update(dt, mBall);
	}
	if (IsBallPassedCutoffY())
	{
		ReduceLifeByOne();
		if (!IsGameOver())
		{
			SetToServeState();
		}
		else
		{
			mGameState = BreakOutGameState::IN_GAME_OVER;
		}
	}
	else if (GetCurrentLevel().IsLevelComplete())
	{
		mCurrentLevel = (mCurrentLevel + 1) % mLevels.size();
		ResetGame(mCurrentLevel);
	}
	
}

void BreakOut::Draw(Screen & screen) 
{
	mBall.Draw(screen);
	mPaddle.Draw(screen);
	GetCurrentLevel().Draw(screen);
	screen.Draw(mLevelBoundary.GetAARectangle(), Color::White());

	//Draw life circles
	Circle lifeCircle = { Vect2D(7, App::Singleton().Heigth() - 10), 5 };


	// Draw the lives
	for (int i = 0; i < mLives;++i)
	{
		screen.Draw(lifeCircle, Color::Red(), true, Color::Red());
		lifeCircle.MoveBy(Vect2D(17, 0));
	}
}


const std::string& BreakOut::GetName() const
{
	static std::string name = "Break Out!";
	return name;
}

void BreakOut::ResetGame(size_t toLevel)
{
	mLevels = BreakoutGameLevel::LoadLevelsFromFile(App::GetBasePath() + "Assets/BreakoutLevels.txt");
	mYCutoff = App::Singleton().Heigth() - 2 * Paddle::PADDLE_HEIGHT;
	mLives = NUM_LIVES;
	mCurrentLevel = 0;
	
	AARectangle paddleRect = { Vect2D(App::Singleton().Width() / 2 - (Paddle::PADDLE_WIDTH/2), App::Singleton().Heigth() - (3 * Paddle::PADDLE_HEIGHT)), Paddle::PADDLE_WIDTH, Paddle::PADDLE_HEIGHT };
	AARectangle levelBoundary = { Vect2D::Zero, App::Singleton().Width(), App::Singleton().Heigth() };
	
	mLevelBoundary = { levelBoundary };

	mPaddle.Init(paddleRect, levelBoundary);
	mBall.MoveTo(Vect2D(App::Singleton().Width() / 2, App::Singleton().Heigth() *0.75f));

	SetToServeState();
}

void BreakOut::SetToServeState()
{
	mGameState = BreakOutGameState::IN_SERVE;
	mBall.Stop();

	mBall.MoveTo(Vect2D(mPaddle.GetAARectangle().GetCenterPoint().GetX(), mPaddle.GetAARectangle().GetTopLeftPoint().GetY() - mBall.GetRadius()-1));
}

bool BreakOut::IsBallPassedCutoffY() const
{
	return mBall.GetPosition().GetY() > mYCutoff;
}

void BreakOut::ReduceLifeByOne()
{
	if (mLives >= 0)
	{
		--mLives;
	}
}