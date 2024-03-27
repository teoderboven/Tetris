#include "Tetromino.h"
#include "util/maxVectorSize.hpp"
#include <iostream>

namespace tetris::model {

    Tetromino::Tetromino(Shape_type shape, Color color) :
            _shape(util::maxVectorSize(shape), std::vector<std::optional<Block>>(util::maxVectorSize(shape)))
    // 				    ^ Make the largest matrix to store the shape even when rotated
    {
        for (size_t i{0}; i < shape.size(); ++i) {
            for (size_t j{0}; j < shape[i].size(); ++j) {
                if (shape[i][j]) {
                    this->_shape[i][j] = Block(color);
                }
            }
        }
    }

    Tetromino::Tetromino(ConstructorComponents_type ctorCmpnts) :
            _shape(util::maxVectorSize(ctorCmpnts.first),
                   std::vector<std::optional<Block>>(util::maxVectorSize(ctorCmpnts.first)))
    //              ^ Make the largest matrix to store the shape even when rotated
    {
        for (size_t i{0}; i < ctorCmpnts.first.size(); ++i) {
            for (size_t j{0}; j < ctorCmpnts.first[i].size(); ++j) {
                if (ctorCmpnts.first[i][j]) {
                    this->_shape[i][j] = Block(ctorCmpnts.second);
                }
            }
        }
    }


    Block Tetromino::get(size_t x, size_t y) const {
        return _shape[x][y].value();
    }


    bool Tetromino::isOccupied(size_t x, size_t y) const {
        return _shape[x][y].has_value();
    }


    //source : https://www.javatpoint.com/rotate-matrix-by-90-degrees-in-java
    void Tetromino::rotate(RotateDirection direction) {
        size_t size = _shape.size();
        std::vector<std::vector<std::optional<Block>>> tempShape(size, std::vector<std::optional<Block>>(size));

        if (direction == RotateDirection::CCW) {
            for (size_t i = 0; i < size; ++i) {
                for (size_t j = 0; j < size; ++j) {
                    tempShape[size - j - 1][i] = _shape[i][j];
                }
            }
        } else if (direction == RotateDirection::CW) {
            for (size_t i = 0; i < size; ++i) {
                for (size_t j = 0; j < size; ++j) {
                    tempShape[j][size - i - 1] = _shape[i][j];
                }
            }
        }

        _shape = tempShape;
    }


    size_t Tetromino::getHeight() const {
        int height{0};

        int vectorHeight {static_cast<int>(_shape.size())}; //used for optimise the loop
        for (int y{0}; y < _shape[0].size(); ++y) {
            int tempHeight{0};
            for (int x{0}; x < vectorHeight; ++x) {
                if (_shape[x][y].has_value()) {
                    tempHeight++;
                }
            }
            if (tempHeight > height) {
                height = tempHeight;
            }
        }

        return height;
    }




    size_t Tetromino::getWidth() const {
        int width{0};
        int vectorWidth {static_cast<int>(_shape[0].size())}; //used for optimise the loop

        for (int x{0}; x < _shape.size(); ++x) {
            int tempWidth{0};
            for (int y{0}; y < vectorWidth; ++y) {
                if (_shape[x][y].has_value()) {
                    tempWidth++;
                }
            }
            if (tempWidth > width) {
                width = tempWidth;
            }
        }

        return width;
    }

    //Only a test - to delete after
    void Tetromino::print() const {
        for (const auto& row : _shape) {
            for (const auto& block : row) {
                std::cout << (block.has_value() ? 'X' : '_');
            }
            std::cout << '\n';
        }
    }


} // namespace tetris::model
