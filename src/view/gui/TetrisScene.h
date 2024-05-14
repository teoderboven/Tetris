#ifndef TETRISSCENE_H
#define TETRISSCENE_H

#include <QGraphicsView>
#include <QLabel>
#include "Observer.h"
#include "Game.h"
#include "NextTetromino.h"

namespace tetris::view::gui {
	using namespace common;

	/**
	 * Represents the graphical window of the game Tetris
	 */
	class TetrisScene : public QWidget, Observer {
	Q_OBJECT

		QGraphicsView *gameBoard;
		QLabel *scoreValue;
		QLabel *levelValue;
		QLabel *clearedLinesValue;
		NextTetromino *nextTetromino;

	public:
		/**
		 * Creates a tetris game window
		 * @param game the game on which the view will be based
		 * @param parent the parent of the window
		 */
		explicit TetrisScene(model::Game &game, QWidget *parent = nullptr);

		/**
		 * Destructor of the window
		 */
		~TetrisScene() override;

		/**
		 * No copy constructor
		 */
		TetrisScene(TetrisScene &) = delete;

		/**
		 * No copy assignment operator
		 */
		TetrisScene &operator=(TetrisScene &) = delete;

		/**
		 * Updates the board display
		 * @param gridView the view on which to base the display
		 */
		void updateGameBoard(const model::Game::GridView_type &gridView);

		// observer
		void update(ActionType action, void *subject) override;

		/**
		 * Displays the game over message
		 * @param isWon true if the game is won, false otherwise
		 */
		void displayGameOver(bool isWon);

	signals:

		/**
		 * Signal sent after keyboard input
		 */
		void keyboardInput(const int &key);

	protected:

		void keyPressEvent(QKeyEvent *event) override;

	private:

		/**
		 * Inits the data container
		 * @param game the game with which to recover the data's
		 * @return the layout that contains data's
		 */
		QLayout *initDataContainer(model::Game &game);

		/**
		 * Sets the values of game statistics
		 * @param game the game with which to recover the data's
		 */
		void updateDatasValues(model::Game &game);


	};

} // namespace tetris::view::gui

#endif // TETRISSCENE_H