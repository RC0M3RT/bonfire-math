find_package(Catch2 CONFIG REQUIRED)

include(Catch)

add_library(catch_main OBJECT catch_main.cpp)
target_link_libraries(catch_main PUBLIC Catch2::Catch2 Catch2::Catch2WithMain)

SET(UNITTEST_SOURCES
    "math/vector3.cpp"
)

add_executable(unittests  ${UNITTEST_SOURCES})
target_link_libraries(unittests PRIVATE catch_main BonfireMath)
