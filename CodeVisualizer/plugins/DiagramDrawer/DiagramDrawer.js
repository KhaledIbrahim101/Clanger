//require("./plugins/DiagramDrawer/JsonReader.js");
//require("./plugins/DiagramDrawer/DiagramConfig.js");
function DrawActivityDiagram(jsonfile,container)
{
    // Use complete cell as highlight region
	mxConstants.ACTIVE_REGION = 1;
    // Checks if browser is supported
    if (!mxClient.isBrowserSupported())
    {
        // Displays an error message if the browser is
        // not supported.
        mxUtils.error('Browser is not supported!', 200, false);
    }
    else
    {
        var jbuffer = JSON.parse(jsonfile);
        var CodeTrace = ReadJson(jbuffer);
        InitializeLayout();
        var graph = ActivityDiagramConfig(container);
        //DrawFunction(0);
    }
}
function DrawLaneActivityDiagram(jsonfile,container)
{
    // Checks if browser is supported
    if (!mxClient.isBrowserSupported())
    {
        // Displays an error message if the browser is
        // not supported.
        mxUtils.error('Browser is not supported!', 200, false);
    }
    else
    {
        var graph = LaneActivityDiagramConfig(container);
        var model = graph.getModel();
        // Gets the default parent for inserting new cells. This
        // is normally the first child of the root (ie. layer 0).
        var parent = graph.getDefaultParent();

        // Adds cells to the model in a single step
        model.beginUpdate();
        try
        {
            var funcalls = [];
            var jbuffer = JSON.parse(jsonfile);
            var CodeTrace = ReadJson(jbuffer);
            InitializeLayout();
            for(var itrace = 0 ; itrace < layouts.length ; itrace++)
            {
                var Step, previousStep, labelsStack = [];
                var filename = "";
                var LaneHeight = 250, LaneWidth = 640, yLaneLocation = 40, yLaneIncrement = 50, xLaneLocation = 60, xLaneIncrement = 0;
                var CellHeight = 40, CellWidth = 0, yCellLocation = 40, yCellIncrement = 50, xCellLocation = 100, xCellIncrement = 0;
                filename = layouts[itrace].FileName.lastIndexOf("/") > 1 ? layouts[itrace].FileName.substring(layouts[itrace].FileName.lastIndexOf("/")+1) : layouts[itrace].FileName ;
                var pool = graph.insertVertex(parent, null, filename, 0, 0, 640, 0); 
                pool.setConnectable(false);    
  
                var currentFunction = layouts[itrace].Function;
                var lane = graph.insertVertex(pool, null, currentFunction.Name, yLaneLocation, xLaneLocation, LaneWidth, LaneHeight);
                lane.setConnectable(false);
                var start = graph.insertVertex(lane, null, 'Start', yCellLocation, xCellLocation, 30, 30, 'state');
                if(itrace != 0)
                {
                    for(var icall = 0 ; icall < funcalls.length ; icall++ )
                    {
                        if(funcalls[icall].value.indexOf(currentFunction.Name) > -1)
                        {
                            graph.insertEdge(lane, null, null, funcalls[icall], start);
                            break;
                        }
                    }
                }
                yCellLocation += (yCellIncrement + CellWidth);
                for(var ifstateCounter = 0 ; ifstateCounter < currentFunction.Statements.length; ifstateCounter++)
                {
                    var statement = currentFunction.Statements[ifstateCounter];
                    CellWidth = statement.Text.length < 10 ? 60 : statement.Text.length * 4;
                    switch(statement.Type)
                    {
                        case "Label":
                            LabelOffset = 80;
                            Step = graph.insertVertex(lane, null, statement.Text, yCellLocation , xCellLocation - LabelOffset, CellWidth, CellHeight, 'process');
                            break;
                        
                        case "Call Expression":
                            LabelOffset = 0;
                            Step = graph.insertVertex(lane, null, statement.Text, yCellLocation , xCellLocation - LabelOffset, CellWidth, CellHeight, 'process');
                            funcalls.push(Step);
                            break;
                        
                        default:
                            LabelOffset = 0;
                            Step = graph.insertVertex(lane, null, statement.Text, yCellLocation , xCellLocation - LabelOffset, CellWidth, CellHeight, 'process');
                            break;
                    }
                    Step.CellType = statement.Type;
                    graph.insertEdge(lane, null, null, previousStep, Step);
                    previousStep = Step;
                    if(statement.Type == "Label")
                    {

                    }
                    else
                    {
                        yCellLocation += (yCellIncrement + CellWidth);
                    }
                }
                yCellLocation += yCellIncrement;
                var end = graph.insertVertex(lane, null, 'End', yCellLocation, 40, 30, 30, 'end');
            }
        }
        finally
        {
            // Updates the display
            model.endUpdate();
        }
        
    }
}

function readFile(container)
{
    var allText = "";
    document.getElementById('inputfile') 
    .addEventListener('change', function() { 
      
    var fr=new FileReader(); 
    fr.onload=function(){ 
        DrawActivityDiagram(fr.result,container);
    } 
      
    fr.readAsText(this.files[0]); 
    }); 
    return allText;
}

function MainDraw(jsondt,container)
{
    jsondt = readFile(container);
}

function CustomData(value)
{
    this.value = value;
}

var codec = new mxObjectCodec(new CustomData());

codec.encode = function(enc, obj)
{
    var node = enc.document.createElement('CustomData');
    mxUtils.setTextContent(node, JSON.stringify(obj));
    
    return node;
};

codec.decode = function(dec, node, into)
{
    var obj = JSON.parse(mxUtils.getTextContent(node));
    obj.constructor = CustomData;
    
    return obj;
};

mxCodecRegistry.register(codec);