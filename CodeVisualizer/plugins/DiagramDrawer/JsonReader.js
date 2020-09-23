var layouts = [];
var cbranches = [];
function CodeStatement()
{
    this.Text = "";
    this.Type = "";
}
function CodeFunction()
{
    this.Name = "";
    this.iCounter = 0;
    this.Statements = [];
}
function CodeLayout()
{
    this.FileName = "";
    this.Function = new CodeFunction();
    this.FunctionPath = [];
}
function CodeTrace()
{
    this.Name = "";
    this.Path = "";
    this.Function = new CodeFunction();
    this.Branches = [];
}

function InitializeLayout()
{
    for(var ic = 0 ; ic < cbranches.length ; ic++)
    {
        var CT = cbranches[ic];
        layout = new CodeLayout();
        layout.FileName = CT.FileName;
        layout.Function = CT.Function;
        var funs = CT.Path.split(">");
        for(var ifun = 0 ; ifun < funs.length ; ifun++)
        {
            var fun = new CodeFunction();
            fun.Name = funs[ifun];
            for(var icc = 0 ; icc < cbranches.length ; icc++)
            {
                if(cbranches[icc].Function.Name == fun.Name)
                {
                    fun.iCounter = icc;
                    break;
                }
            }   
            layout.FunctionPath.push(fun);
        }
        layouts.push(layout);
    }
}

function ReadMainBranch(json)
{
    function ReadBranch(json,path)
    {
        var CT = new CodeTrace();
        CT.Name = json["Name"];
        CT.FileName = json["File"];
        CT.Function.Name = json["Function"];
        CT.Path += (path.length == 0 ? '' : (path + '>')) + CT.Function.Name;
        var statements = json.Statements;
        for (var i = 0 ; i < statements.length; i++) 
        {
            var statement = new CodeStatement();
            statement.Text = statements[i].Text;
            statement.Type = statements[i].Type;
            CT.Function.Statements.push(statement);
        }
        cbranches.push(CT);
        var branches = json.Branches;
        for (var i = 0; i < branches.length; ++i) 
        {
            CT.Branches.push(ReadBranch(branches[i],CT.Path));
        }
        
        return CT;
    }
    return ReadBranch(json,'');
}

function ReadJson(json)
{
    return ReadMainBranch(json);
}