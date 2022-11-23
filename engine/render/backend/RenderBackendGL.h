#pragma once

#include <string_view>
#include <vector>
#include <loader/image/Image.h>
#include <math/Types.h>
#include <math/Vertex.h>
#include "RendererTypes.h"

namespace chira {

struct MeshHandle {
    unsigned int vaoHandle;
    unsigned int vboHandle;
    unsigned int eboHandle;
};

struct RenderBackendGL {
    RenderBackendGL() = delete;

    [[nodiscard]] static std::string_view getHumanName();
    [[nodiscard]] static bool setupForDebugging();

    [[nodiscard]] static int getTextureFormat(TextureFormat format);
    [[nodiscard]] static int getTextureFormatFromBitDepth(int bd);
    [[nodiscard]] static int getWrapMode(WrapMode mode);
    [[nodiscard]] static int getFilterMode(FilterMode mode);
    [[nodiscard]] static unsigned int createTexture2D(const Image& image, WrapMode wrapS, WrapMode wrapT, FilterMode filter,
                                                      bool genMipmaps = true, TextureUnit activeTextureUnit = TextureUnit::G0);
    [[nodiscard]] static unsigned int createTextureCubemap(const Image& imageRT, const Image& imageLT, const Image& imageUP,
                                                           const Image& imageDN, const Image& imageFD, const Image& imageBK,
                                                           WrapMode wrapS, WrapMode wrapT, WrapMode wrapR, FilterMode filter,
                                                           bool genMipmaps = true, TextureUnit activeTextureUnit = TextureUnit::G0);
    static void useTexture(TextureType type, unsigned int handle, TextureUnit activeTextureUnit = TextureUnit::G0);

    [[nodiscard]] static int getShaderModuleType(ShaderModuleType type);
    [[nodiscard]] static int createShaderModule(const std::string& shader, ShaderModuleType type);
    static void destroyShaderModule(int handle);

    [[nodiscard]] static int getMeshDrawMode(MeshDrawMode mode);
    [[nodiscard]] static int getMeshDepthFunction(MeshDepthFunction function);
    [[nodiscard]] static int getMeshCullType(MeshCullType type);
    [[nodiscard]] static MeshHandle createMesh(const std::vector<Vertex>& vertices, const std::vector<Index>& indices, MeshDrawMode drawMode);
    static void updateMesh(MeshHandle handle, const std::vector<Vertex>& vertices, const std::vector<Index>& indices, MeshDrawMode drawMode);
    static void drawMesh(MeshHandle handle, const std::vector<Index>& indices, MeshDepthFunction depthFunction, MeshCullType cullType);
    static void destroyMesh(MeshHandle handle);
};

} // namespace chira
