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
    A getAsset(path filepath);

  private:
    path mAssetRoot;
    std::map<path, A> mFilepathToAsset;
  };
}