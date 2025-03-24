cmake_minimum_required(VERSION 3.30)
project(FallingSand)

set(CMAKE_CXX_STANDARD 26)

# Find SDL2
find_package(SDL2 REQUIRED)

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
        particles/types/solids/IceParticle.cpp)

# Include SDL2 headers
target_include_directories(FallingSand PRIVATE ${SDL2_INCLUDE_DIRS})

# Link SDL2 library
target_link_libraries(FallingSand PRIVATE ${SDL2_LIBRARIES})