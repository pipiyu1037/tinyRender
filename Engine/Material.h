#pragma once
#include "Shader.h"
#include "MeshRenderer.h"
#include "MessageOut.h"

#include <string>
#include <unordered_map>
#include <vector>

class MeshRenderer;

class Material // abstract class
{
public:
	struct Property {
		float value;
		const float minVal;
		const float maxVal;
		Property(float val, float minv, float maxv) :
			value(val), minVal(minv), maxVal(maxv) {}
	};

	Material(MeshRenderer& meshRenderer) :
		meshRenderer(meshRenderer) {}
	virtual ~Material() = default;
	virtual void Set() = 0;
	virtual Shader& GetShader() = 0;

	void SetProperty(std::string name, float value) {
		auto iter = properties.find(name);
		if (iter != properties.end()) {
			iter->second.value = value;
		}
		else {
			MessageOut::Console << "Wrong shader property: "
				<< name << "!\n";
		}
	}

	std::vector<std::pair<std::string, Property>> GetProperties() {
		std::vector<std::pair<std::string, Property>> result;
		for (auto proper : properties) {
			result.push_back(proper);
		}
		return result;
	}

	MeshRenderer& meshRenderer;

protected:
	std::unordered_map<std::string, Property> properties;
};

