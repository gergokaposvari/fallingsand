cmake_minimum_required(VERSION 3.30)
project(FallingSand)

set(CMAKE_CXX_STANDARD 26)

set(BOOST_ROOT "/opt/homebrew/Cellar/boost")
set(BOOST_INCLUDEDIR "/opt/homebrew/Cellar/boost/include")
set(BOOST_LIBRARYDIR "/opt/homebrew/Cellar/boost/lib")

find_package(Boost REQUIRED)

# Find SDL2
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)




add_executable(FallingSand main.cpp
        particles/Particle.h
        FSsimulation/Simulation.cpp
        FSsimulation/Simulation.h
        particles/types/PowderParticle.cpp
        particles/types/PowderParticle.h
        particles/types/State.h
        particles/EdgeParticle.h
        particles/types/powders/SandParticle.h
        particles/types/LiquidParticle.h
        particles/types/LiquidParticle.cpp
        particles/types/liquids/WaterParticle.h
        particles/types/SolidParticle.h
        particles/types/solids/StoneParticle.h
        FSsimulation/ParticleManager.h
        particles/types/solids/IceParticle.h
        particles/types/liquids/LavaParticle.h
        particles/types/solids/StoneParticle.cpp
        particles/types/liquids/LavaParticle.cpp
        particles/types/liquids/WaterParticle.cpp
        particles/types/solids/IceParticle.cpp
        FSsimulation/Chunk.h
        particles/types/FireParticle.cpp
        particles/types/FireParticle.h
        particles/types/Explosive.cpp
        particles/types/Explosive.h)

# Include SDL2 headers
target_include_directories(FallingSand PRIVATE ${SDL2_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

target_link_libraries(FallingSand PRIVATE ${Boost_LIBRARIES})


# Link SDL2 library
target_link_libraries(FallingSand PRIVATE SDL2::SDL2 SDL2_ttf::SDL2_ttf)