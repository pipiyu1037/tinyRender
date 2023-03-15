#include "ImageLoader.h"
#include "MessageOut.h"
#include "stb_image.h"

#include <io.h>
#include <vector>
#include <utility>
#include <algorithm>

std::unordered_map<std::string, unsigned int> 
    ImageLoader::textureSet;

static void GetFiles(std::string path, std::vector<std::string>& files)
{
    long long hFile = 0;
    struct _finddata_t fileinfo;
    std::string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
        do {
            if ((fileinfo.attrib & _A_SUBDIR)) {
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                    GetFiles(p.assign(path).append("\\").append(fileinfo.name), files);
            }
            else {
                std::string ultName = p.assign(path).append("\\").append(fileinfo.name);
                replace(ultName.begin(), ultName.end(), '\\', '/');
                files.push_back(std::move(ultName));
            }
        } while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
}

unsigned int ImageLoader::GetTexture(std::string path) {
    auto result = textureSet.find(path);
    if (result == textureSet.end()) {
        MessageOut::Console << "Texture path error: " << path << "!\n";
        return 0;
    }
    return result->second;
}

void ImageLoader::Load() {
    /*std::vector<std::string> files;
    GetFiles("models", files);
    int modelCount = files.size();
    for (int i = 0; i < modelCount; ++i) {
        auto model = std::make_shared<Model>(files[i]);
        MessageOut::Console << "Load model " << i << "/" << modelCount <<
            ": " << files[i] << std::endl;
        modelSet[files[i]] = model;
    }*/
}
