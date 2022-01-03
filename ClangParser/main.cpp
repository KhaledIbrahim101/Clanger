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
#include <set>
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
#include <CodeElement.hpp>
#include <Tracer.hpp>
#include <fstream>
#include <filesystem>

/*
#include <boost/graph/connected_components.hpp>
#include <TGraph.hpp>
#include <boost/graph/graphviz.hpp>
//#include <boost/graph/strong_components.hpp>


#include <boost/graph/graphviz.hpp>
#include <boost/property_map/dynamic_property_map.hpp>
#include <boost/graph/graph_utility.hpp>
*/
using namespace clang;
using namespace clang::ast_matchers;
using namespace clang::driver;
using namespace clang::tooling;
using namespace boost;
namespace fs = std::filesystem;

std::set<CodeFile*> CodeDB ;
CodeFile* CF = NULL;
string rootpath = "";

ofstream outfile;
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

      DeclarationMatcher methMatch = cxxMethodDecl().bind("CXXMethodDecl");
      Matcher.addMatcher(methMatch, &HandlerForFunction);
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
      //string jsonpath = StringUtility::parent_path(CF->getPath()) + "\\json\\" + CF->getName() + ".json"; 
      string jsonpath = "";
      if(fs::is_directory(rootpath))
      {
        jsonpath = rootpath + "\\json\\" + CF->getName() + ".json"; 
      }
      else
      {
        jsonpath = StringUtility::parent_path(rootpath) + "\\" + CF->getName() + ".json"; 
      }
      CodeDB.insert(CF);
      pt::write_json(jsonpath, root); // to implement inside codeFile as public function
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
          string delimiter = ",";
          string cextension = extension;
          size_t pos = 0;
          std::string token;
          while ((pos = cextension.find(delimiter)) != std::string::npos) {
              token = cextension.substr(0, pos);
              if(StringUtility::ends_with(iter->path().string(),token))
					      listOfFiles.push_back(replace(iter->path().string(),oldc,newc));
              cextension.erase(0, pos + delimiter.length());
          }
          
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

void GenerateCodeDB(string proroot, string rootpath, string includePath, string extensions)
{
  vector<char*> files;
  vector<string> sfiles;
  
  if(fs::is_directory(rootpath))
  {
    fs::create_directory(rootpath+"//json");
    sfiles = getAllFilesInDir(rootpath,extensions);
    files.push_back(const_cast<char*>(proroot.c_str()));
    for(size_t i = 0; i < sfiles.size(); i++)
    {
      files.push_back(const_cast<char*>(sfiles[i].c_str()));
    }
    
  }
  else
  {
    files.push_back(const_cast<char*>(proroot.c_str()));
    //string temp = proroot + " " + rootpath + " -- " +  incPath;
    files.push_back(const_cast<char*>(rootpath.c_str()));
    //files.push_back(const_cast<char*>(proroot.c_str()));
  }
  files.push_back("--");
  size_t pos = 0;
  std::string token;
  string delimiter = ",";
  string incPaths[2];
  int i = 0 ;
  while ((pos = includePath.find(delimiter)) != std::string::npos) 
  {
      token = includePath.substr(0, pos);
      incPaths[i] = "-I" + token;
      files.push_back(const_cast<char*>(incPaths[i].c_str()));  
      includePath.erase(0, pos + delimiter.length());
      i++;
  }
  
  int lsize = (int)(files.size());
  CommonOptionsParser op(lsize,(const char **)files.data() , ToolSampleCategory);
  ClangTool Tool(op.getCompilations(), op.getSourcePathList());
  Tool.run(newFrontendActionFactory<MyFrontendAction>().get());  
}


vector<string> sfiles;
CodeFile* GetFileByName(string path)
{
  CodeFile* cf = new CodeFile();
  cf->setGID(0);
  bool found = (std::find(sfiles.begin(), sfiles.end(), path) != sfiles.end());
  if(found)
  {
    ifstream ifs(path);
    string content((std::istreambuf_iterator<char>(ifs)),
                  (std::istreambuf_iterator<char>()));
    cf->FromString("Json", content);
  }
  return cf;
} 
template <class I1, class I2>
bool have_common_element(I1 first1, I1 last1, I2 first2, I2 last2) {
    while (first1 != last1 && first2 != last2) {
        if (*first1 < *first2)
            ++first1;
        else if (*first2 < *first1)
            ++first2;
        else
            return true;
    }
    return false;
}
void LoadCodeDB(string rootpath,string extensions)
{
  //try
  {
    uint16_t CID = 0;
    time_t start0 = time(0);
    //set<GEdge> edges;
    ClearFile("results.txt");
    outfile.open("results.txt" , ios::app);
    int num_nodes = 0;
    CodeDB.clear();
    CodeElement* CE = new CodeElement();
    set<CodeElement*> Elements;
    string ElementNames;
    sfiles = getAllFilesInDir(rootpath,extensions);
    for(auto jfile : sfiles)
    {
      num_nodes++;
      CodeFile* sample = new CodeFile();
      ifstream ifs(jfile);
      string content((std::istreambuf_iterator<char>(ifs)),
                    (std::istreambuf_iterator<char>()));
      sample->FromString("Json", content);
      sample->setGID(CID);
      CodeDB.insert(sample);
      //add_vertex({sample->getGID(), custom_node{sample->getName(), 0}}, g);
      if(sample->getName().find(".h") != string::npos)
      {
        if(sample->getName().find(CE->getName()) != string::npos &&
          CE->getName() != "")
        {
          CE->AddCodeFile(sample);  
          CE->setGID(CID++);
          ElementNames += CE->getName();
          Elements.insert(CE);
          CE = new CodeElement();
          CE->setName("");
          CE->Files.clear();
        }
      }
      else if(sample->getName().find(".c") != string::npos)
      {
        if(sample->getName().find(CE->getName()) == string::npos &&
          CE->getName() != "")
        {
          CE->setGID(CID++);
          ElementNames += CE->getName();
          Elements.insert(CE);
          CE = new CodeElement();
          CE->setName("");
          CE->Files.clear();
        }
        CE->setName(StringUtility::remove_extension(sample->getName()));
        CE->AddCodeFile(sample);  
        for (auto elem : sample->getIncludes())
        {
          string hname = elem->getFileName().find(".h") != string::npos ? 
                         elem->getFileName() : elem->getFileName() + ".h";

          CE->IncludeNames += hname + ";";
        }
        for (auto elem : sample->getGlobalFunctions())
        {
          for (auto selem : elem->getStatements())
          {
            if(selem->getType() == "Call Expression")
            {
              CallExprSt* call = (CallExprSt*)selem;
              
              if(!call->getFuncDeclFile().empty())
              {
                string linkName = StringUtility::remove_extension(
                                    StringUtility::base_name(call->getFuncDeclFile()).erase(
                                    StringUtility::base_name(call->getFuncDeclFile()).find(":")));
                if(CE->ElementLinks.find(linkName) == string::npos)
                {
                  CE->ElementLinks +=  linkName + ";";
                }
              }
              free(call);
            }
          }
        }
      }     
      else
      {

      }
      //free(sample);
    }
    double seconds_since_start = difftime( time(0), start0);
    outfile<<"load Duration: "<<seconds_since_start/60<<" minutes."<<endl;
    CID = 1;
    list<CodeCluster*> Clusters;
    list<CodeCluster*> FinalClusters;
    time_t start = time(0);
    for (auto it : Elements)
    {
      if(it->Marked == false)
      {
        it->Marked = true;
        CodeCluster* CC = new CodeCluster();
        CC->GID = CID++;
        CC->Elements.insert(*it);
        string delimiter = ";";
        string cextension = it->ElementLinks;
        size_t pos = 0;
        std::string token;
        while ((pos = cextension.find(delimiter)) != std::string::npos && token.find(";") == string::npos) 
        {
          token = cextension.substr(0, pos);
          if(ElementNames.find(token) != string::npos && token != it->getName())
          {
            for (auto link : Elements)
            {
              if(link->Marked == false && link->getName() == token)
              {
                link->Marked = true;
                CC->Elements.insert(*link);
                break;
              }
            }
          }
          cextension.erase(0, pos + delimiter.length());
        }
        Clusters.push_back(CC);
      }
    }
    /*CodeCluster* HCC = new CodeCluster();
    HCC->Elements = HElements;
    Clusters.push_back(HCC);*/
    seconds_since_start = difftime( time(0), start);
    outfile<<"1st Clustering Duration: "<<seconds_since_start/60<<" minutes."<<endl;
    start = time(0);
    for(auto it1 : Clusters)
    {
      if(it1->Marked == false)
      {
        CodeCluster* CC = new CodeCluster();
        it1->Marked = true;
        CC->Elements = it1->Elements;
        for(auto it2 : Clusters)
        {
          if( have_common_element(it1->Elements.begin(),it1->Elements.end(),it2->Elements.begin(),it2->Elements.end()))
          {
            it2->Marked = true;
            CC->Elements.insert(it2->Elements.begin(),it2->Elements.end());
          }
        }
        FinalClusters.push_back(CC);
      }
    }
    seconds_since_start = difftime( time(0), start);
    outfile<<"2nd Clustering Duration: "<<seconds_since_start/60<<" minutes."<<endl;
    start = time(0);
    for(auto it : FinalClusters)
    {
      outfile<<"Cluster: "<<endl;
      for(auto element : it->Elements)
      {
        outfile<<"Element Name: "<<element.getName()<<endl;
        for(auto file : element.Files)
        {
          outfile<<file.getName()<<endl;
        }
      }
    }
    seconds_since_start = difftime( time(0), start0);
    outfile<<"Total Duration: "<<seconds_since_start/60<<" minutes."<<endl;
  }
  //catch(...)
  {

  }
}

int main(int argc, const char **argv) 
{
  
  string EntryFunction = "main";
  uint16_t src = StringUtility::str2int(EntryFunction.c_str());
  string command = "", extensions="", includePath = "";
  command = argv[1];
  rootpath = argv[2];
  includePath = argv[3];
  extensions = argv[4];
        
  if(argc > 3)
  {
    switch(StringUtility::str2int(command.c_str()))
    {
      case StringUtility::str2int("parse"):
      {
        GenerateCodeDB(argv[0], rootpath,includePath, extensions);
        //RunSpectralClustering("D:\\Work\\Projects\\git\\Clanger\\functionmap.txt");
        break;
      }

      case StringUtility::str2int("load"):
      {
        LoadCodeDB(rootpath,extensions);
        //RunSpectralClustering("D:\\Work\\Projects\\git\\Clanger\\functionmap.txt");
        
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
          LoadCodeDB(rootpath,extensions);
          CodeTrace* cs = new CodeTrace();
          cs->setName(argv[5]);
          cs->setFileName(argv[4]);
          cs->setFunctionName(argv[3]);
          Tracer::TraceFunction(cs);
          pt::ptree root = JsonUtility::GetJsonObject(cs->ToString("Json"));
          fs::create_directory(rootpath+"//trace");
          string jsonpath = rootpath + "\\trace\\" + cs->getName() + ".trc"; 
          //pt::write_json(jsonpath, root);
        
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
        CommonOptionsParser op(argc,argv, ToolSampleCategory);
        ClangTool Tool(op.getCompilations(), op.getSourcePathList());
        Tool.run(newFrontendActionFactory<MyFrontendAction>().get());  
        break;
      }
    }
  }
  return 0;
}
