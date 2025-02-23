#pragma once

#include <cstdint>
#include <string>
#include <string_view>

#include <module/Module.h>

struct DiscordUser;

namespace chira {

struct DiscordButtonData {
    std::string name;
    std::string url;
};

/// Discord should be initialized manually before Engine::init.
/// Setter functions will change the status after update().
CHIRA_CREATE_MODULE(Discord) {
    static inline const std::vector<std::string_view> DEPS;

    void init(std::string_view appId);

    void update() override;

    void deinit() override;

    void setState(const std::string& state_);
    void setDetails(const std::string& details_);
    void setLargeImage(const std::string& imageKey);
    void setLargeImageText(const std::string& text);
    void setSmallImage(const std::string& imageKey);
    void setSmallImageText(const std::string& text);
    void setStartTimestamp(std::int64_t time);
    void setEndTimestamp(std::int64_t time);
    void setTopButton(const DiscordButtonData& button);
    void setBottomButton(const DiscordButtonData& button);

    void resetPresence();

private:
    bool dirty = false;
    std::string state;
    std::string details;
    std::string largeImage;
    std::string largeImageText;
    std::string smallImage;
    std::string smallImageText;
    std::int64_t startTimestamp = -1;
    std::int64_t endTimestamp = -1;
    DiscordButtonData button1, button2;

    using IModule::init;
};

} // namespace chira
