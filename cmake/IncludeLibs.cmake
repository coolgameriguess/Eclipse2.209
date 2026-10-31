cmake_minimum_required(VERSION 3.21)
add_library(third_party INTERFACE)

# Include libraries
add_library(imgui INTERFACE)
CPMAddPackage(
    NAME imgui
    GIT_REPOSITORY https://git.eclipse.menu/EclipseMenu/imgui
    GIT_TAG de917ebb95
)
target_include_directories(imgui INTERFACE ${imgui_SOURCE_DIR})
target_sources(imgui INTERFACE
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/misc/cpp/imgui_stdlib.cpp
)
set(HAS_IMGUI ON)
set(IMGUI_HOOK_EARLY OFF)

if (NOT ANDROID AND NOT IOS)
    CPMAddPackage(
        NAME discord-rpc
        GIT_REPOSITORY https://git.eclipse.menu/EclipseMenu/discord-presence
        GIT_TAG 3b50b0854e
    )
endif()

CPMAddPackage("gh:matcool/gd-imgui-cocos#b93f08c")
CPMAddPackage("gh:prevter/msgpack-for-matjson#12edd5a")
CPMAddPackage("gh:maxnut/GDR-converter#71104a9")
CPMAddPackage(
    NAME rift
    GIT_REPOSITORY https://git.eclipse.menu/EclipseMenu/rift
    GIT_TAG 0d12007e35
)
CPMAddPackage("gh:prevter/AdvancedLabel#e9e1649")
CPMAddPackage("gh:prevter/sinaps#b9c3434")
CPMAddPackage("gh:prevter/rock#6a2d29e")

if (WIN32)
    CPMAddPackage("gh:zyantific/zydis#8a961be")
endif ()

# Fix debug build
if (CMAKE_BUILD_TYPE STREQUAL "Debug" AND WIN32)
    target_compile_definitions(discord-rpc PRIVATE _ITERATOR_DEBUG_LEVEL=0)
    target_compile_definitions(rift PRIVATE _HAS_ITERATOR_DEBUGGING=0)
endif()

# Link them to the project
target_link_libraries(third_party INTERFACE
    GDRconverter
    libGDR
    imgui
    imgui-cocos
    rift
    advanced_label
    sinaps
    rock
)

if (NOT ANDROID AND NOT IOS)
    target_link_libraries(third_party INTERFACE discord-rpc)
endif()

if (WIN32)
    target_link_libraries(third_party INTERFACE Zydis Zycore)
endif ()
