set(HANDLERS_SOURCES 
	${CMAKE_CURRENT_SOURCE_DIR}/IncludeHandler/IncludeHandler.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/VarDeclHandler/VarDeclHandler.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/StatementHandler/StatementHandler.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/FunctionDeclHandler/FunctionDeclHandler.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ClassDeclHandler/ClassDeclHandler.cpp
PARENT_SCOPE)

set(HANDLERS_HEADERS 
	${CMAKE_CURRENT_SOURCE_DIR}/IncludeHandler/IncludeHandler.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/VarDeclHandler/VarDeclHandler.hpp 
	${CMAKE_CURRENT_SOURCE_DIR}/StatementHandler/StatementHandler.hpp 
	${CMAKE_CURRENT_SOURCE_DIR}/FunctionDeclHandler/FunctionDeclHandler.hpp 
	${CMAKE_CURRENT_SOURCE_DIR}/ClassDeclHandler/ClassDeclHandler.hpp 
PARENT_SCOPE)
