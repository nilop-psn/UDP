cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(UDP VERSION 0.5.0)
message(STATUS "[Project] ${PROJECT_NAME}")

message(STATUS "find package: UCMake 0.5.0")
find_package(UCMake 0.5.0 QUIET)
if(NOT UCMake_FOUND)
  message(STATUS "UCMake 0.5.0 not found")
  message(STATUS "fetch: ${_address} 0.5.0")
  set(_address "https://github.com/Ubpa/UCMake")
  FetchContent_Declare(
    UCMake
    GIT_REPOSITORY ${_address}
    GIT_TAG "0.5.0"
  )
  FetchContent_MakeAvailable(UCMake)
  message(STATUS "UCMake 0.5.0 build done")
endif()

Ubpa_AddDep(UTemplate 0.4.0)

Ubpa_AddSubDirsRec(include)
Ubpa_AddSubDirsRec(src)

Ubpa_Export(DIRECTORIES "include")
