project(Dominion_Main)

add_subdirectory(cards)
add_executable(Dominion
    main.cpp
    game.hpp
    player.hpp
    strategy.hpp
)
