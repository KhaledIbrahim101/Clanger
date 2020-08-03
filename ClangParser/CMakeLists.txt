set(CMAKE_MAKE_PROGRAM "C:/msys64/usr/bin/make.exe" CACHE STRING "CMAKE Make Program")
set(CMAKE_C_COMPILER "C:/msys64/mingw64/bin/clang.exe" CACHE STRING "CMAKE Make Program")
set(CMAKE_CXX_COMPILER "C:/msys64/mingw64/bin/clang++.exe" CACHE STRING "CMAKE Make Program")
set(CMAKE_LIBRARY_PATH "C:/msys64/mingw64/lib" CACHE STRING "CMAKE Library Path")
set(DCMAKE_LIBRARY_PATH "C:/msys64/mingw64/lib" CACHE STRING "CMAKE build Path")

project(clang-parser)
cmake_minimum_required(VERSION 3.12)
add_definitions(-std=c++17) 

set(LLVM_SRC_PATH "C:/msys64/mingw64/include" CACHE STRING "LLVM sources path")
set(LLVM_BUILD_PATH "C:/msys64/mingw64/lib" CACHE STRING "LLVM build path")
set(LLVM_BIN_PATH "C:/msys64/mingw64/bin" CACHE STRING "LLVM binaries path")

execute_process(COMMAND ${LLVM_BIN_PATH}/llvm-config.exe --cxxflags
  OUTPUT_VARIABLE LLVM_CXXFLAGS
  OUTPUT_STRIP_TRAILING_WHITESPACE)
string(REGEX REPLACE "\n" " " LLVM_CXXFLAGS ${LLVM_CXXFLAGS}) # Also strips newlines
set(LLVM_CXXFLAGS "${LLVM_CXXFLAGS} -std=c++17 -fexceptions")
set(LLVM_CXXFLAGS "${LLVM_CXXFLAGS} -frtti -ferror-limit=0")
execute_process(COMMAND ${LLVM_BIN_PATH}/llvm-config.exe --ldflags --libs --system-libs 
  OUTPUT_VARIABLE LLVM_LDFLAGS 
  OUTPUT_STRIP_TRAILING_WHITESPACE)
string(REGEX REPLACE "\n" " " LLVM_LDFLAGS ${LLVM_LDFLAGS}) # Also strips newlines
set(CMAKE_CXX_FLAGS "-ferror-limit=0")
set(CLANG_INCLUDES ${LLVM_SRC_PATH})
 
set(CLANG_LIBS
  -Wl,--start-group
  clangAST
  clangAnalysis
  clangBasic
  clangDriver
  clangEdit
  clangFrontend
  clangFrontendTool
  clangLex
  clangParse
  clangSema
  clangEdit
  clangASTMatchers
  clangRewrite
  clangRewriteFrontend
  clangStaticAnalyzerFrontend
  clangStaticAnalyzerCheckers
  clangStaticAnalyzerCore
  clangSerialization
  clangToolingCore
  clangTooling
  -Wl,--end-group)

add_subdirectory(Libraries)
add_subdirectory(Containers)
add_subdirectory(Handlers)
add_subdirectory(Services)

include_directories(${CLANG_INCLUDES})

include_directories(Libraries/StringUtility)
include_directories(Libraries/JsonUtility)

include_directories(Containers/Statements/Statement)

include_directories(Containers/Statements/DeclarationStatements/DeclSt)

include_directories(Containers/Statements/ExpressionStatements/CallExprSt)
include_directories(Containers/Statements/ExpressionStatements/BinaryOperatorSt)
include_directories(Containers/Statements/ExpressionStatements/OpaqueValueExprSt)

include_directories(Containers/Statements/JumpStatements/ReturnSt)
include_directories(Containers/Statements/JumpStatements/BreakSt)

include_directories(Containers/Statements/SelectionStatements/IfSt)
include_directories(Containers/Statements/SelectionStatements/SwitchSt)

include_directories(Containers/Statements/IterationStatements/ForSt)
include_directories(Containers/Statements/IterationStatements/DoSt)
include_directories(Containers/Statements/IterationStatements/WhileSt)

include_directories(Containers/Statements/CompoundStatements/IncludeSt)
include_directories(Containers/Statements/CompoundStatements/CompoundSt)

include_directories(Containers/Entities/Variable)
include_directories(Containers/Entities/Function)
include_directories(Containers/Entities/Violation)
include_directories(Containers/Entities/CodeFile)
include_directories(Containers/Entities/CodeStage)


include_directories(Handlers/IncludeHandler)
include_directories(Handlers/VarDeclHandler)
include_directories(Handlers/StatementHandler)
include_directories(Handlers/FunctionDeclHandler)

include_directories(Services/Tracer)

list (APPEND LIBRARIES_SOURCES ${CONTAINERS_SOURCES})
list (APPEND LIBRARIES_SOURCES ${HANDLERS_SOURCES})
list (APPEND LIBRARIES_SOURCES ${SERVICES_SOURCES})

add_executable(${PROJECT_NAME} ${LIBRARIES_SOURCES})

link_directories(${LLVM_BUILD_PATH})

set_target_properties(${PROJECT_NAME} PROPERTIES
  COMPILE_FLAGS ${LLVM_CXXFLAGS})

message( ${LLVM_LDFLAGS} )
# These need to be placed (both libraries and flags) at the end (do not use
# LINK_FLAGS since they're inserted before the .o obj files to link and thus
# since ld is positional no symbols are available when actual objs ask them)

#Important Note: They have to be in order!!!
target_link_libraries(${PROJECT_NAME} ${CLANG_LIBS})
target_link_libraries(${PROJECT_NAME} ${LLVM_LDFLAGS})
target_link_libraries(${PROJECT_NAME} version)

