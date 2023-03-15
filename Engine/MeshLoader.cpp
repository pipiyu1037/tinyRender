#include "MeshLoader.h"

#include "MessageOut.h"

#include <io.h>
#include <utility>
#include <algorithm>

std::unordered_map<std::string, std::shared_ptr<Model>>
	MeshLoader::modelSet;

static bool hasEnding(std::string const& fullString, std::string const& ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
    }
    else {
        return false;
    }
}

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
                if (hasEnding(ultName, ".obj") || 
                    hasEnding(ultName, ".fbx"))
                    files.push_back(std::move(ultName));
            }
        } while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
}

void MeshLoader::Load()
{
    std::vector<std::string> files;
    GetFiles("models", files);
    int modelCount = files.size();
    for (int i = 0; i < modelCount; ++i) {
        auto model = std::make_shared<Model>(files[i]);
        MessageOut::Console << "Load model " << i << "/" << modelCount <<
            ": " << files[i] << std::endl;
        modelSet[files[i]] = model;
    }
}

std::shared_ptr<Model> MeshLoader::GetModel(std::string path) {
	auto result = modelSet.find(path);
	if (result == modelSet.end()) {
		MessageOut::Console << "Model path error: " << path << "!\n";
		return std::shared_ptr<Model>();
	}
	return result->second;
}