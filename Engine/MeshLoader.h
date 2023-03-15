#pragma once
#include "Model.h"

#include <unordered_map>
#include <string>
#include <memory>

class MeshLoader // static class
{
private:
	MeshLoader();

public:
	static void Load();

	static std::shared_ptr<Model> GetModel(std::string path);

private:
	static std::unordered_map<std::string, std::shared_ptr<Model>> modelSet;
};

