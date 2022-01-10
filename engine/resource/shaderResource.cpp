#include "shaderResource.h"

#include <sstream>
#include <regex>

#include <utility/logger.h>
#include <i18n/translationManager.h>
#include <config/glVersion.h>

using namespace chira;

std::string ShaderResource::preprocessorPrefix = std::string{SHADER_PREPROCESSOR_DEFAULT_PREFIX}; // NOLINT(cert-err58-cpp)
std::string ShaderResource::preprocessorSuffix = std::string{SHADER_PREPROCESSOR_DEFAULT_SUFFIX}; // NOLINT(cert-err58-cpp)
std::unordered_map<std::string, std::string> ShaderResource::preprocessorSymbols{};

ShaderResource::ShaderResource(const std::string& identifier_, int type_) : StringResource(identifier_), HandleObject<int>(), type(type_) {}

void ShaderResource::compile(const unsigned char buffer[], std::size_t bufferLength) {
    if (this->handle != -1)
        return;
    this->handle = glCreateShader(this->type);

    StringResource::compile(buffer, bufferLength);
    this->data = std::string{GL_VERSION_STRING} + "\n\n" + this->data;

    // WARNING: The following code is HYPER SENSITIVE
    // If you change ANYTHING it will BREAK HORRIBLY
    // TEST ALL CHANGES

    // Includes
    static const std::regex includes{ShaderResource::preprocessorPrefix +
                                     "(include[ \t]+([a-z:\\/.]+))" +
                                     ShaderResource::preprocessorSuffix,
                                     std::regex_constants::icase | std::regex_constants::optimize};
    // Add the include as a macro to be expanded
    // This has the positive side effect of caching previously used includes
    for (std::sregex_iterator it{this->data.begin(), this->data.end(), includes}; it != std::sregex_iterator{}; it++) {
        if (it->str(2) == this->identifier)
            continue;
        if (ShaderResource::preprocessorSymbols.count(it->str(2)) == 0) {
            auto contents = Resource::getResource<StringResource>(it->str(2));
            ShaderResource::addPreprocessorSymbol(it->str(1), contents->getString());
        }
        Resource::cleanup(); // todo: clean up from resource destructor
    }

    // Macros
    for (const auto& [key, value] : ShaderResource::preprocessorSymbols) {
        std::string fullKey = ShaderResource::preprocessorPrefix;
        fullKey += key;
        fullKey += ShaderResource::preprocessorSuffix;
        this->data = std::regex_replace(this->data.data(), std::regex{fullKey}, value);
    }

    const char* dat = this->data.c_str();
    glShaderSource(this->handle, 1, &dat, nullptr);
    glCompileShader(this->handle);
#if DEBUG
    this->checkForCompilationErrors();
#endif
}

ShaderResource::~ShaderResource() {
    if (this->handle != -1)
        glDeleteShader(this->handle);
}

void ShaderResource::checkForCompilationErrors() const {
    int success;
    char infoLog[512];
    glGetShaderiv(this->handle, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(this->handle, 512, nullptr, infoLog);
        Logger::log(LogType::ERROR, "Shader Resource", fmt::format(TR("error.shader_resource.compilation_failure"), this->type, infoLog));
    }
}

unsigned int ShaderResource::getType() const {
    return this->type;
}

void ShaderResource::addPreprocessorSymbol(const std::string& name, const std::string& value) {
    if (ShaderResource::preprocessorSymbols.count(name) == 0) {
        ShaderResource::preprocessorSymbols.insert(std::pair<std::string, std::string>{name, value});
    } else {
        ShaderResource::preprocessorSymbols[name] = value;
    }
}

void ShaderResource::setPreprocessorPrefix(const std::string& prefix) {
    ShaderResource::preprocessorPrefix = prefix;
}

void ShaderResource::setPreprocessorSuffix(const std::string& suffix) {
    ShaderResource::preprocessorSuffix = suffix;
}
