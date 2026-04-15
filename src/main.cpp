#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include <cstdio>
#include <iostream>

#include "SearchController.h"
#include "UI/MainWindow.h"

#include <cpr/cpr.h>


// TODO: Create a aircraft controller simulator with each aircraft having a certain desired elevation and a PID Controller that simulates take off.
static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}
int main() {
    // setup
    glfwSetErrorCallback(glfw_error_callback);
    glfwInit(); // inits glfw window and input system.
    float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor()); // Valid on GLFW 3.3+ only
    GLFWwindow* window = glfwCreateWindow((int)(1280 * main_scale), (int)(800 * main_scale), "CFR Analyzer", nullptr, nullptr); // creates a glfw window
    if (window == nullptr)
        return 1;
    glfwMakeContextCurrent(window); // creates an opengl context and ties it to the window

    glfwSwapInterval(1); // Enable vsync

    IMGUI_CHECKVERSION(); // check to make sure the headers match the compiled code
    ImGui::CreateContext(); // starts the imgui engine
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(main_scale);        // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
    style.FontScaleDpi = main_scale;        // Set initial font scale. (in docking branch: using io.ConfigDpiScaleFonts=true automatically overrides this for every window depending on the current monitor)

    // backend bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true); // handles input
    ImGui_ImplOpenGL3_Init("#version 130"); // handles renderingS
    ImVec4 clear_color = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    CompareController _compareController;
    SearchController _searchController;
    MainWindow _mainWindow(_searchController, _compareController);

    // draw frames
    while (!glfwWindowShouldClose(window)) { // runs until window is closed
        glfwPollEvents(); // updates keyboard, mouse, and window events
        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
        {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }
        // start a new imgui frame (reset ui and start a new frame)
        ImGui_ImplOpenGL3_NewFrame(); // backend prepares opengl
        ImGui_ImplGlfw_NewFrame(); // backend prepares glfw input
        ImGui::NewFrame(); // imgui starts a new frame
        // Everything ImGui related should be between here

        _mainWindow.Draw();

        // and here
        ImGui::Render(); // converts ui calls into draw commands
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT); // clears previous frame (don't draw on top of old frames)
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); // takes imgui draw commands and sends them to opengl to actually render

        glfwSwapBuffers(window); // displays the rendered frame.
    }
    // clean up imgui + backend
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // destroy window and shut down glfw
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}