set(CONTAINERS_SOURCES 
	${CMAKE_CURRENT_SOURCE_DIR}/Statements/Statement/Statement.cpp 
	
	${CMAKE_CURRENT_SOURCE_DIR}/Statements/DeclarationStatements/DeclSt/DeclSt.cpp 
	
	${CMAKE_CURRENT_SOURCE_DIR}/Statements/ExpressionStatements/BinaryOperatorSt/BinaryOperatorSt.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/Statements/ExpressionStatements/CallExprSt/CallExprSt.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/Statements/ExpressionStatements/OpaqueValueExprSt/OpaqueValueExprSt.cpp 
	
	${CMAKE_CURRENT_SOURCE_DIR}/Statements/JumpStatements/ReturnSt/ReturnSt.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Statements/JumpStatements/BreakSt/BreakSt.cpp 
	
	${CMAKE_CURRENT_SOURCE_DIR}/Statements/SelectionStatements/IfSt/IfSt.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/Statements/SelectionStatements/SwitchSt/SwitchSt.cpp 
	
	${CMAKE_CURRENT_SOURCE_DIR}/Statements/IterationStatements/ForST/ForSt.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/Statements/IterationStatements/DoSt/DoSt.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Statements/IterationStatements/WhileSt/WhileSt.cpp 
	
	${CMAKE_CURRENT_SOURCE_DIR}/Statements/CompoundStatements/IncludeSt/IncludeSt.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Statements/CompoundStatements/CompoundSt/CompoundSt.cpp  
	
	${CMAKE_CURRENT_SOURCE_DIR}/Entities/Variable/Variable.cpp 
	
	${CMAKE_CURRENT_SOURCE_DIR}/Entities/Function/Function.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/Entities/Violation/Violation.cpp 

	${CMAKE_CURRENT_SOURCE_DIR}/Entities/CodeFile/CodeFile.cpp 

	${CMAKE_CURRENT_SOURCE_DIR}/Entities/CodeTrace/CodeTrace.cpp 
PARENT_SCOPE)

set(CONTAINERS_HEADERS 
	${CMAKE_CURRENT_SOURCE_DIR}/Statements/Statement/Statement.hpp 
	
	${CMAKE_CURRENT_SOURCE_DIR}/Statements/DeclarationStatements/DeclSt/DeclSt.hpp 
	
	${CMAKE_CURRENT_SOURCE_DIR}/Statements/ExpressionStatements/BinaryOperatorSt/BinaryOperatorSt.hpp 
	${CMAKE_CURRENT_SOURCE_DIR}/Statements/ExpressionStatements/CallExprSt/CallExprSt.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Statements/ExpressionStatements/OpaqueValueExprSt/OpaqueValueExprSt.hpp 
	
	${CMAKE_CURRENT_SOURCE_DIR}/Statements/JumpStatements/ReturnSt/ReturnSt.hpp 
	${CMAKE_CURRENT_SOURCE_DIR}/Statements/JumpStatements/BreakSt/BreakSt.hpp 

	${CMAKE_CURRENT_SOURCE_DIR}/Statements/SelectionStatements/IfSt/IfSt.hpp 
	${CMAKE_CURRENT_SOURCE_DIR}/Statements/SelectionStatements/SwitchSt/SwitchSt.hpp 
	
	${CMAKE_CURRENT_SOURCE_DIR}/Statements/IterationStatements/ForST/ForSt.hpp 
	${CMAKE_CURRENT_SOURCE_DIR}/Statements/IterationStatements/DoSt/DoSt.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Statements/IterationStatements/WhileSt/WhileSt.hpp 
	
	${CMAKE_CURRENT_SOURCE_DIR}/Statements/CompoundStatements/IncludeSt/IncludeSt.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Statements/CompoundStatements/CompoundSt/CompoundSt.hpp 
	
	${CMAKE_CURRENT_SOURCE_DIR}/Entities/Variable/Variable.hpp 
	
	${CMAKE_CURRENT_SOURCE_DIR}/Entities/Function/Function.hpp 
	
	${CMAKE_CURRENT_SOURCE_DIR}/Entities/Violation/Violation.hpp
	
	${CMAKE_CURRENT_SOURCE_DIR}/Entities/CodeFile/CodeFile.hpp 

	${CMAKE_CURRENT_SOURCE_DIR}/Entities/CodeTrace/CodeTrace.hpp 
PARENT_SCOPE)
