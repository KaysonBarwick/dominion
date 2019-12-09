find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
add_executable(runTests 
  tests.cpp
  
  cards/cardTest.cpp
  cards/cardFactoryTest.cpp
  cards/supplyTest.cpp

  strategy/inputTest.cpp
  strategy/moneyTest.cpp
  strategy/randomTest.cpp

  playerTest.cpp
)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)