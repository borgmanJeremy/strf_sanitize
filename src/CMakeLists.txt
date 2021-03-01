add_library(parser parse.cpp)

add_executable(parse main.cpp)
target_link_libraries(
  parse
  PRIVATE
  parser
  project_options
  project_warnings)
