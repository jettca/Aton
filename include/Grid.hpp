#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace Aton
{
  template<typename T>
  class Grid
  {
  public:
    Grid(glm::uvec2 gridSize, glm::uvec2 cellSize,
      T defaultValue = T{}, glm::vec2 zeroPos = glm::vec2{ 0, 0 });

    T& operator()(const glm::vec2& pos);
    const T& operator()(const glm::vec2& pos) const;

    void resize(glm::vec2 size);

    void shift(const glm::vec2& delta);

  private:
    glm::vec2 mZeroPos;
    glm::uvec2 mGridSize, mCellSize, mTileOffset;
    size_t mWidth, mHeight;

    std::vector<T> mGrid;
    T mDefaultValue;
  };
}

using namespace Aton;

template<typename T>
Grid<T>::Grid(glm::uvec2 gridSize, glm::uvec2 cellSize,
      T defaultValue, glm::vec2 zeroPos)
  : mGridSize{ std::move(gridSize) }
  , mCellSize{ std::move(cellSize) }
  , mTileOffset{ 0, 0 }
  , mZeroPos{ std::move(zeroPos) }
  , mWidth{ static_cast<size_t>(std::ceil(mGridSize.x / mCellSize.x)) + 1 }
  , mHeight{ static_cast<size_t>std::ceil(mGridSize.y / mCellSize.y)) + 1 }
  , mGrid{ mWidth * mHeight }
{}

template<typename T>
T& Grid<T>::operator()(const glm::vec2& pos)
{
  auto coord = glm::ivec2{ (pos + mZeroPos + mTileOffset) / mCellSize };
  return mGrid[coord.y * mWidth + coord.x];
}

template<typename T>
const T& Grid<T>::operator()(const glm::vec2& pos) const
{
  auto coord = glm::ivec2{ (pos + mZeroPos + mTileOffset) / mCellSize };
  return mGrid[coord.y * mWidth + coord.x];
}

template<typename T>
void Grid<T>::resize(glm::vec2 size)
{
  auto oldGridSize = std::move(mGridSize);
  auto oldWidth = mWidth;
  auto oldHeight = mHeight;
  auto oldGrid = std::move(mGrid);

  mGridSize = std::move(size);
  mWidth = static_cast<size_t>(std::ceil(mGridSize.x / mCellSize.x));
  mHeight = static_cast<size_t>(std::ceil(mGridSize.y / mCellSize.y));
  mGrid = std::vector<T>(mWidth * mHeight, mDefaultValue);

  auto minX = glm::min(oldGridSize.x, mGridSize.x);
  auto minY = glm::min(oldGridSize.y, mGridSize.y);
  for (auto x = int{ 0 }; x < minX; x++) {
    for (auto y = int{ 0 }; y < minY; y++)
    {
      mGrid[y * mWidth + x] = std::move(oldGrid[y * oldWidth + x]);
    }
  }
}

template<typename T>
void Grid<T>::shift(const glm::vec2& delta)
{
  auto oldGrid = std::move(mGrid);
  mGrid = std::vector<T>(mWidth * mHeight, mDefaultValue);

  auto oldOffset = mTileOffset;

  auto newOffset = mTileOffset + delta - glm::vec2{ glm::ivec2{ delta } };
  if (newOffset < 0) newOffset = 1 - newOffset;
  mTileOffset = newOffset - glm::ivec2{ newOffset };

  auto flooredDelta = glm::ivec2{ glm::floor(delta) };
  for (auto x = int{ 0 }; x < mGridSize.x; x++) {
    for (auto y = int{ 0 }; y < mGridSize.y; y++)
    {
      auto newX = x + flooredDelta.x;
      auto newY = y + flooredDelta.y;
      if (newY < mHeight && newX < mWidth && newY >= 0 && newX >= 0)
      {
        mGrid[newY * mWidth + newX] = oldGrid[y * mWidth + x];
      }
    }
  }
}