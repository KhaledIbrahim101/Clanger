#include "clang/Lex/PPCallbacks.h"
#include <string>
#ifndef  CODEFILE_H  
#include <CodeFile.hpp>
#endif

using namespace clang;
using namespace std;
class IncludeHandler : public PPCallbacks
{
public:
  void InclusionDirective(SourceLocation HashLoc,
                          const Token &IncludeTok,
                          StringRef FileName,
                          bool IsAngled,
                          CharSourceRange FilenameRange,
                          const FileEntry *File,
                          StringRef SearchPath,
                          StringRef RelativePath,
                          const Module *Imported,
                          SrcMgr::CharacteristicKind FileType)  override;
};