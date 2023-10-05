#pragma once

#include <string>
#include <string_view>

#define CHIRA_PROJECT_NAME "Chira"

#ifdef DEBUG
    #define CHIRA_DEBUG_ASSET_DIR "/home/craftablescience/CLionProjects/ChiraEngine/assets"
#endif

namespace chira::Config {

[[nodiscard]] std::string_view getConfigDirectory();
[[nodiscard]] std::string getConfigFile(std::string_view file);

} // namespace chira::Config
