project(space_tests)

  # Specify the source files
set(SOURCES
    CollectionTests.cpp
    main.cpp
    NormalizedVectorTests.cpp
    NormalizedXYVectorTests.cpp
    PointTests.cpp
    VectorTests.cpp
    XYPointTests.cpp 
    XYVectorTests.cpp
)

# Add the executable
add_executable(space_tests ${SOURCES})

# Include directories
target_include_directories(space_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)

add_test(NAME space_tests COMMAND space_tests)
