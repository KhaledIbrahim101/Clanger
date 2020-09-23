function GetVertexStyle(elemType,graph)
{
    // Changes the default vertex style in-place
    var style = graph.getStylesheet().getDefaultVertexStyle();
    style[mxConstants.STYLE_VERTICAL_ALIGN] = 'middle';
    style[mxConstants.STYLE_FONTSIZE] = 11;
    style[mxConstants.STYLE_STARTSIZE] = 22;
    style[mxConstants.STYLE_HORIZONTAL] = false;
    style[mxConstants.STYLE_FONTCOLOR] = 'black';
    style[mxConstants.STYLE_STROKECOLOR] = 'black';
    style[mxConstants.STYLE_WHITE_SPACE] = 'wrap';
    delete style[mxConstants.STYLE_FILLCOLOR];
    style = mxUtils.clone(style);
    switch(elemType)
    {
        case "Call Expression":
            style[mxConstants.STYLE_SHAPE] = mxConstants.SHAPE_RECTANGLE;
            style[mxConstants.STYLE_FONTSIZE] = 10;
            style[mxConstants.STYLE_ROUNDED] = true;
            style[mxConstants.STYLE_HORIZONTAL] = true;
            style[mxConstants.STYLE_VERTICAL_ALIGN] = 'middle';
            style[mxConstants.STYLE_FILLCOLOR] = '#C3D9FF';
            delete style[mxConstants.STYLE_STARTSIZE];
            style[mxConstants.STYLE_LABEL_BACKGROUNDCOLOR] = 'none';
            break;

        case "Crossover":
            style = graph.getStylesheet().getDefaultEdgeStyle();
            style[mxConstants.STYLE_EDGE] = mxEdgeStyle.ElbowConnector;
            style[mxConstants.STYLE_ENDARROW] = mxConstants.ARROW_BLOCK;
            style[mxConstants.STYLE_ROUNDED] = true;
            style[mxConstants.STYLE_FONTCOLOR] = 'black';
            style[mxConstants.STYLE_STROKECOLOR] = 'black';
            style[mxConstants.STYLE_DASHED] = true;
            style[mxConstants.STYLE_ENDARROW] = mxConstants.ARROW_OPEN;
            style[mxConstants.STYLE_STARTARROW] = mxConstants.ARROW_OVAL;
            break;

        case "Action":
            style[mxConstants.STYLE_SHAPE] = mxConstants.SHAPE_RECTANGLE;
            style[mxConstants.STYLE_FONTSIZE] = 10;
            style[mxConstants.STYLE_ROUNDED] = true;
            style[mxConstants.STYLE_HORIZONTAL] = true;
            style[mxConstants.STYLE_VERTICAL_ALIGN] = 'middle';
            delete style[mxConstants.STYLE_STARTSIZE];
            style[mxConstants.STYLE_LABEL_BACKGROUNDCOLOR] = 'none';
            break;

        case "HeaderFile":
            style[mxConstants.STYLE_SHAPE] = mxConstants.SHAPE_RECTANGLE;
            style[mxConstants.STYLE_FONTSIZE] = 14;
            style[mxConstants.STYLE_HORIZONTAL] = true;
            style[mxConstants.STYLE_VERTICAL_ALIGN] = 'middle';
            style[mxConstants.STYLE_FILLCOLOR] = '#4C92CC';
            style[mxConstants.STYLE_FONTCOLOR] = 'white';
            style[mxConstants.STYLE_STROKECOLOR] = 'white';
            style[mxConstants.STYLE_LABEL_BACKGROUNDCOLOR] = 'none';
            break;
        
        case "HeaderFunction":
            style[mxConstants.STYLE_SHAPE] = mxConstants.SHAPE_RECTANGLE;
            style[mxConstants.STYLE_FONTSIZE] = 14;
            style[mxConstants.STYLE_HORIZONTAL] = true;
            style[mxConstants.STYLE_VERTICAL_ALIGN] = 'middle';
            style[mxConstants.STYLE_FILLCOLOR] = '#87B9E1';
            style[mxConstants.STYLE_FONTCOLOR] = 'white';
            style[mxConstants.STYLE_STROKECOLOR] = 'white';
            style[mxConstants.STYLE_LABEL_BACKGROUNDCOLOR] = 'none';
            break;

        case "State":
            style[mxConstants.STYLE_SHAPE] = mxConstants.SHAPE_ELLIPSE;
            style[mxConstants.STYLE_PERIMETER] = mxPerimeter.EllipsePerimeter;
            delete style[mxConstants.STYLE_ROUNDED];
            break;
        
        case "Condition":
            style[mxConstants.STYLE_SHAPE] = mxConstants.SHAPE_RHOMBUS;
            style[mxConstants.STYLE_PERIMETER] = mxPerimeter.RhombusPerimeter;
            style[mxConstants.STYLE_HORIZONTAL] = true;
            style[mxConstants.STYLE_VERTICAL_ALIGN] = 'middle';
            break;
        
        case "End":
            style[mxConstants.STYLE_SHAPE] = mxConstants.SHAPE_DOUBLE_ELLIPSE;
            style[mxConstants.STYLE_PERIMETER] = mxPerimeter.EllipsePerimeter;
            style[mxConstants.STYLE_SPACING_TOP] = 28;
            style[mxConstants.STYLE_FONTSIZE] = 14;
            style[mxConstants.STYLE_FONTSTYLE] = 1;
            delete style[mxConstants.STYLE_SPACING_RIGHT];
            break;
    }
    
    return style;
}

function GetEdgeStyle(elemType,graph)
{
    var style = graph.getStylesheet().getDefaultEdgeStyle();
    style[mxConstants.STYLE_EDGE] = mxEdgeStyle.ElbowConnector;
    style[mxConstants.STYLE_ENDARROW] = mxConstants.ARROW_BLOCK;
    style[mxConstants.STYLE_ROUNDED] = true;
    style[mxConstants.STYLE_FONTCOLOR] = 'black';
    style[mxConstants.STYLE_STROKECOLOR] = 'black';
    
    switch(elemType)
    {
        default:
           
            break;
    }
    return style;
}
function ActivityDiagramConfig(container)
{
    // Disables built-in context menu
    mxEvent.disableContextMenu(document.body);
     // Creates a wrapper editor around a new graph inside
    // the given container using an XML config for the
    // keyboard bindings
    // Creates the graph inside the given container
    var graph = new mxGraph(container);
    graph.setEnabled(true);
    graph.setTooltips(true);
    graph.constrainChildren = false;
    graph.extendParents = false;
	graph.extendParentsOnAdd = false;

    // Enables HTML labels as wrapping is only available for those
    graph.setHtmlLabels(true);

    // Disables in-place editing for edges
    graph.isCellEditable = function(cell)
    {
        return !this.model.isEdge(cell);
    };
    
    //graph.graphHandler.scaleGrid = true;
    //graph.panningHandler.ignoreCell = true;
    
    // Changes the default style for edges "in-place"
    var style = graph.getStylesheet().getDefaultEdgeStyle();
    style[mxConstants.STYLE_EDGE] = mxEdgeStyle.ElbowConnector;
    
    /* Enables panning with left mouse button
    graph.panningHandler.useLeftButtonForPanning = true;
    graph.panningHandler.ignoreCell = true;
    graph.container.style.cursor = 'move';
    graph.setPanning(true);
    */
    // Enables rubberband selection
    new mxRubberband(graph);
    
    graph.getStylesheet().putCellStyle('HeaderFile', GetVertexStyle('HeaderFile',graph));

    graph.getStylesheet().putCellStyle('HeaderFunction', GetVertexStyle('HeaderFunction',graph));

    graph.getStylesheet().putCellStyle('Action', GetVertexStyle('Action',graph));
    
    graph.getStylesheet().putCellStyle('State', GetVertexStyle('State',graph));
    
    graph.getStylesheet().putCellStyle('Condition', GetVertexStyle('Condition',graph));

    graph.getStylesheet().putCellStyle('Crossover', GetVertexStyle('Crossover',graph));
    
    graph.getStylesheet().putCellStyle('End', GetVertexStyle('End',graph)); 

    graph.getStylesheet().putCellStyle('Call Expression', GetVertexStyle('Call Expression',graph)); 
            
    // Installs double click on middle control point and
    // changes style of edges between empty and this value
    graph.alternateEdgeStyle = 'elbow=vertical';

    // Adds automatic layout and various switches if the
    // graph is enabled
    if (graph.isEnabled())
    {
        // Allows new connections but no dangling edges
        graph.setConnectable(true);
        graph.setAllowDanglingEdges(false);
    }
    // Highlights offpage connectors
    var highlight = new mxCellTracker(graph, null, function(me)
    {
        var cell = me.getCell();
        
        if (cell != null &&
            cell.value != null &&
            typeof(cell.value.create) == 'function')
        {
            return cell;
        }
        
        return null;
    });
            
    // Handles clicks on offpage connectors and
    // executes function in user object
    graph.addListener(mxEvent.CLICK, function(source, evt)
    {
        var cell = evt.getProperty('cell');
        
        if (cell != null &&
            cell.value != null &&
            typeof(cell.value.create) == 'function')
        {
            cell.value.create();
        }
    });
    
    // Handles clicks on offpage connectors and
    // executes function in user object
    graph.getCursorForCell = function(cell)
    {
        if (cell != null &&
            cell.value != null &&
            typeof(cell.value.create) == 'function')
        {
            return 'pointer';
        }
    };
    
    // Adds zoom buttons in top, left corner
    var buttons = document.createElement('div');
    buttons.style.position = 'absolute';
    buttons.style.overflow = 'visible';

    var bs = graph.getBorderSizes();
    buttons.style.top = (container.offsetTop + bs.y) + 'px';
    buttons.style.left = (container.offsetLeft + bs.x) + 'px';
    
    var left = 0;
    var bw = 30;
    var bh = 30;
    
    if (mxClient.IS_QUIRKS)
    {
        bw -= 1;
        bh -= 1;
    }
    var Counter = 0;
    
    function UpdateGraphNavigation(funlist)
    {
        var navdiv = document.getElementsByClassName("graphnavi")[0];
        navdiv.innerHTML = "";
        for(var ifun = 0 ; ifun < funlist.length ; ifun++)
        {
            var navitemdiv = document.createElement("div"); 
            navitemdiv.id = funlist[ifun].Name;
            navitemdiv.style = "float:left;margin-right:10px;";
            if(ifun != funlist.length - 1)
            {
                navitemdiv.innerHTML = "<li><a><i class=\"fa fa-play\"></i> " + funlist[ifun].Name + " \\ </a></li>";
                $("#" + funlist[ifun].Name).click(function () {
                    DrawFunction(funlist[ifun].iCounter);
                });
            }
            else
            {
                navitemdiv.innerHTML = "<li class=\"fa fa-stop active\"> " + funlist[ifun].Name + " </li>";
            }
            navdiv.appendChild(navitemdiv);
        }
    }
    
    function DrawFunction(Counter)
    {
        var currentFunction = layouts[Counter].Function;
        UpdateGraphNavigation(layouts[Counter].FunctionPath);
        var Step, previousStep, labelsStack = [],vertexStack = [];
        var CellHeight = 40, CellWidth = 0, yCellLocation = 40, yCellIncrement = 50, xCellLocation = 220, xCellIncrement = 0;
        // Adds cells to the model in a single step
        graph.getModel().beginUpdate();
        try
        {
            var isConnectAlternate = false, IsNoElse = false;
            var lastyLocation = 0;
            graph.getModel().setRoot(graph.getModel().createRoot());
            var parent = graph.getDefaultParent();
            FileCellWidth = layouts[Counter].FileName.length <= 10  ? 120 : layouts[Counter].FileName.indexOf(' ') > 0 ? layouts[Counter].FileName.length * 4 : layouts[Counter].FileName.length * 8;
            var headerFile = graph.insertVertex(parent, null, layouts[Counter].FileName , 0, 0, FileCellWidth, 60, 'HeaderFile');
            FunCellWidth = currentFunction.Name.length < 10  ? 80 : currentFunction.Name.indexOf(' ') > 0 ? currentFunction.Name.length * 4 : currentFunction.Name.length * 8;
            var headerFun = graph.insertVertex(headerFile, null, currentFunction.Name , FileCellWidth-10, 15, FunCellWidth, 30, 'HeaderFunction');
            Step = graph.insertVertex(parent, null, 'Start', yCellLocation, xCellLocation, 30, 30, 'State');
            previousStep = Step;
            yCellLocation += (yCellIncrement + CellWidth + 40);
            for(var ifstateCounter = 0 ; ifstateCounter < currentFunction.Statements.length; ifstateCounter++)
            {
                var statement = currentFunction.Statements[ifstateCounter];
                CellWidth = statement.Text.length < 10  ? 60 : statement.Text.indexOf(' ') > 0 ? statement.Text.length * 4 : statement.Text.length * 6;
                switch(statement.Type)
                {
                    case "Label":
                        if(statement.Text.indexOf("If(") >= 0)
                        {
                            Step = graph.insertVertex(parent, null, statement.Text, yCellLocation , xCellLocation , CellWidth, CellHeight, 'Condition');
                            xCellLocation -= 70; 
                            vertexStack.push(Step);
                            labelsStack.push(yCellLocation);
                        }
                        else if(statement.Text.indexOf("If End") >= 0)
                        {
                            lastyLocation = yCellLocation;
                            xCellLocation += 70; 
                            if(currentFunction.Statements[ifstateCounter+1].Text.indexOf("Else Start") < 0)
                            {
                                IsNoElse = true;
                            }
                            continue;
                        }
                        else if(statement.Text.indexOf("Else Start") >= 0)
                        {
                            xCellLocation += 70;
                            yCellLocation = labelsStack.pop();
                            isConnectAlternate = true;
                            continue;
                        }
                        else if(statement.Text.indexOf("Else End") >= 0)
                        {
                            xCellLocation -= 70;
                            lastyLocation = yCellLocation;
                            continue;
                        }
                        
                        break;
                    
                    case "Call Expression":
                        Step = graph.insertVertex(parent, null, statement.Text, yCellLocation , xCellLocation , CellWidth, CellHeight, 'Call Expression');
                        break;
                    
                    default:
                        Step = graph.insertVertex(parent, null, statement.Text, yCellLocation , xCellLocation , CellWidth, CellHeight, 'Action');
                        break;
                }
                Step.CellType = statement.Type;
                if(isConnectAlternate)
                {
                    if(labelsStack.length > 0)
                    {
                        graph.insertEdge(parent, null, null, vertexStack.pop(), Step);
                    }
                    isConnectAlternate = false;
                }
                else if (IsNoElse)
                {
                    if(labelsStack.length > 0)
                    {
                        graph.insertEdge(parent, null, null, vertexStack.pop(), Step);
                    }
                    IsNoElse = false;
                }
                else
                {
                    if(previousStep != null)
                    {
                        graph.insertEdge(parent, null, null, previousStep, Step);
                    }
                }
                previousStep = Step;
                yCellLocation += (yCellIncrement + CellWidth);
            }
            yCellLocation += yCellIncrement;
            //var end = graph.insertVertex(parent, null, 'End', yCellLocation, 40, 30, 30, 'End');
        }
        finally
        {
            // Updates the display
            graph.getModel().endUpdate();
        }
    }

    function addToolBar(funct)
    {
        var btn = document.createElement('div'); 
        
        btn.innerHTML = "<div class=\"toolbar-container\">    <div class=\"menu-toggle\">      <span class=\"fa fa-plus\"></span>    </div>        <div class=\"menu-round\">      <div class=\"btn-toolbar btn-fa-step-forward\">        <div class=\"fa fa-step-forward\"></div>      </div>      <div class=\"btn-toolbar btn-fa-play\">        <div class=\"fa fa-play\"></div>      </div>      <div class=\"btn-toolbar btn-fa-step-backward\">        <div class=\"fa fa- fa-step-backward\"></div>      </div>    </div>        <div class=\"menu-line\">   <div class=\"btn-toolbar btn-fa-fast-forward\">        <div class=\"fa fa-fast-forward\"></div>      </div>  <div class=\"btn-toolbar btn-fa-fast-backward\">        <div class=\"fa fa-fast-backward\"></div>      </div> <div class=\"btn-toolbar btn-fa-search-plus\">        <div class=\"fa fa-search-plus\"></div>      </div>      <div class=\"btn-toolbar btn-fa-search-minus\">        <div class=\"fa fa-search-minus\"></div>      </div>      <div class=\"btn-toolbar btn-fa-sign-in\">        <div class=\"fa fa-sign-in\"></div>      </div>      <div class=\"btn-toolbar btn-fa-sign-out\">        <div class=\"fa fa-sign-out\"></div>      </div>   <div class=\"btn-toolbar btn-fa-image\">        <div class=\"fa fa-image\"></div>      </div>      <div class=\"btn-toolbar btn-fa-download\">        <div class=\"fa fa-download\"></div>      </div>    </div>          </div>";

        //mxUtils.write(btn, label);
        var toolbtn = btn.getElementsByClassName("menu-toggle")[0];
        mxEvent.addListener(toolbtn, 'click', function(evt)
        {
            funct();
        });

        var isPlay = false;
        var playbtn = btn.getElementsByClassName("btn-fa-play")[0];
        mxEvent.addListener(playbtn, 'click', function(evt)
        {
            function Next()
            {
                if(isPlay)
                {
                    Counter++;
                    DrawFunction(Counter);
                    play();
                }
                
            }
            var play = function(){
                if(isPlay)
                {
                    if(Counter >= layouts.length-1){
                        alert("play is done");
    
                    }
                    else {
                        setTimeout(Next, 3000); // check again in a second
                    }
                }
                else
                {
                    //alert("play is done");
                }
                
            }
            isPlay = !isPlay;
            play();
            if(!isPlay)
            {
                playbtn.getElementsByClassName("fa")[0].classList.remove("fa-stop");
                playbtn.getElementsByClassName("fa")[0].classList.add("fa-play");
            }
            else
            {
                playbtn.getElementsByClassName("fa")[0].classList.remove("fa-play");
                playbtn.getElementsByClassName("fa")[0].classList.add("fa-stop");
            }
        });

        var forwardbtn = btn.getElementsByClassName("btn-fa-step-forward")[0];
        mxEvent.addListener(forwardbtn, 'click', function(evt)
        {
            Counter = Counter >= layouts.length-1 ? Counter : Counter+1; 
            DrawFunction(Counter);
        });
        
        var backwardbtn = btn.getElementsByClassName("btn-fa-step-backward")[0];
        mxEvent.addListener(backwardbtn, 'click', function(evt)
        {
            Counter = Counter > 0 ? Counter - 1 : Counter ; 
            DrawFunction(Counter);
        });

        var zoominbtn = btn.getElementsByClassName("btn-fa-search-plus")[0];
        mxEvent.addListener(zoominbtn, 'click', function(evt)
        {
            graph.zoomIn();
        });

        var zoomoutbtn = btn.getElementsByClassName("btn-fa-search-minus")[0];
        mxEvent.addListener(zoomoutbtn, 'click', function(evt)
        {
            graph.zoomOut();
        });

        var gotostartbtn = btn.getElementsByClassName("btn-fa-sign-in")[0];
        mxEvent.addListener(gotostartbtn, 'click', function(evt)
        {
            container.scrollTop = 0;
            container.scrollLeft = 0;
        });

        var gotoendbtn = btn.getElementsByClassName("btn-fa-sign-out")[0];
        mxEvent.addListener(gotoendbtn, 'click', function(evt)
        {
            container.scrollLeft = container.scrollWidth - container.clientWidth;
            container.scrollTop = container.scrollHeight - container.clientHeight;
        });

        var firstfunbtn = btn.getElementsByClassName("btn-fa-fast-backward")[0];
        mxEvent.addListener(firstfunbtn, 'click', function(evt)
        {
            Counter = 0;
            DrawFunction(Counter);
        });

        var lastfunbtn = btn.getElementsByClassName("btn-fa-fast-forward")[0];
        mxEvent.addListener(lastfunbtn, 'click', function(evt)
        {
            Counter = layouts.length-1;
            DrawFunction(Counter);
        });

        var asimagebtn = btn.getElementsByClassName("btn-fa-image")[0];
        mxEvent.addListener(asimagebtn, 'click', function(evt)
        {
            var xmlDoc = mxUtils.createXmlDocument();
            var root = xmlDoc.createElement('output');
            xmlDoc.appendChild(root);

            var xmlCanvas = new mxXmlCanvas2D(root);
            var imgExport = new mxImageExport();
            imgExport.drawState(graph.getView().getState(graph.model.root), xmlCanvas);

            var bounds = graph.getGraphBounds();
            var w = Math.ceil(bounds.x + bounds.width);
            var h = Math.ceil(bounds.y + bounds.height);

            var xml = mxUtils.getXml(root);
            new mxXmlRequest('export', 'format=png&w=' + w +
                '&h=' + h + '&bg=#F9F7ED&xml=' + encodeURIComponent(xml))
                .simulate(document, '_blank');
        });
        
        buttons.appendChild(btn);
    };
    
    addToolBar(function()
    {
        $(".menu-toggle").toggleClass('open');
        $(".menu-round").toggleClass('open');
        $(".menu-line").toggleClass('open');
    });
    
    if (container.nextSibling != null)
    {
        container.parentNode.insertBefore(buttons, container.nextSibling);
    }
    else
    {
        container.appendChild(buttons);
    }
    
    // Configures automatic expand on mouseover
    graph.popupMenuHandler.autoExpand = true;

    // Installs context menu
    graph.popupMenuHandler.factoryMethod = function(menu, cell, evt)
    {
        if(cell != null && cell.CellType == "Call Expression")
        {
            menu.addItem('Show Details', null, function()
            {

            });
            
            menu.addItem('Called By', null, function()
            {

            });

            
            var tracemenu = menu.addItem('Trace As', null, null);
            
            menu.addItem('Activity Diagram', null, function()
            {

            }, tracemenu);
            menu.addItem('Sequence Diagram', null, function()
            {

            }, tracemenu);
        }
    };
    
    DrawFunction(Counter);
    return graph;
}
function LaneActivityDiagramConfig(container)
{
    // Disables built-in context menu
    mxEvent.disableContextMenu(document.body);
     // Creates a wrapper editor around a new graph inside
    // the given container using an XML config for the
    // keyboard bindings
    // Creates the graph inside the given container
    var graph = new mxGraph(container);
    graph.setTooltips(true);
    //graph.graphHandler.scaleGrid = true;
    //graph.panningHandler.ignoreCell = true;
    
    // Changes the default style for edges "in-place"
    var style = graph.getStylesheet().getDefaultEdgeStyle();
    style[mxConstants.STYLE_EDGE] = mxEdgeStyle.ElbowConnector;
    
    // Enables panning with left mouse button
    graph.panningHandler.useLeftButtonForPanning = true;
    graph.panningHandler.ignoreCell = true;
    graph.container.style.cursor = 'move';
    graph.setPanning(true);
    
    
    //graph.resizeContainer = false;
    /**
     * Specifies the size of the size for "tiles" to be used for a graph with
     * scrollbars but no visible background page. A good value is large
     * enough to reduce the number of repaints that is caused for auto-
     * translation, which depends on this value, and small enough to give
     * a small empty buffer around the graph. Default is 400x400.
     */
   // graph.scrollTileSize = new mxRectangle(0, 0, 400, 400);
    

    // Enables rubberband selection
    new mxRubberband(graph);

    // Changes the default vertex style in-place
    var style = graph.getStylesheet().getDefaultVertexStyle();
    style[mxConstants.STYLE_SHAPE] = mxConstants.SHAPE_SWIMLANE;
    style[mxConstants.STYLE_VERTICAL_ALIGN] = 'middle';
    style[mxConstants.STYLE_LABEL_BACKGROUNDCOLOR] = 'white';
    style[mxConstants.STYLE_FONTSIZE] = 11;
    style[mxConstants.STYLE_STARTSIZE] = 22;
    style[mxConstants.STYLE_HORIZONTAL] = false;
    style[mxConstants.STYLE_FONTCOLOR] = 'black';
    style[mxConstants.STYLE_STROKECOLOR] = 'black';
    style[mxConstants.STYLE_WHITE_SPACE] = 'wrap';
    delete style[mxConstants.STYLE_FILLCOLOR];

    style = mxUtils.clone(style);
    style[mxConstants.STYLE_SHAPE] = mxConstants.SHAPE_RECTANGLE;
    style[mxConstants.STYLE_FONTSIZE] = 10;
    style[mxConstants.STYLE_ROUNDED] = true;
    style[mxConstants.STYLE_HORIZONTAL] = true;
    style[mxConstants.STYLE_VERTICAL_ALIGN] = 'middle';
    delete style[mxConstants.STYLE_STARTSIZE];
    style[mxConstants.STYLE_LABEL_BACKGROUNDCOLOR] = 'none';
    graph.getStylesheet().putCellStyle('process', style);
    
    style = mxUtils.clone(style);
    style[mxConstants.STYLE_SHAPE] = mxConstants.SHAPE_ELLIPSE;
    style[mxConstants.STYLE_PERIMETER] = mxPerimeter.EllipsePerimeter;
    delete style[mxConstants.STYLE_ROUNDED];
    graph.getStylesheet().putCellStyle('state', style);
                                    
    style = mxUtils.clone(style);
    style[mxConstants.STYLE_SHAPE] = mxConstants.SHAPE_RHOMBUS;
    style[mxConstants.STYLE_PERIMETER] = mxPerimeter.RhombusPerimeter;
    style[mxConstants.STYLE_VERTICAL_ALIGN] = 'top';
    style[mxConstants.STYLE_SPACING_TOP] = 40;
    style[mxConstants.STYLE_SPACING_RIGHT] = 64;
    graph.getStylesheet().putCellStyle('condition', style);
                    
    style = mxUtils.clone(style);
    style[mxConstants.STYLE_SHAPE] = mxConstants.SHAPE_DOUBLE_ELLIPSE;
    style[mxConstants.STYLE_PERIMETER] = mxPerimeter.EllipsePerimeter;
    style[mxConstants.STYLE_SPACING_TOP] = 28;
    style[mxConstants.STYLE_FONTSIZE] = 14;
    style[mxConstants.STYLE_FONTSTYLE] = 1;
    delete style[mxConstants.STYLE_SPACING_RIGHT];
    graph.getStylesheet().putCellStyle('end', style);
    
    style = graph.getStylesheet().getDefaultEdgeStyle();
    style[mxConstants.STYLE_EDGE] = mxEdgeStyle.ElbowConnector;
    style[mxConstants.STYLE_ENDARROW] = mxConstants.ARROW_BLOCK;
    style[mxConstants.STYLE_ROUNDED] = true;
    style[mxConstants.STYLE_FONTCOLOR] = 'black';
    style[mxConstants.STYLE_STROKECOLOR] = 'black';
    
    style = mxUtils.clone(style);
    style[mxConstants.STYLE_DASHED] = true;
    style[mxConstants.STYLE_ENDARROW] = mxConstants.ARROW_OPEN;
    style[mxConstants.STYLE_STARTARROW] = mxConstants.ARROW_OVAL;
    graph.getStylesheet().putCellStyle('crossover', style);
            
    // Installs double click on middle control point and
    // changes style of edges between empty and this value
    graph.alternateEdgeStyle = 'elbow=vertical';

    // Adds automatic layout and various switches if the
    // graph is enabled
    if (graph.isEnabled())
    {
        // Allows new connections but no dangling edges
        graph.setConnectable(true);
        graph.setAllowDanglingEdges(false);
        
        // End-states are no valid sources
        var previousIsValidSource = graph.isValidSource;
        
        graph.isValidSource = function(cell)
        {
            if (previousIsValidSource.apply(this, arguments))
            {
                var style = this.getModel().getStyle(cell);
                
                return style == null || !(style == 'end' || style.indexOf('end') == 0);
            }

            return false;
        };
        
        // Start-states are no valid targets, we do not
        // perform a call to the superclass function because
        // this would call isValidSource
        // Note: All states are start states in
        // the example below, so we use the state
        // style below
        graph.isValidTarget = function(cell)
        {
            var style = this.getModel().getStyle(cell);
            
            return !this.getModel().isEdge(cell) && !this.isSwimlane(cell) &&
                (style == null || !(style == 'state' || style.indexOf('state') == 0));
        };
        
        // Allows dropping cells into new lanes and
        // lanes into new pools, but disallows dropping
        // cells on edges to split edges
        graph.setDropEnabled(true);
        graph.setSplitEnabled(false);
        
        // Returns true for valid drop operations
        graph.isValidDropTarget = function(target, cells, evt)
        {
            if (this.isSplitEnabled() && this.isSplitTarget(target, cells, evt))
            {
                return true;
            }
            
            var model = this.getModel();
            var lane = false;
            var pool = false;
            var cell = false;
            
            // Checks if any lanes or pools are selected
            for (var i = 0; i < cells.length; i++)
            {
                var tmp = model.getParent(cells[i]);
                lane = lane || this.isPool(tmp);
                pool = pool || this.isPool(cells[i]);
                
                cell = cell || !(lane || pool);
            }
            
            return !pool && cell != lane && ((lane && this.isPool(target)) ||
                (cell && this.isPool(model.getParent(target))));
        };
        
        // Adds new method for identifying a pool
        graph.isPool = function(cell)
        {
            var model = this.getModel();
            var parent = model.getParent(cell);
        
            return parent != null && model.getParent(parent) == model.getRoot();
        };
        
        // Changes swimlane orientation while collapsed
        graph.model.getStyle = function(cell)
        {
            var style = mxGraphModel.prototype.getStyle.apply(this, arguments);
        
            if (graph.isCellCollapsed(cell))
            {
                if (style != null)
                {
                    style += ';';
                }
                else
                {
                    style = '';
                }
                
                style += 'horizontal=1;align=left;spacingLeft=14;';
            }
            
            return style;
        };

        // Keeps widths on collapse/expand					
        var foldingHandler = function(sender, evt)
        {
            var cells = evt.getProperty('cells');
            
            for (var i = 0; i < cells.length; i++)
            {
                var geo = graph.model.getGeometry(cells[i]);

                if (geo.alternateBounds != null)
                {
                    geo.width = geo.alternateBounds.width;
                }
            }
        };

        graph.addListener(mxEvent.FOLD_CELLS, foldingHandler);
    }
    
    // Applies size changes to siblings and parents
    new mxSwimlaneManager(graph);

    // Creates a stack depending on the orientation of the swimlane
    var layout = new mxStackLayout(graph, false);
    
    // Makes sure all children fit into the parent swimlane
    layout.resizeParent = true;
                
    // Applies the size to children if parent size changes
    layout.fill = true;

    // Only update the size of swimlanes
    layout.isVertexIgnored = function(vertex)
    {
        return !graph.isSwimlane(vertex);
    }
    
    // Keeps the lanes and pools stacked
    var layoutMgr = new mxLayoutManager(graph);

    layoutMgr.getLayout = function(cell)
    {
        var model = graph.getModel();
        if (!model.isEdge(cell) && graph.getModel().getChildCount(cell) > 0 &&
            (model.getParent(cell) == model.getRoot() || graph.isPool(cell)))
        {
            layout.fill = graph.isPool(cell);
            
            return layout;
        }
        
        return null;
    };
    // Adds zoom buttons in top, left corner
    var buttons = document.createElement('div');
    buttons.style.position = 'absolute';
    buttons.style.overflow = 'visible';

    var bs = graph.getBorderSizes();
    buttons.style.top = (container.offsetTop + bs.y) + 'px';
    buttons.style.left = (container.offsetLeft + bs.x) + 'px';
    
    var left = 750;
    var bw = 16;
    var bh = 16;
    
    if (mxClient.IS_QUIRKS)
    {
        bw -= 1;
        bh -= 1;
    }
    
    function addButton(label, funct)
    {
        var btn = document.createElement('div');
        mxUtils.write(btn, label);
        btn.style.position = 'absolute';
        btn.style.backgroundColor = 'transparent';
        btn.style.border = '1px solid gray';
        btn.style.textAlign = 'center';
        btn.style.fontSize = '10px';
        btn.style.cursor = 'hand';
        btn.style.width = bw + 'px';
        btn.style.height = bh + 'px';
        btn.style.left = left + 'px';
        btn.style.top = '0px';
        
        mxEvent.addListener(btn, 'click', function(evt)
        {
            funct();
            mxEvent.consume(evt);
        });
        
        left += bw;
        
        buttons.appendChild(btn);
    };
    
    addButton('+', function()
    {
        graph.zoomIn();
    });
    
    addButton('-', function()
    {
        graph.zoomOut();
    });
    
    if (container.nextSibling != null)
    {
        container.parentNode.insertBefore(buttons, container.nextSibling);
    }
    else
    {
        container.appendChild(buttons);
    }
    
    // Configures automatic expand on mouseover
    graph.popupMenuHandler.autoExpand = true;

    // Installs context menu
    graph.popupMenuHandler.factoryMethod = function(menu, cell, evt)
    {
        if(cell != null && cell.CellType == "Call Expression")
        {
            menu.addItem('Show Details', null, function()
            {

            });
            
            menu.addItem('Called By', null, function()
            {

            });

            
            var tracemenu = menu.addItem('Trace As', null, null);
            
            menu.addItem('Activity Diagram', null, function()
            {

            }, tracemenu);
            menu.addItem('Sequence Diagram', null, function()
            {

            }, tracemenu);
        }
        
    };
    return graph;
}