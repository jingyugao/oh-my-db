cmake_minimum_required(VERSION 3.0.0)
project(oh-my-db VERSION 0.1.0)

include(CTest)
enable_testing()
aux_source_directory(. DIRSRCS)
add_executable(oh-my-db )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
