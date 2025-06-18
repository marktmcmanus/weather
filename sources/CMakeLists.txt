
include(FetchContent)

#
# Get wxWidgets
#

set(wxBUILD_SHARED OFF)
set(wxUSE_WEBVIEW OFF)

message(STATUS "Fetching wxWidgets...")

FetchContent_Declare(
   wxWidgets
   GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets.git
   GIT_SHALLOW ON
)
FetchContent_MakeAvailable(wxWidgets)

#
# Get nlohmann/json
#

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_MakeAvailable(json)

#
# weather library
#

set(_library_src_root_path "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}")
file(
    GLOB_RECURSE _library_source_list 
    LIST_DIRECTORIES false
    RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "${_library_src_root_path}/*.c*"
    "${_library_src_root_path}/*.h*"
)
add_library( "${PROJECT_NAME}" ${_library_source_list} )
target_include_directories("${PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/include" )
target_compile_definitions("${PROJECT_NAME}" PUBLIC WIN32_LEAN_AND_MEAN)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${_library_source_list})
target_link_libraries("${PROJECT_NAME}" PRIVATE wxcore wxnet )
target_link_libraries("${PROJECT_NAME}" PUBLIC nlohmann_json::nlohmann_json)

#
# weather.test app
#

set(SRCS 
    "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.test/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.test/MainFrame.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.test/MainFrame.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.test/TileSettingsDlg.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.test/TileSettingsDlg.cpp"
    )

if(APPLE)
	add_executable("${PROJECT_NAME}.test" MACOSX_BUNDLE ${SRCS})
    set_target_properties("${PROJECT_NAME}.test" PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.test/Info.plist)
else()
	add_executable("${PROJECT_NAME}.test" WIN32 ${SRCS} "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.test/main.exe.manifest" )
endif()

target_compile_definitions("${PROJECT_NAME}.test" PUBLIC WIN32_LEAN_AND_MEAN)
target_link_libraries("${PROJECT_NAME}.test" PRIVATE "${PROJECT_NAME}" wxcore wxnet )
