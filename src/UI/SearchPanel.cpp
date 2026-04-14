//
// Created by dylin on 4/7/2026.
//

#include "SearchPanel.h"
#include <string>
#include <cpr/cpr.h>
#include <iostream>
#include "imgui.h"


void SearchPanel::Draw() {
    float spacing = ImGui::GetStyle().ItemSpacing.x;
    float buttonWidth = ImGui::CalcTextSize("Search").x + ImGui::GetStyle().FramePadding.x * 2.0f;

    float titleLabelWidth   = ImGui::CalcTextSize("Title").x;
    float chapterLabelWidth = ImGui::CalcTextSize("Chapter").x;
    float partLabelWidth    = ImGui::CalcTextSize("Part").x;
    float sectionLabelWidth = ImGui::CalcTextSize("Section").x;

    float avail = ImGui::GetContentRegionAvail().x;

    float totalSpacing = spacing * 8;

    float remaining = avail
        - buttonWidth
        - titleLabelWidth
        - chapterLabelWidth
        - partLabelWidth
        - sectionLabelWidth
        - totalSpacing;

    float inputWidth = remaining / 4.0f; // for 4 inputs


    ImGui::Text("Title");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(inputWidth);
    ImGui::InputTextWithHint("##Title", "14" , _title, IM_ARRAYSIZE(_title));
    ImGui::SameLine();
    ImGui::Text("Chapter");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(inputWidth);
    ImGui::InputTextWithHint("##Chapter", "I" ,_chapter, IM_ARRAYSIZE(_chapter));
    ImGui::SameLine();
    ImGui::Text("Part");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(inputWidth);
    ImGui::InputTextWithHint("##Part", "25", _part, IM_ARRAYSIZE(_part));
    ImGui::SameLine();
    ImGui::Text("Section");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(inputWidth);
    ImGui::InputTextWithHint("##Section", "25.1309" ,_section, IM_ARRAYSIZE(_section));
    ImGui::SameLine();

    if (ImGui::Button("Search")) {
        if (_controller.GetStatus() == LOADING)
            return;
        Query query;
        query.title = _title;
        query.chapter = _chapter;
        query.part = _part;
        query.section = _section;
        query.url = "https://www.ecfr.gov/api/versioner/v1/versions/title-" + query.title + ".json";
        _controller.SubmitSearch(query);
    }
}