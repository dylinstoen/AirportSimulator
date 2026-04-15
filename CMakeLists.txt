cmake_minimum_required(VERSION 3.20)
project(AirportSimulator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
        json
        URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(json)

FetchContent_Declare(
        cpr
        GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 1.14.2
)
FetchContent_Declare(
        tinyxml2
        GIT_REPOSITORY https://github.com/leethomason/tinyxml2.git
        GIT_TAG 11.0.0  # or latest
)
FetchContent_MakeAvailable(cpr)
FetchContent_MakeAvailable(tinyxml2)

set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/external/imgui)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_library(imgui
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backends
)

target_link_libraries(imgui PUBLIC
        glfw
)

add_executable(AirportSimulator
        src/main.cpp
        src/UI/SearchPanel.cpp
        src/UI/SearchPanel.h
        src/UI/MainWindow.cpp
        src/UI/MainWindow.h
        src/UI/ResultsPanel.cpp
        src/UI/ResultsPanel.h
        src/SearchController.cpp
        src/SearchController.h
        src/RegulationService.cpp
        src/RegulationService.h
        src/Model/Query.h
        src/Model/Query.h
        src/UI/DatePickerPanel.cpp
        src/UI/DatePickerPanel.h
        src/CompareController.cpp
        src/CompareController.h
        src/CompareController.h
        src/Model/Status.h
        src/Model/Status.h
        src/CompareResponseMotor.cpp
        src/CompareResponseMotor.h
        src/CompareResponseMotor.h
        src/Utilities/MarkerDetector.h
        src/Utilities/MarkerDetector.h
        src/Utilities/MarkerDetector.cpp
        src/Utilities/MarkerDetector.cpp
        src/Model/MarkerKind.h
        src/Model/MarkerKind.h
        src/Utilities/MarkerCycle.cpp
        src/Utilities/MarkerCycle.h
        src/Utilities/MarkerCycle.h
        src/Model/Response.h
        src/Model/Response.h
)

target_link_libraries(AirportSimulator PRIVATE
        imgui
        glfw
        OpenGL::GL
        nlohmann_json::nlohmann_json
        cpr::cpr
        tinyxml2
)