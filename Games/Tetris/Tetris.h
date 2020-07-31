#ifndef GAMES_TETRIS_H_
#define GAMES_TETRIS_H_

#include "Game.h"
#include "Vec2D.h"
#include "Ball.h"
#include "LevelBoundary.h"
#include "vector"
#include "App.h"
#include "Tetronimos.h"

namespace TetrisGameState
{
	enum TetrisGameState
	{
		IN_PLAY = 0,
		IN_POSITION,
		IN_GAME_OVER
	};
}

class Tetris : public Game
{
public:	
	virtual void Init(GameController& controller) override;
	virtual void Update(uint32_t dt) override;
	virtual void Draw(Screen& screen) override;
	virtual const std::string& GetName() const override;
	void CreateTetronimos();
	AARectangle levelBoundary = { Vect2D::Zero, App::Singleton().Width(), App::Singleton().Heigth() };
	

private:
	const int NUM_LIVES = 3;
	int TTID = 0;
	float mYCutoff;

	void ResetGame(size_t toLevel = 0);
	void AddNewTetronimos();
	void SetToPlayState();
	void SetToPositionState();
	bool IsBallPassedCutoffY() const;
	const float INITIAL_BRICK_SPEED = 100;
	const Vect2D INITIAL_BRICK_VEL = Vect2D(0, -100);

	int mLives;
	TetrisGameState::TetrisGameState mGameState;
	std::vector<Tetronimos> mTetronimosVector;
	bool IsGameOver() const { return mLives < 0; }
};
/*
for now the block stops because there's a lineCuteOff.
The better way would be to setup a level boundary, and use levelboundary.hcpp to check if a bottom collision happened-> if yes set the tetronimo in Position.

I should design several shapes for the tetronimos, and associate with each one of them an ID, that will be picked randomely at each generation


TETRIS

Level : H = 20 blocks   L= 10 blocks

tetrominos:

I:  __ __ __ __
   |__|__|__|__|  

J:  __ __ __ 
   |__|__|__|
		 |__|

L:  __ __ __ 
   |__|__|__|
   |__|

O:  __ __  
   |__|__|
   |__|__|

S:     __ __
	__|__|__|
   |__|__|
		 
T:  __ __ __
   |__|__|__|
      |__|

Z:
    __ __ 
   |__|__|__
      |__|__|

A random tetrominos are spawned  at the top of the playfield in their initial positions (see above) and subsequently can be moved by the player.

***** MOVEMENT *******

The player should be able to move the tetrominos around the play area (explained later) to either side (left or right) by one block or down by one block. The player should also be able to "drop" the current tetromino which will instantly move the piece down to the bottom floor or on top of the nearest block below it. There should be a short delay before locking the block in place in which the player can still move the piece. Once the piece is locked, the player should not be able to move it any longer.

Each tetromino moves downward slowly by itself regardless of any player involvement. As the game goes on, there should be less and less time between the active tetromino being moved down automatically.


***** ROTATION *******

These shapes should be able to be rotated around one of the blocks that the shape is composed of. They should each have 4 different rotations (except the O tetromino which doesn't rotate). Each rotation is 90 degrees counter clock-wise. The player should not be able to rotate the tetromino if there isn't room to rotate (ie. something is blocking it - either another block or the side walls).


***** PLAYFIELD *******

The playfield is a block grid that contains all of the tetromino pieces. Your playfield should be at least 10 blocks in width and 20 blocks in height.

Any time a full row (or rows) is made, the rows are cleared and any non completed rows are brought down to be flush with the rest of the blocks. Completed rows (depending on how many rows were completed that turn) give the player points.

There should be a x2 multiplier for each row (above 1) that were completed. 1 completed row should earn the player 100 points. An extra 1000 points should be awarded to the player if they manage to get 4 rows cleared at once.


***** LOSS CONDITION *******

If a piece would be initially spawned overlapping at least one block in the playfield.


***** VISUALS *******


Ghosted block

The active block should show a "ghosted" image of itself where it would land if the player drops it right now.


***** NEXT BLOCK PLANEL *******

There should a panel next to the playfield that will tell you what your next block will be and draw it.

The score should exist in this panel, however, since we don't have text rendering yet, we'll save that until later. Be sure to leave some room for it for later.


*/


#endif // !GAMES_TETRIS_H_

