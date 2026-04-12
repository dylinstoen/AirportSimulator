//
// Created by dylin on 4/8/2026.
//

#include "MainWindow.h"
#include "imgui.h"
void MainWindow::Draw() {
    ImGui::Begin("CFR Tool");
    _searchPanel.Draw();
    _datePickerPanel.Draw();
    _resultsPanel.Draw();
    ImGui::End();
}