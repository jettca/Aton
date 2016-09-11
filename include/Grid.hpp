#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace Aton
{
  template<typename T>
  class Grid
  {
  public:
    Grid(glm::vec2 gridSize, glm::vec2 cellSize,
      T defaultValue = T{}, glm::vec2 zeroPos = glm::vec2{ 0, 0 });

    T& operator()(const glm::vec2& pos);
    const T& operator()(const glm::vec2& pos) const;
    inline glm::ivec2 getIndexFromPos(const glm::vec2& pos) const;

    T* operator[](size_t i);
    const T* operator[](size_t i) const;

    void resize(glm::vec2 size);
    void shift(const glm::vec2& delta);

    size_t height() const { return mHeight; }
    size_t width() const { return mWidth; }
    glm::vec2 getPosFromIndex(size_t w, size_t h) const;

    typename std::vector<T>::iterator begin() { return mGrid.begin(); }
    typename std::vector<T>::const_iterator begin() const { return mGrid.begin(); }

    typename std::vector<T>::iterator end() { return mGrid.end(); }
    typename std::vector<T>::const_iterator end() const { return mGrid.end(); }

  private:
    glm::vec2 mGridSize, mCellSize, mTileOffset, mZeroPos;
    size_t mWidth, mHeight;

    std::vector<T> mGrid;
    T mDefaultValue;
  };
}

using namespace Aton;

template<typename T>
Grid<T>::Grid(glm::vec2 gridSize, glm::vec2 cellSize,
      T defaultValue, glm::vec2 zeroPos)
  : mGridSize{ std::move(gridSize) }
  , mCellSize{ std::move(cellSize) }
  , mTileOffset{ 0, 0 }
  , mZeroPos{ std::move(zeroPos) }
  , mWidth{ static_cast<size_t>(std::ceil(mGridSize.x / mCellSize.x)) + 1 }
  , mHeight{ static_cast<size_t>(std::ceil(mGridSize.y / mCellSize.y)) + 1 }
  , mGrid(mWidth * mHeight, defaultValue)
  , mDefaultValue{ std::move(defaultValue) }
{}

template<typename T>
T& Grid<T>::operator()(const glm::vec2& pos)
{
  auto coord = getIndexFromPos(pos);
  return mGrid[coord.x * mHeight + coord.y];
}

template<typename T>
const T& Grid<T>::operator()(const glm::vec2& pos) const
{
  auto coord = getIndexFromPos(pos);
  return mGrid[coord.x * mHeight + coord.y];
}

template<typename T>
glm::ivec2 Grid<T>::getIndexFromPos(const glm::vec2& pos) const
{
  return glm::ivec2{ (pos + mZeroPos) / mCellSize + mTileOffset };
}

template<typename T>
T* Grid<T>::operator[](size_t x)
{
  return mGrid.data() + x * mHeight;
}

template<typename T>
const T* Grid<T>::operator[](size_t i) const
{
  return mGrid.data() + x * mHeight;
}

template<typename T>
void Grid<T>::resize(glm::vec2 size)
{
  if (size.x < 0 || size.y < 0)
    return;

  auto oldGridSize = std::move(mGridSize);
  auto oldWidth = mWidth;
  auto oldHeight = mHeight;
  auto oldGrid = std::move(mGrid);

  mGridSize = std::move(size);
  mWidth = static_cast<size_t>(std::ceil(mGridSize.x / mCellSize.x)) + 1;
  mHeight = static_cast<size_t>(std::ceil(mGridSize.y / mCellSize.y)) + 1;
  mGrid = std::vector<T>(mWidth * mHeight, mDefaultValue);

  auto minW = glm::min(mWidth, oldWidth);
  auto minH = glm::min(mHeight, oldHeight);
  for (auto w = size_t{ 0 }; w < minW; w++) {
    for (auto h = size_t{ 0 }; h < minH; h++)
    {
      mGrid[w * mHeight + h] = std::move(oldGrid[w * oldHeight + h]);
    }
  }
}

template<typename T>
void Grid<T>::shift(const glm::vec2& delta)
{
  auto cellDelta = delta / mCellSize;

  auto intDelta = glm::ivec2{ cellDelta };
  auto shiftGridX = intDelta.x;
  auto shiftGridY = intDelta.y;

  mTileOffset = mTileOffset + cellDelta - glm::vec2{ intDelta };
  if (glm::abs(mTileOffset.x) > 0.5)
  {
    auto sign = glm::sign(mTileOffset.x);
    mTileOffset.x -= sign;
    shiftGridX += static_cast<int>(sign);
  }
  if (glm::abs(mTileOffset.y) > 0.5)
  {
    auto sign = glm::sign(mTileOffset.y);
    mTileOffset.y -= sign;
    shiftGridY += static_cast<int>(sign);
  }

  if (shiftGridX != 0 || shiftGridY != 0)
  {
    auto oldGrid = std::move(mGrid);
    mGrid = std::vector<T>(mWidth * mHeight, mDefaultValue);

    auto flooredDelta = glm::ivec2{ glm::floor(delta) };
    for (auto x = size_t{ 0 }; x < mWidth; x++)
    {
      auto newX = x - static_cast<long>(shiftGridX);
      for (auto y = size_t{ 0 }; y < mHeight; y++)
      {
        auto newY = y - static_cast<long>(shiftGridY);
        if (newY < mHeight && newX < mWidth)
        {
          mGrid[newX * mHeight + newY] = oldGrid[x * mHeight + y];
        }
      }
    }
  }
}

template<typename T>
glm::vec2 Grid<T>::getPosFromIndex(size_t w, size_t h) const
{
  return (glm::vec2{ w, h } - mTileOffset) * mCellSize - mZeroPos;
}