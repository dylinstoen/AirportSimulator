#include "imgui.h"
#include <cmath>
#include "Display.h"

static bool cfr_analyzer = true;
static float my_color[4] = {0.2f, 0.7f, 0.3f, 1.0f};
static char buf1[64];
static int MyCallback(ImGuiInputTextCallbackData* data)
{
    if (data->EventFlag == ImGuiInputTextFlags_CallbackCompletion)
    {
        data->InsertChars(data->CursorPos, "..");
    }
    else if (data->EventFlag == ImGuiInputTextFlags_CallbackHistory)
    {
        if (data->EventKey == ImGuiKey_UpArrow)
        {
            data->DeleteChars(0, data->BufTextLen);
            data->InsertChars(0, "Pressed Up!");
            data->SelectAll();
        }
        else if (data->EventKey == ImGuiKey_DownArrow)
        {
            data->DeleteChars(0, data->BufTextLen);
            data->InsertChars(0, "Pressed Down!");
            data->SelectAll();
        }
    }
    else if (data->EventFlag == ImGuiInputTextFlags_CallbackEdit)
    {
        // Toggle casing of first character
        char c = data->Buf[0];
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) data->Buf[0] ^= 32;
        data->BufDirty = true;

        // Increment a counter
        int* p_int = (int*)data->UserData;
        *p_int = *p_int + 1;
    }
    return 0;
}
void Display::DrawToolbar() {
    if (!cfr_analyzer)
        return;

    ImGui::Begin("CFR Analyzer", &cfr_analyzer, ImGuiWindowFlags_MenuBar);

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
            if (ImGui::MenuItem("Save", "Ctrl+S"))   { /* Do stuff */ }
            if (ImGui::MenuItem("Close", "Ctrl+W"))  { cfr_analyzer = false; }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }


    ImGui::TextColored(ImVec4(1, 1, 0, 1), "Important Stuff");
    ImGui::BeginChild("Sidebar", ImVec2(ImGui::GetContentRegionAvail().x * 0.3f, ImGui::GetContentRegionAvail().y), ImGuiChildFlags_None);
    ImGui::InputText("Search", buf1, IM_COUNTOF(buf1), ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory, MyCallback);
    for (int n = 0; n < 50; n++)
        ImGui::Text("%04d: Some text", n);
    ImGui::EndChild();
    ImGui::SameLine();
    ImGui::BeginChild("Content", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), ImGuiChildFlags_None);
    for (int n = 0; n < 50; n++)
        ImGui::Text("%04d: Some text", n);
    ImGui::EndChild();




    ImGui::End(); // rebuild entire ui every frame. Not in retained mode but in immediate mode
}


static bool show_demo_window = true;
static bool show_another_window = false;

void Display::DrawDemo(ImVec4 clear_color, ImGuiIO& io) {
    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
        ImGui::Checkbox("Another Window", &show_another_window);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::End();
    }

    // 3. Show another simple window.
    if (show_another_window)
    {
        ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me"))
            show_another_window = false;
        ImGui::End();
    }
}