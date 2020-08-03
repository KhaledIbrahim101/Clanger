#include "IncludeHandler.hpp"
#include "IncludeSt.hpp"
extern CodeFile* CF;
void IncludeHandler::InclusionDirective(SourceLocation HashLoc,
    const Token &IncludeTok,
    StringRef FileName,
    bool IsAngled,
    CharSourceRange FilenameRange,
    const FileEntry *File,
    StringRef SearchPath,
    StringRef RelativePath,
    const Module *Imported,
    SrcMgr::CharacteristicKind FileType)
{
    IncludeSt* include = new IncludeSt();
    include->setFileName(FileName.str());
    include->setText("#include <" + FileName.str() + ">");
    include->setType("Include");
    switch(FileType)
    {
        case SrcMgr::CharacteristicKind::C_User:
            include->setIncludeType("C_User");
            break;

        case SrcMgr::CharacteristicKind::C_User_ModuleMap:
            include->setIncludeType("C_User_ModuleMap");
            break;
        
        case SrcMgr::CharacteristicKind::C_System:
            include->setIncludeType("C_System");
            break;

        case SrcMgr::CharacteristicKind::C_ExternCSystem:
            include->setIncludeType("C_ExternCSystem");
            break;

        case SrcMgr::CharacteristicKind::C_System_ModuleMap:
            include->setIncludeType("C_System_ModuleMap");
            break;

        default:
            include->setIncludeType("Not_Handled");
            break;
    }
    CF->AddInclude(include);
}
