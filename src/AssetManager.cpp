#include "AssetManager.hpp"
#include "Sprite.hpp"

#include <cinder/app/App.h>

using namespace Aton;

template<typename A>
AssetManager<A>::AssetManager(path assetRoot)
  : mAssetRoot{ std::move(assetRoot) }
  , mFilepathToAsset{}
{}

template<typename A>
A AssetManager<A>::getAsset(path filepath)
{
  auto filepath_it = mFilepathToAsset.find(filepath);
  if (filepath_it != mFilepathToAsset.end())
  {
    return filepath_it->second;
  }

  return mFilepathToAsset[filepath] = A{ ci::app::loadAsset(mAssetRoot / filepath) };
}

template AssetManager<Sprite>;