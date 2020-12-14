
find_package (Eigen3 REQUIRED)

add_executable(spaam_tool_eigen SPAAM_Code.cpp)
target_link_libraries(spaam_tool_eigen Eigen3::Eigen)
