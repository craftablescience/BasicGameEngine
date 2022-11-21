#pragma once

#include <string>
#include <memory>
#include <glm/glm.hpp>
// todo(render): move to render backend
#include <glad/gl.h>
#include <math/Types.h>
#include <utility/HandleObject.h>

namespace chira {

class DirectionalLight;
class PointLight;
class SpotLight;
class Shader;

class UniformBufferObject : public HandleObject<unsigned int> {
public:
    explicit UniformBufferObject(std::string name_, unsigned int size);
    [[nodiscard]] unsigned int getBindingPoint() const;
    void update(const byte buffer[], GLsizeiptr length) const;
    void bindToShader(Shader* shader_) const;
protected:
    unsigned int bindingPoint = 0;
    std::string name;
    static inline unsigned int uboBindingPoint = 0;
};

/// Stores two mat4 values, named PV
class PerspectiveViewUBO : public UniformBufferObject {
public:
    static PerspectiveViewUBO* get();
    void update(glm::mat4 proj, glm::mat4 view, glm::vec3 viewPos, glm::vec3 viewLookDir) const;
private:
    using UniformBufferObject::update;
    PerspectiveViewUBO();
    static inline std::unique_ptr<PerspectiveViewUBO> singleton = nullptr;
};

/// Stores lights
class LightsUBO : public UniformBufferObject {
public:
    static LightsUBO* get();
    void updateLights(DirectionalLight* directionalLights[], PointLight* pointLights[], SpotLight* spotLights[], glm::vec3 numberOfLights) const;
private:
    using UniformBufferObject::update;
    LightsUBO();
    static inline std::unique_ptr<LightsUBO> singleton = nullptr;
};

} // namespace chira
