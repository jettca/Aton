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
    T* operator[](size_t i);
    const T* operator[](size_t i) const;

    void resize(glm::vec2 size);
    void shift(const glm::vec2& delta);

    size_t height() const { return mHeight; }
    size_t width() const { return mWidth; }
    glm::vec2 getPosFromIndex(int w, int h) const;

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
  auto coord = glm::ivec2{ (pos + mZeroPos + mTileOffset) / mCellSize };
  return mGrid[coord.x * mHeight + coord.y];
}

template<typename T>
const T& Grid<T>::operator()(const glm::vec2& pos) const
{
  auto coord = glm::ivec2{ (pos + mZeroPos + mTileOffset) / mCellSize };
  return mGrid[coord.x * mHeight + coord.y];
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

  auto minX = glm::min(oldGridSize.x, mGridSize.x) / mCellSize.x;
  auto minY = glm::min(oldGridSize.y, mGridSize.y) / mCellSize.y;
  for (auto x = int{ 0 }; x < minX; x++) {
    for (auto y = int{ 0 }; y < minY; y++)
    {
      mGrid[x * mHeight + y] = std::move(oldGrid[x * oldHeight + y]);
    }
  }
}

template<typename T>
void Grid<T>::shift(const glm::vec2& delta)
{
  auto oldGrid = std::move(mGrid);
  mGrid = std::vector<T>(mWidth * mHeight, mDefaultValue);

  auto newOffset = mTileOffset + delta - glm::vec2{ glm::ivec2{ delta } };
  if (newOffset.x < 0) newOffset.x = 1 - newOffset.x;
  if (newOffset.y < 0) newOffset.y = 1 - newOffset.y;
  mTileOffset = newOffset - glm::vec2{ glm::ivec2{ newOffset } };

  auto flooredDelta = glm::ivec2{ glm::floor(delta) };
  for (auto x = size_t{ 0 }; x < mWidth; x++) {
    for (auto y = size_t{ 0 }; y < mHeight; y++)
    {
      auto newX = x + flooredDelta.x;
      auto newY = y + flooredDelta.y;
      if (newY < mHeight && newX < mWidth && newY >= 0 && newX >= 0)
      {
        mGrid[newX * mHeight + newY] = oldGrid[x * mHeight + y];
      }
    }
  }
}

template<typename T>
glm::vec2 Grid<T>::getPosFromIndex(int w, int h) const
{
  return glm::vec2{ w, h } * mCellSize - mZeroPos - mTileOffset;
}