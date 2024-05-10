#ifndef TETRIS_MODEL_GAME_H
#define TETRIS_MODEL_GAME_H

#include <vector>
#include "Grid.h"
#include "MoveDirection.h"
#include "Tetromino.h"
#include "Observable.h"

namespace tetris::model{

	/**
	 * Parameters of a Game
	 */
	struct GameParameters{
		/**
		 * The shapes of tetrominoes to play during the game
		 * @sa tetris::model::Tetromino::ConstructorComponents_type
		 */
		std::vector<Tetromino::ConstructorComponents_type> shapes;
		/**
		 * If specified, the game will start at a higher level of difficulty
		 */
		unsigned int level = 0;
		/**
		 * The width of the game Grid. Default is 10
		 * @sa tetris::model::Grid::Grid()
		 */
		size_t gridWidth = 10;
		/**
		 * The height of the game Grid. Default is 20
		 * @sa tetris::model::Grid::Grid()
		 */
		size_t gridHeight = 20;
		/**
		 * If specified, the game Grid will be filled with randomly placed blocks at the bottom
		 * @sa tetris::model::Grid::Grid()
		 */
		int nbAlreadyPlacedBlocks = 0;
	};

	/**
	 * Represents a game part of the Tetris game
	 */
class Game : public common::Observable{
		Grid _grid;

		std::vector<Tetromino> _bag;
		size_t _nextTetromino;

		/**
		 * Position of a Tetromino in the grid
		 */
		struct TetrominoPosition{
			size_t row;
			size_t col;
		};
		/*
		 	the current tetromino that falls is not yet in the grid,
		 	it acts as a mask above the grid
		 */
		std::optional<Tetromino> _current; // the current Tetromino that can be moved
		TetrominoPosition _currentPosition;

		const unsigned int _startLevel;
		unsigned int _currentLevel;

	protected:
		/**
		 * The current game score
		 */
		unsigned long long int score;
		/**
		 * The number of lines cleared since the start of the game
		 */
		unsigned int nbClearedLines;

	public:

		/**
		 * Alias of vector of Lines
		 * Represents an overview of the current state of the grid
		 * @sa tetris::model::Grid::getGridView()
		 * @sa tetris::model::Line
		 */
		using GridView_type = const std::vector<Line>;

		/**
		 * Creates a game part of the Tetris game
		 * @param params the parameters of the Game
		 * @sa tetris::model::GameParameters
		 */
		explicit Game(const GameParameters & params);

		/**
		 * Destructor of Game
		 */
		virtual ~Game() = default;

		/**
		 * @name Victory checks
		 * @{
		 */

		/**
		 * Determines if the game is over
		 * @return true if the game is still active, false if the game is over
		 */
		bool isGameActive() const;


		/**
		 * Determines if the game is won
		 * @return true if the game is won, false else
		 * @note The method does not really make sense if it is not override. With the simple Game class, it always returns false
		 */
		virtual bool isWon() const;

		/**
		 * @}
		 *
		 * @name Bag
		 * @{
		 */


		/**
		 * Gives an overview of the next tetromino in the bag
		 * @return a constant reference to the next tetromino
		 */
		const Tetromino & peekNext() const;

	private:

		/**
		 * Gives the next tetromino to play
		 * @return a copy of the tetromino to play
		 */
		Tetromino getNext();

		/**
		 * Shuffles the bag
		 */
		void shuffleBag();

		/**
		 * @}
		 *
		 * @name Getters
		 * @{
		 */
	public:

		/**
		 * Gives the current score
		 * @return the current score
		 */
		const unsigned long long int & getScore() const;

		/**
		 * Gives the current level
		 * @return the current level
		 */
        const unsigned int & getLevel() const;

		/**
		 * Gives an overview of the current state of the game Grid
		 * @return a view to the current state of the Grid
		 */
		GridView_type getGridView() const;

        /**
         * Gives the number of lines cleared since the start of the game
         * @return the number of line cleared
         */
        const unsigned int & getNbClearedLines() const;

		/**
		 * @}
		 *
		 * @name Actions
		 * @{
		 */

		/**
		 * Performs the action move the current tetromino down
		 */
		void goDown();

		/**
		 * Performs the action move the current tetromino to the left
		 */
		void goLeft();

		/**
		 * Performs the action move the current tetromino to the right
		 */
		void goRight();

		/**
		 * Performs the action rotate the current tetromino clockwise
		 */
		void rotateClockwise();

		/**
		 * Performs the action rotate the current tetromino counterclockwise
		 */
		void rotateCounterclockwise();

		/**
		 * Performs the action drop the current tetromino
		 */
		void drop();


	/**
	 * @}
	 */

	private:
		// Current Tetromino related

		/**
		 * Inserts a Tetromino at the top of the grid mask
		 * @param tetromino the tetromino to insert
		 * @return true if tetromino could be inserted, false if there is no place to insert it
		 */
		bool insert(Tetromino tetromino); // FIXME bool?

		/**
		 * Moves the current Tetromino in the given direction.
		 * Has no effect if the current tetromino cannot move in this direction
		 * @param direction the direction to move the tetromino
		 */
		void moveCurrent(const MoveDirection & direction);

		/**
		 * Rotates the current Tetromino in the given direction in the grid mask.
		 * Has no effect if the current tetromino cannot rotate without
		 * supperposing with grid blocks or be outside the grid boundaries.
		 * @param direction the direction to rotate the tetromino
		 * @sa tetris::model::Tetromino::rotate()
		 */
		void rotateCurrent(const RotateDirection & direction);

		/**
		 * Places the current Tetromino into the grid
		 */
		void placeCurrent();

		/**
		 * Check if the current tetromino can move in the given direction in the grid mask
		 * @param direction the direction to check
		 * @return true if the tetromino can move, false otherwise
		 */
		bool canMove(const MoveDirection & direction) /*const*/;

		/**
		 * Check if the current tetromino can rotate in the grid mask
		 * @return true if the tetromino can rotate, false otherwise
		 */
		bool canRotate() const;

		/**
		 * Verify if a tetromino touch the top of the grid
		 * @return true if is a tetromino on the top of the grid
		 */
		bool isOnTop() const; // FIXME useful?


		/**
		 * Used at the end of a movement of a the current Tetromino
		 */
		void endMovement(); // FIXME useful?

		/**
		 * Used to update game datas like score, level or number of cleared lines
		 * @param nbLinesRemoved the number of lines removed after a drop
		 * @param nbLinesCrossed the number of lines crossed by the last Tetromino before inserting
		 */
		void updateData(size_t nbLinesRemoved, size_t nbLinesCrossed = 0);


	};

} // namespace tetris::model

#endif //TETRIS_MODEL_GAME_H
