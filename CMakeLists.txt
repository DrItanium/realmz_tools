cmake_minimum_required(VERSION 3.17)
project(realmz_tools)

set(CMAKE_CXX_STANDARD 17)

add_executable(dumpcaste CasteDecomposer.cpp BinaryManipulation.h Caste.cc Caste.h Ability.h
        Ability.cc CasteConditions.cc CasteConditions.h CasteDataBuffer.h
        SpecialAbilities.cc
        SpecialAbilities.h
        DRVAdjustments.cc
        DRVAdjustments.h
        )
add_executable(dumprace RaceDecomposer.cc RaceDecomposer.cc RaceData.cc RaceData.h RaceDataBuffer.h
        SpecialAbilities.cc
        SpecialAbilities.h
        DRVAdjustments.cc
        DRVAdjustments.h
        )
add_executable(realmz_keygen KeyGen.cc)