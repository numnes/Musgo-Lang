cmake_minimum_required(VERSION 3.14)

project(MUSGO VERSION 1.0.0 LANGUAGES CXX)

# ---------------------- Include guards --------------------------
# TODO: Check if this is necessary
# ----------------------------------------------------------------

# ----------------------------- Add Musgo Lib ---------------------------

#Compiler
add_library(
  Compiler
  src/Compiler/Compiler.h
  src/Compiler/Compiler.cpp
  )

# Analizer
add_library(
  Analyzer
  src/Analyzer/Analyzer.h
  src/Analyzer/Analyzer.cpp
  )

#FrontEnd
add_library(
  FrontEnd
  src/FrontEnd/Lexical/Lexical.cpp
  src/FrontEnd/Lexical/Lexical.h
  src/FrontEnd/Syntactic/Syntatic.h
  src/FrontEnd/Syntactic/Syntatic.cpp
  src/FrontEnd/Types/Production.cpp
  src/FrontEnd/Types/Symbol.cpp
  src/FrontEnd/Utils/Utils.cpp
  ) 

# -----------------------------------------------------------------------------

# ------------------------------ Build and Include ----------------------------
target_include_directories(Compiler   PUBLIC src/Compiler)
target_include_directories(Analyzer   PUBLIC src/Analyzer)
target_include_directories(FrontEnd   PUBLIC src/FrontEnd)

add_executable(MUSGO src/main.cpp)
target_link_libraries(MUSGO
  PRIVATE Compiler
  PRIVATE Analyzer
  PRIVATE FrontEnd
  )
# -----------------------------------------------------------------------------
set_target_properties(MUSGO PROPERTIES CXX_STANDARD 17)


