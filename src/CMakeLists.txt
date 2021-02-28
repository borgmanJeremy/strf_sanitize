add_executable(parse main.cpp)
target_link_libraries(
  parse
  PRIVATE
  project_options
  project_warnings)
