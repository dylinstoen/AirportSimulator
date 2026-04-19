//
// Created by dylin on 4/10/2026.
//

#include "DatePickerPanel.h"

#include <iostream>
#include <ostream>

#include "imgui.h"
int selectedIndexFirst = 0;
int selectedIndexSecond = 0;
void DatePickerPanel::Draw() {
    if (_searchController.GetResults().empty() || _searchController.GetStatus() != Status::SUCCESS) {
        return;
    }
    float buttonWidth = ImGui::CalcTextSize("Compare").x + ImGui::GetStyle().FramePadding.x * 2.0f;
    float spacing = ImGui::GetStyle().ItemSpacing.x;
    float label1Width = ImGui::CalcTextSize("First Date").x;
    float label2Width = ImGui::CalcTextSize("Second Date").x;
    float avail = ImGui::GetContentRegionAvail().x;
    float remaining = avail
        - label1Width
        - label2Width
        - buttonWidth
        - spacing * 4;
    float comboWidth = remaining * 0.5f;


    ImGui::Text("First Date");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(comboWidth);
    if (ImGui::BeginCombo("##DatePickerFirst", _searchController.GetResults().at(selectedIndexFirst).c_str())) {
        for (int i = 0; i < _searchController.GetResults().size(); i++) {
            bool isSelected = selectedIndexFirst == i;
            if (ImGui::Selectable(_searchController.GetResults().at(i).c_str(), isSelected)) {
                selectedIndexFirst = i;
            }
            if (isSelected) {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }
    ImGui::SameLine();
    ImGui::Text("Second Date");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(comboWidth);
    if (ImGui::BeginCombo("##DatePickerSecond", _searchController.GetResults().at(selectedIndexSecond).c_str())) {
        for (int i = 0; i < _searchController.GetResults().size(); i++) {
            bool isSelected = selectedIndexSecond == i;
            if (ImGui::Selectable(_searchController.GetResults().at(i).c_str(), isSelected)) {
                selectedIndexSecond = i;
            }
            if (isSelected) {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }
    ImGui::SameLine();
    if (ImGui::Button("Compare")) {
        if (_compareController.GetStatus() == Status::LOADING) {
            return;
        }
        std::string firstDate = _searchController.GetResults().at(selectedIndexFirst);
        std::string secondDate = _searchController.GetResults().at(selectedIndexSecond);
        Query query = _searchController.GetQuery();
        _compareController.SubmitCompare(query, firstDate,
            secondDate);
    }
}
