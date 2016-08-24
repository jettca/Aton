#pragma once

#include <filesystem>
#include <map>

namespace Aton
{
  using namespace std::experimental::filesystem::v1;

  template<typename A>
  class AssetManager
  {
  private:
    using byte_t = unsigned char;

  public:
    AssetManager(path assetRoot);
    std::shared_ptr<A> getAsset(path filepath);
    void unloadAsset(const std::shared_ptr<A>& asset);

  private:
    path mAssetRoot;
    std::map<path, std::shared_ptr<A>> mFilepathToAsset;
    std::map<std::shared_ptr<A>, path> mAssetToFilepath;
  };
}