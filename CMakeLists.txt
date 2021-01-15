
if (UNIX)
    find_package (Eigen3 REQUIRED)
    add_executable(spaam_tool_eigen SPAAM_code.cpp)
    target_link_libraries(spaam_tool_eigen Eigen3::Eigen)
elseif (WIN32)
    add_executable(spaam_tool_eigen SPAAM_code.cpp)
    target_link_libraries(spaam_tool_eigen CONAN_PKG::eigen)
endif ()
