/*
1. install msys2 
2. C:\Python27;C:\msys64\mingw64\bin;C:\msys64\mingw32\bin
3. 
pacman -Syu
pacman -S mingw-w64-x86_64-gcc, 
pacman -S mingw-w64-x86_64-gdb, 
pacman -S mingw-w64-x86_64-cmake, 
pacman -S mingw-w64-x86_64-make,
pacman -S mingw-w64-x86_64-boost,
pacman -S mingw-w64-x86_64-clang
<msys2_path>/mingw64/include/c++/9.2.0/bits/fs_path.h.
At lines 666-692, there is a definition of class filesystem_error. It has to be moved up to line 614, to be right above the definition of u8path().

4. update gdb printer script and gdbinit file in "C:\msys64\mingw64\etc"
g++ main.cpp -g -fno-rtti 
-lclangAST -lclangAnalysis -lclangBasic -lclangDriver -lclangEdit -lclangFrontend -lclangFrontendTool -lclangLex -lclangParse -lclangSema -lclangEdit -lclangASTMatchers -lclangRewrite -lclangRewriteFrontend -lclangStaticAnalyzerFrontend -lclangStaticAnalyzerCheckers -lclangStaticAnalyzerCore -lclangSerialization -lclangToolingCore -lclangTooling 
$(C:/msys64/mingw64/bin/llvm-config --cxxflags) 
$(llvm-config --cxxflags --ldflags --libs --system-libs) -lversion -o main.exe

cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . > output_file.txt
./clang-parser.exe ../test/test2.h ../test/test2.cpp ../test/test1.cpp
./clang-parser.exe "C:\Archi\Bot\Projects\ACTIC5G\code\ACTIC5G\src"

$ clang++ -S -emit-llvm main1.cpp -o - | opt -analyze -dot-callgraph
$ dot -Tpng -ocallgraph.png callgraph.dot
$ clang -cc1 -ast-dump "D:\Work\My Projects\all\APP_Blr.c"
clang -Xclang -I -ast-dump "D:\Work\Projects\all\testcplusplus.h"
clang-check  "D:\Work\Projects\all\testcplusplus.h" -ast-dump --
clang -Xclang -ast-dump -ast-dump-filter="APP_vidManageDataVsConnectionState" -I"C:\Archi\Bot\Projects\MKW35\code\bigpang\inc" "C:\Archi\Bot\Projects\MKW35\code\bigpang\src\APP_Blr.c"
  gpg --keyserver hkp://p80.pool.sks-keyservers.net:80  --search-keys alexpux@gmail.com
pacman -U https://repo.msys2.org/mingw/x86_64/mingw-w64-x86_64-gdb-9.2-1-any.pkg.tar.zst version gdb 9.2

*/

#include <string>
#include <memory>
#include <set>
#include <iterator>
#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/AST/ExternalASTSource.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "llvm/Support/raw_ostream.h"
#include <IncludeHandler.hpp>
#include <VarDeclHandler.hpp>
#include <ClassDeclHandler.hpp>
#include <Tracer.hpp>
#include <filesystem>


using namespace clang;
using namespace clang::ast_matchers;
using namespace clang::driver;
using namespace clang::tooling;

namespace fs = std::filesystem;

set<CodeFile> CodeDB ;
CodeFile* CF = NULL;

void PrintAll(string Path)
{
	string temp = "";
	ofstream outfile ;
	CodeFile* comp;
	outfile.open(Path , ios::app);
	for (set<CodeFile>::iterator it = CodeDB.begin(); it != CodeDB.end(); ++it)
	{
		comp = new CodeFile();
		comp = (CodeFile*)&(*it);
		temp = comp->ToString("");
		outfile << temp;
	}
	outfile.close();
}
void PrintItem(CodeFile CF,string Path)
{
	string temp = "";
	ofstream outfile ;

	outfile.open(Path, ios::app);

	temp = CF.ToString("Json");
	outfile << temp;
	
	outfile.close();
}

void ClearFile(string path)
{
  std::ofstream ofs;
  ofs.open(path, std::ofstream::out | std::ofstream::trunc);
  ofs.close();
}

static llvm::cl::OptionCategory ToolSampleCategory("Sample Category");

// Implementation of the ASTConsumer interface for reading an AST produced
// by the Clang parser. It registers a couple of matchers and runs them on
// the AST.
class MyASTConsumer : public ASTConsumer 
{
  public:
    MyASTConsumer(Rewriter &R) : /*HandlerForIf(R), HandlerForFor(R) ,*/ HandlerForFunction(R), HandlerForClass(R)
    {
      DeclarationMatcher DeclMatch = varDecl().bind("VarDecl");
      Matcher.addMatcher(DeclMatch, &HandlerForVarDecl);
      
      DeclarationMatcher funMatch = functionDecl(isDefinition()).bind("FunctionDecl");
      Matcher.addMatcher(funMatch, &HandlerForFunction);

      DeclarationMatcher classMatch = cxxRecordDecl().bind("CXXRecordDecl");
      Matcher.addMatcher(classMatch, &HandlerForClass);
      //Matcher.addMatcher(funMatch, &HandlerForFunction);
      /*StatementMatcher loopMatch = forStmt(hasLoopInit(declStmt(hasSingleDecl(
                      varDecl(hasInitializer(integerLiteral(equals(0))))
                          .bind("initVarName")))),
                  hasIncrement(unaryOperator(
                      hasOperatorName("++"),
                      hasUnaryOperand(declRefExpr(to(
                          varDecl(hasType(isInteger())).bind("incVarName")))))),
                hasCondition(binaryOperator(
                      hasOperatorName("<"),
                      hasLHS(ignoringParenImpCasts(declRefExpr(to(
                          varDecl(hasType(isInteger())).bind("condVarName"))))),
                      hasRHS(expr(hasType(isInteger())))))).bind("forLoop");

      Matcher.addMatcher(loopMatch, &HandlerForFor);*/
      // Add a simple matcher for finding 'if' statements.
      //StatementMatcher ifMatch = ifStmt().bind("ifStmt"); 
      //Matcher.addMatcher(ifMatch, &HandlerForIf);

    }

    void HandleImplicitImportDecl(ImportDecl *D) override 
    {
      D->dump();
      llvm::outs() << "lol";
    }

    void HandleTranslationUnit(ASTContext &Context) override 
    {
      // Run the matchers when we have the whole TU parsed.
      Matcher.matchAST(Context);
    }

  private:
    //IfStmtHandler HandlerForIf;
    VarDeclHandler HandlerForVarDecl;
    //IncrementForLoopHandler HandlerForFor;
    FunctionDeclHandler HandlerForFunction;
    ClassDeclHandler HandlerForClass;
    MatchFinder Matcher;
};


// For each source file provided to the tool, a new FrontendAction is created.
class MyFrontendAction : public ASTFrontendAction 
{
  public:
    MyFrontendAction() {}

    void EndSourceFileAction() override 
    {
      /*SourceManager &SM = TheRewriter.getSourceMgr();
      llvm::errs() << "** EndSourceFileAction for: "
                    << SM.getFileEntryForID(SM.getMainFileID())->getName() << "\n";

      // Now emit the rewritten buffer.
      TheRewriter.getEditBuffer(SM.getMainFileID()).write(llvm::outs());*/
      llvm::outs()<<"end of file\n";
      
      string jsonbuffer = CF->ToString("Json") ;
      pt::ptree root = JsonUtility::GetJsonObject(jsonbuffer);
      string jsonpath = StringUtility::parent_path(CF->getPath()) + "\\json\\" + StringUtility::remove_extension(CF->getName()) + ".json"; 
      pt::write_json(jsonpath, root);
      CF = new CodeFile();
    }

    std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &CI, StringRef file) override 
    {
      CF = new CodeFile();
      CF->setPath((string)file);
      CF->setName((string)StringUtility::base_name(file));
      llvm::errs() << "** Creating AST consumer for: " << file << "\n";
      TheRewriter.setSourceMgr(CI.getSourceManager(), CI.getLangOpts());
      
      std::unique_ptr<IncludeHandler> find_includes_callback(new IncludeHandler());
      Preprocessor &pp = CI.getPreprocessor();
      pp.addPPCallbacks(std::move(find_includes_callback));
      return std::make_unique<MyASTConsumer>(TheRewriter);
    }

  private:
    Rewriter TheRewriter;
};

///// CUSTOM TESTS ////

class ASTAction : public ASTConsumer 
{
  public:
      ASTAction() = default;
};

class PPObserver : public PPCallbacks 
{
  public:
      PPObserver(const SourceManager& sm) : SM(sm) {}
        
      virtual void FileChanged (SourceLocation Loc, FileChangeReason  Reason,SrcMgr::CharacteristicKind FileType, FileID PrevFID = FileID()) 
      {
        llvm::outs() << "Found a changefile for preprocessor " << Reason << " " << FileType << " " <<  '\n';
        llvm::outs() << SM.getBuffer(PrevFID)->getBuffer();
        llvm::outs() << "\n\n";
      }
      const SourceManager& SM;    
};

class PPAction : public ASTFrontendAction 
{
   protected:
      virtual std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance& compiler,llvm::StringRef /* dummy */) 
      {                                       
        std::unique_ptr<PPObserver> ppO(new PPObserver(compiler.getSourceManager()));    
        compiler.getPreprocessor().addPPCallbacks(std::move(ppO) );
        //compiler.getPreprocessor().addCommentHandler(preprocessor_consumer);
        std::unique_ptr<ASTAction> aaA(new ASTAction());

        return std::move(aaA);
      }
};

int QueueFiles(const char* path,char ** files)
{
  int i = 0;
  for (const auto & entry : fs::directory_iterator(path))
  {
    strcpy(files[i], entry.path().string().c_str());
    i++;
  }
  return i;
}
std::string replace(std::string str, const std::string from, const std::string to) {
    if(from.empty())
        return str;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
    return str;
}
/*
 * Get the list of all files in given directory and its sub directories.
 *
 * Arguments
 * 	dirPath : Path of directory to be traversed
 * 	dirSkipList : List of folder names to be skipped
 *
 * Returns:
 * 	vector containing paths of all the files in given directory and its sub directories
 *
 */
std::vector<std::string> getAllFilesInDir(const std::string &dirPath, const std::string &extension, 	const std::vector<std::string> dirSkipList = { })
{
 
	// Create a vector of string
	std::vector<std::string> listOfFiles;
	try {
		// Check if given path exists and points to a directory
		if (fs::exists(dirPath) && fs::is_directory(dirPath))
		{
			// Create a Recursive Directory Iterator object and points to the starting of directory
			fs::recursive_directory_iterator iter(dirPath);
 
			// Create a Recursive Directory Iterator object pointing to end.
			fs::recursive_directory_iterator end;
 
			// Iterate till end
			while (iter != end)
			{
				// Check if current entry is a directory and if exists in skip list
				if (fs::is_directory(iter->path()) &&
						(std::find(dirSkipList.begin(), dirSkipList.end(), iter->path().filename()) != dirSkipList.end()))
				{
					// Skip the iteration of current directory pointed by iterator
#ifdef USING_BOOST
					// Boost Fileystsem  API to skip current directory iteration
					iter.no_push();
#else
					// c++17 Filesystem API to skip current directory iteration
					iter.disable_recursion_pending();
#endif
				}
				else
				{
					// Add the name in vector
          string oldc = "/", newc = "\\";
          if(iter->path().string().find(extension) != string::npos)
					  listOfFiles.push_back(replace(iter->path().string(),oldc,newc));
				}
 
				error_code ec;
				// Increment the iterator to point to next entry in recursive iteration
				iter.increment(ec);
				if (ec) {
					std::cerr << "Error While Accessing : " << iter->path().string() << " :: " << ec.message() << '\n';
				}
			}
		}
	}
	catch (std::system_error & e)
	{
		std::cerr << "Exception :: " << e.what();
	}
	return listOfFiles;
}

vector<char*> ConvertVectorTo2DArray(vector<string> sfiles)
{
  vector<char*> files;
  files.reserve(sfiles.size());
  for(size_t i = 0; i < sfiles.size(); i++)
  {
    files.push_back(const_cast<char*>(sfiles[i].c_str()));
  }
  return files;
}

void GenerateCodeDB(string proroot, string rootpath, string extensions)
{
  vector<string> sfiles;
  fs::create_directory(rootpath+"//json");
  sfiles = getAllFilesInDir(rootpath,extensions);
  sfiles.push_back(proroot.c_str());
  vector<char*> files;
  files.reserve(sfiles.size());
  for(size_t i = 0; i < sfiles.size(); i++)
  {
    files.push_back(const_cast<char*>(sfiles[i].c_str()));
  }
  //files = ConvertVectorTo2DArray(sfiles);
  int lsize = (int)(files.size());
  CommonOptionsParser op(lsize,(const char **)files.data() , ToolSampleCategory);
  ClangTool Tool(op.getCompilations(), op.getSourcePathList());
  Tool.run(newFrontendActionFactory<MyFrontendAction>().get());  
}

void LoadCodeDB(string rootpath)
{
  CodeDB.clear();
  vector<string> sfiles;
  sfiles = getAllFilesInDir(rootpath,".json");
  for(auto jfile : sfiles)
  {
    CodeFile* sample = new CodeFile();
    ifstream ifs(jfile);
    string content((std::istreambuf_iterator<char>(ifs)),
                  (std::istreambuf_iterator<char>()));
    sample->FromString("Json", content);
    CodeDB.insert(*sample);
  }
}

int main(int argc, const char **argv) 
{
  string command = "", rootpath ="", extensions="";
  
  if(argc > 3)
  {
    command = argv[1];
    rootpath = argv[2];
    extensions = argv[3];
    switch(StringUtility::str2int(command.c_str()))
    {
      case StringUtility::str2int("parse"):
      {
        GenerateCodeDB(argv[0], rootpath,extensions);
        break;
      }

      case StringUtility::str2int("load"):
      {
        LoadCodeDB(rootpath);
        break;
      }

      case StringUtility::str2int("check"):
      {
        //CheckCodeDB(rootpath);
        break;
      }

      case StringUtility::str2int("trace"):
      {
        if(argc >= 5)
        {
          LoadCodeDB(rootpath);
          CodeTrace* cs = new CodeTrace();
          cs->setName(argv[5]);
          cs->setFileName(argv[4]);
          cs->setFunctionName(argv[3]);
          Tracer::TraceFunction(cs);
          pt::ptree root = JsonUtility::GetJsonObject(cs->ToString("Json"));
          fs::create_directory(rootpath+"//trace");
          string jsonpath = rootpath + "\\trace\\" + cs->getName() + ".trc"; 
          pt::write_json(jsonpath, root);
        
        }
        
        // services
        // 1. tracer
        // 2. safety checker
        // 3. assessors
          // 3.1 misra
          // 3.2 design best practises
          // 3.3 Coding rules (reference from coding best practises google powerpoint)
        break;
      }
      
      default:
      {
        llvm::outs()<< "This command is not recognized!\n";
        break;
      }
    }
  }
  return 0;
}
