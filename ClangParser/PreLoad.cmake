set(CMAKE_MAKE_PROGRAM "C:/msys64/usr/bin/make.exe" CACHE STRING "CMAKE Make Program")
set(CMAKE_C_COMPILER "C:/msys64/mingw64/bin/gcc.exe" CACHE STRING "CMAKE Make Program")
set(CMAKE_CXX_COMPILER "C:/msys64/mingw64/bin/g++.exe" CACHE STRING "CMAKE Make Program")
set(CMAKE_LIBRARY_PATH "C:/msys64/mingw64/lib" CACHE STRING "CMAKE Library Path")
set(DCMAKE_LIBRARY_PATH "C:/msys64/mingw64/lib" CACHE STRING "CMAKE build Path")
set(CMAKE_GENERATOR "Unix Makefiles" CACHE INTERNAL "" FORCE)
set(CMAKE_BUILD_TYPE "Debug" CACHE INTERNAL "" FORCE)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG")
