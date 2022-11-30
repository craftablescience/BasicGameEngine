#include "FramePanel.h"

#include <entity/root/Frame.h>

using namespace chira;

FramePanel::FramePanel(const std::string& title_, bool startVisible, ImVec2 windowSize, bool enforceSize)
    : IPanel(title_, startVisible, windowSize, enforceSize), currentSize(windowSize.x, windowSize.y) {
    this->frame = new Frame{static_cast<int>(windowSize.x), static_cast<int>(windowSize.y)};
}

FramePanel::~FramePanel() {
    delete this->frame;
}

void FramePanel::renderContents() {
    if (ImGui::BeginChild("__internal_frame__")) {
        ImVec2 guiSize = ImGui::GetWindowSize();
        glm::vec2i size{guiSize.x, guiSize.y};
        if (this->currentSize != size) {
            this->frame->setFrameSize(size);
            this->currentSize = size;
        }
        // thank you C++ for this whole casting mess
        // todo(render): abstract this
        ImGui::Image(reinterpret_cast<ImTextureID>(static_cast<unsigned long long>(this->frame->handle.colorHandle)), guiSize, ImVec2(0, 1), ImVec2(1, 0));
    }
    ImGui::EndChild();
}
