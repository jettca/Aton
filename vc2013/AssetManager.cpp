#include "AssetManager.hpp"

#include <fstream>
#include <iterator>

using namespace Aton;

AssetManager::AssetManager(path assetRoot)
  : mAssetRoot{ std::move(assetRoot) }
  , mFilepathToData{}
{}

const std::vector<AssetManager::byte_t>& AssetManager::getData(path filepath)
{
  auto filepath_it = mFilepathToData.find(filepath);
  if (filepath_it != mFilepathToData.end())
  {
    return filepath_it->second;
  }

  auto data = std::vector<byte_t>{};
  auto instream = std::ifstream{ mAssetRoot / filepath };
  std::copy(std::istream_iterator<byte_t>{ instream },
    std::istream_iterator<byte_t>{}, std::back_inserter(data));

  return mFilepathToData[filepath] = std::move(data);
}