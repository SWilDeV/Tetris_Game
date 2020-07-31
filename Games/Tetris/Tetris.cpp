#include "Tetris.h"
#include <iostream>
#include "Gamecontroller.h"
#include "Vec2D.h"
#include "BoundaryEdge.h"
#include "Circle.h"


void Tetris::Init(GameController& controller)
{
	controller.ClearAll();
	mYCutoff = App::Singleton().Heigth() - 1.1 * Tetronimos::BLOCK_HEIGHT;
	ResetGame();

	//move block left action key
	ButtonAction leftKeyAction;
	leftKeyAction.key = GameController::LeftKey();
	leftKeyAction.action = [this](uint32_t dt, InputState state)
	{
		if (mGameState == TetrisGameState::IN_PLAY )
		{
			if (GameController::IsPressed(state))
			{
				mTetronimosVector[TTID].SetMovementDirection(tetronimosSpace::TetronimosDirection::LEFT);
			}
			else
			{
				mTetronimosVector[TTID].UnsetMovementDirection(tetronimosSpace::TetronimosDirection::LEFT);
			}
		}
	};
	controller.AddInputActionForKey(leftKeyAction);

	// move paddle right action key
	ButtonAction rightKeyAction;
	rightKeyAction.key = GameController::RightKey();
	rightKeyAction.action = [this](uint32_t dt, InputState state)
	{
		if (mGameState == TetrisGameState::IN_PLAY)
		{
			if (GameController::IsPressed(state))
			{
				mTetronimosVector[TTID].SetMovementDirection(tetronimosSpace::TetronimosDirection::RIGHT);
			}
			else
			{
				mTetronimosVector[TTID].UnsetMovementDirection(tetronimosSpace::TetronimosDirection::RIGHT);
			}
		}

	};
	controller.AddInputActionForKey(rightKeyAction);
	//mTetronimos.SetVelocity(-INITIAL_BRICK_VEL); // useless for now

}
void Tetris::Update(uint32_t dt)
{
	if (mGameState == TetrisGameState::IN_PLAY)
	{
		mTetronimosVector[TTID].Update(dt);
	}
	else if (mGameState == TetrisGameState::IN_POSITION)
	{
		TTID += 1;
		AddNewTetronimos();
		SetToPlayState();
	}
	if (IsBallPassedCutoffY())
	{
		SetToPositionState();
	}
}
void Tetris::Draw(Screen& screen) 
{
	for (int i = 0;i <= TTID; i++)
	{
		mTetronimosVector[i].Draw(screen);
	}
}


const std::string& Tetris::GetName() const
{
	static std::string name = "Tetris!";
	return name;
}

void Tetris::ResetGame(size_t toLevel)
{
	CreateTetronimos();
	AddNewTetronimos();
}

void Tetris::SetToPlayState()
{
	mGameState = TetrisGameState::IN_PLAY;
}

void Tetris::SetToPositionState()
{
	mGameState = TetrisGameState::IN_POSITION;

}

void Tetris::AddNewTetronimos()
{
	mTetronimosVector[TTID].MoveTo(Vect2D(100, 60));
	AARectangle blockRect = { Vect2D(App::Singleton().Width() / 2 - (Tetronimos::BLOCK_WIDTH / 2),  Tetronimos::BLOCK_HEIGHT), Tetronimos::BLOCK_WIDTH, Tetronimos::BLOCK_HEIGHT };
	mTetronimosVector[TTID].Init(blockRect, levelBoundary);
}

void Tetris::CreateTetronimos()
{
	for (int i = 0; i < 10; i++)
	{
		Tetronimos mTetronimos;
		mTetronimosVector.push_back(mTetronimos);
	}
}

bool Tetris::IsBallPassedCutoffY() const
{
	return mTetronimosVector[TTID].GetAARectangle().GetTopLeftPoint().GetY() > mYCutoff;
}

