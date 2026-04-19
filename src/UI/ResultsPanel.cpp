//
// Created by dylin on 4/9/2026.
//

#include "ResultsPanel.h"

#include <iostream>

#include "imgui.h"
#include "../Model/Response.h"

void DrawNodeRecursion(const ResponseNode& node, int depth) {
    std::string line = node.marker + " " + node.text;
    ImGui::TextWrapped("%s", line.c_str());
    if (node.children.empty()) {
        return;
    }
    ImGui::Indent(20.0f);
    for (const auto& child : node.children) {
        DrawNodeRecursion(child, depth + 1);
    }
    ImGui::Unindent(20.0f);
}
void ResultsPanel::Draw() const {
    if (_controller.GetStatus() == Status::Error) {
        std::cout << _controller.GetError() << std::endl;
        return;
    }
    if (_controller.GetStatus() != Status::SUCCESS) {
        return;
    }
    ImGui::BeginChild("Content", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), ImGuiChildFlags_None);
    if (ImGui::BeginTabBar("ResultsTab")) {
        if (ImGui::BeginTabItem("First")) {
            const auto& response = _controller.GetResponseFirstDate();

            ImGui::Text("%s", response.header.c_str());
            ImGui::Separator();

            DrawNodeRecursion(response.body, 0);

            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Second")) {
            const auto& response = _controller.GetResponseSecondDate();
            ImGui::Text("%s", response.header.c_str());
            ImGui::Separator();
            DrawNodeRecursion(response.body, 0);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Diff")) {
            const auto& response = _controller.GetDiffResponse(); // you implement this

            ImGui::Text("%s", response.header.c_str());
            ImGui::Separator();

            DrawNodeRecursion(response.body, 0);

            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    ImGui::EndChild();
}