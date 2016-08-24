#include "AssetManager.hpp"
#include "Texture.hpp"

#include <cinder/app/App.h>
#include <cinder/gl/gl.h>

using namespace Aton;

template<typename A>
AssetManager<A>::AssetManager(path assetRoot)
  : mAssetRoot{ std::move(assetRoot) }
{}

template<typename A>
std::shared_ptr<A> AssetManager<A>::getAsset(path filepath)
{
  auto filepath_it = mFilepathToAsset.find(filepath);
  if (filepath_it != mFilepathToAsset.end())
  {
    return filepath_it->second;
  }

  auto& asset = mFilepathToAsset[filepath] =
    std::make_shared<A>(ci::app::loadAsset(mAssetRoot / filepath));

  mAssetToFilepath[asset] = filepath;

  return asset;
}

template<typename A>
void AssetManager<A>::unloadAsset(const std::shared_ptr<A>& asset)
{
  auto path = mAssetToFilepath[asset];
  mAssetToFilepath.erase(asset);
  mFilepathToAsset.erase(path);
}

template AssetManager<Texture>;