
if (UNIX)
    find_package (Eigen3 REQUIRED)
    add_executable(spaam_tool_eigen SPAAM_code.cpp)
    target_link_libraries(spaam_tool_eigen Eigen3::Eigen)
elseif (WIN32)
    add_executable(spaam_tool_eigen SPAAM_code.cpp)
    target_link_libraries(spaam_tool_eigen PRIVATE CONAN_PKG::Eigen3)

    add_library(spaam STATIC SPAAM_code.cpp spaam.cpp)
    target_include_directories(spaam PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
    target_link_libraries(spaam  PUBLIC CONAN_PKG::opencv 
                                 PRIVATE CONAN_PKG::Eigen3)
endif ()
