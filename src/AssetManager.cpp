#include "AssetManager.hpp"

using namespace Aton;

template<typename A>
AssetManager<A>::AssetManager(path assetRoot)
  : mAssetRoot{ std::move(assetRoot) }
  , mFilepathToAsset{}
{}

template<typename A>
A AssetManager<A>::getBatch(path filepath)
{
  auto filepath_it = mFilepathToBatch.find(filepath);
  if (filepath_it != mFilepathToBatch.end())
  {
    return filepath_it->second;
  }

  return mFilepathToAsset[filepath] = A{ mAssetRoot / filepath };
}

namespace Aton
{
  class Sprite;
}

template AssetManager<Sprite>;