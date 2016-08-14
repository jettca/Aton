#pragma once

#include <filesystem>
#include <map>

namespace Aton
{
  using namespace std::experimental::filesystem::v1;

  class AssetManager
  {
  private:
    using byte_t = unsigned char;

  public:
    AssetManager(path assetRoot);
    const std::vector<byte_t>& getData(path filepath);

  private:
    path mAssetRoot;
    std::map<path, std::vector<byte_t>> mFilepathToData;
  };
}