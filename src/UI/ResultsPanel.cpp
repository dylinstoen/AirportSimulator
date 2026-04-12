//
// Created by dylin on 4/9/2026.
//

#include "ResultsPanel.h"
#include "imgui.h"

void ResultsPanel::Draw() {
    ImGui::BeginChild("Content", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), ImGuiChildFlags_None);
    for (int n = 0; n < 50; n++)
        ImGui::Text("%04d: Some text", n);
    ImGui::EndChild();
}
