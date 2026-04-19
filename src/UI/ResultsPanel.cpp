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
void DrawDifNodeRecursion(const ResponseDifNode& node, int depth) {
    ImVec4 color;
    bool useColor = true;
    const char* prefix = "";
    switch (node.kind) {
        case ADDED:
            prefix = "+ ";
            color = ImVec4(0.2f, 0.9f, 0.2f, 1.0f); // green
            break;
        case REMOVED:
            prefix = "- ";
            color = ImVec4(0.9f, 0.2f, 0.2f, 1.0f); // red
            break;
        case CHANGED:
            prefix = "~ ";
            color = ImVec4(0.9f, 0.8f, 0.2f, 1.0f); // yellow
            break;
        case SAME:
            color = ImVec4(0.7f, 0.7f, 0.7f, 1.0f); // grey
        default:
            useColor = false;
            break;
    }

    if (useColor) {
        ImGui::PushStyleColor(ImGuiCol_Text, color);
    }
    std::string line = "";
    if (depth != 0) {
        line = std::string(prefix) + node.marker + " " + node.text;
    }

    if (node.kind == SAME && !node.children.empty() && depth != 0) {
        if (!ImGui::TreeNode((node.marker + " " + node.text).c_str())) {
            return;
        }
    } else {
        ImGui::TextWrapped("%s", line.c_str());
    }

    if (useColor) {
        ImGui::PopStyleColor();
    }
    if (!node.children.empty()) {
        ImGui::Indent(20.0f);
        for (const auto& child : node.children) {
            DrawDifNodeRecursion(child, depth + 1);
        }
        ImGui::Unindent(20.0f);
    }
    if (node.kind == SAME && !node.children.empty() && depth != 0) {
        ImGui::TreePop();
    }
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

            DrawDifNodeRecursion(response.body, 0);

            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    ImGui::EndChild();
}