find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
add_executable(runTests 
  tests.cpp
  cards/cardTest.cpp
  cards/cardFactoryTest.cpp
  cards/supplyTest.cpp
)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)