/*! AdminLTE 2.0.1 app.js
 * ======================
 * Main JS application file for AdminLTE v2. This file
 * should be included in all pages. It controls some layout
 * options and implements exclusive AdminLTE plugins.
 *
 * @Author  Almsaeed Studio
 * @Support <http://www.almsaeedstudio.com>
 * @Email   <support@almsaeedstudio.com>
 * @version 2.0
 * @license MIT <http://opensource.org/licenses/MIT>
 */

//Make sure jQuery has been loaded before app.js
if (typeof jQuery === "undefined") {
  throw new Error("AdminLTE requires jQuery");
}

'use strict';

/* AdminLTE
 *
 * @type Object
 * @description $.AdminLTE is the main object for the template's app.
 *				It's used for implementing functions and options related
 *				to the template. Keeping everything wrapped in an object
 *				prevents conflict with other plugins and is a better
 *				way to organize our code.
 */
$.AdminLTE = {};

/* --------------------
 * - AdminLTE Options -
 * --------------------
 * Modify these options to suit your implementation
 */
$.AdminLTE.options = {
  //Add slimscroll to navbar menus
  //This requires you to load the slimscroll plugin
  //in every page before app.js
  navbarMenuSlimscroll: true,
  navbarMenuSlimscrollWidth: "3px", //The width of the scroll bar
  navbarMenuHeight: "200px", //The height of the inner menu
  //Sidebar push menu toggle button selector
  sidebarToggleSelector: "[data-toggle='offcanvas']",
  //Activate sidebar push menu
  sidebarPushMenu: true,
  //Activate sidebar slimscroll if the fixed layout is set (requires SlimScroll Plugin)
  sidebarSlimScroll: true,
  //BoxRefresh Plugin
  enableBoxRefresh: true,
  //Bootstrap.js tooltip
  enableBSToppltip: true,
  BSTooltipSelector: "[data-toggle='tooltip']",
  //Enable Fast Click. Fastclick.js creates a more
  //native touch ecperience with touch devices. If you
  //choose to enable the plugin, make sure you load the script 
  //before AdminLTE's app.js
  enableFastclick: true,
  //Box Widget Plugin. Enable this plugin
  //to allow boxes to be collapsed and/or removed
  enableBoxWidget: true,
  //Box Widget plugin options
  boxWidgetOptions: {
    boxWidgetIcons: {
      //The icon that triggers the collapse event
      collapse: 'fa fa-minus',
      //The icon that trigger the opening event
      open: 'fa fa-plus',
      //The icon that triggers the removing event
      remove: 'fa fa-times'
    },
    boxWidgetSelectors: {
      //Remove button selector
      remove: '[data-widget="remove"]',
      //Collapse button selector
      collapse: '[data-widget="collapse"]'
    }
  },
  //Define the set of colors to use globally around the website
  colors: {
    lightBlue: "#87B9E1",
    red: "#f56954",
    green: "#00a65a",
    aqua: "#00c0ef",
    yellow: "#f39c12",
    blue: "#0073b7",
    navy: "#001F3F",
    teal: "#39CCCC",
    olive: "#3D9970",
    lime: "#01FF70",
    orange: "#FF851B",
    fuchsia: "#F012BE",
    purple: "#8E24AA",
    maroon: "#D81B60",
    black: "#222222",
    gray: "#d2d6de"
  }
};

/* ------------------
 * - Implementation -
 * ------------------
 * The next block of code implements AdminLTE's
 * functions and plugins as specified by the
 * options above.
 */
$(function () {
  //Easy access to options
  var o = $.AdminLTE.options;

  //Activate the layout maker
  $.AdminLTE.layout.activate();

  //Enable sidebar tree view controls
  $.AdminLTE.tree('.sidebar');

  //Add slimscroll to navbar dropdown
  if (o.navbarMenuSlimscroll && typeof $.fn.slimscroll != 'undefined') {
    $(".navbar .menu").slimscroll({
      height: "200px",
      alwaysVisible: false,
      size: "3px"
    }).css("width", "100%");
  }

  //Activate sidebar push menu
  if (o.sidebarPushMenu) {
    $.AdminLTE.pushMenu(o.sidebarToggleSelector);
  }

  //Activate Bootstrap tooltip
  if (o.enableBSToppltip) {
    $(o.BSTooltipSelector).tooltip();
  }

  //Activate box widget
  if (o.enableBoxWidget) {
    $.AdminLTE.boxWidget.activate();
  }
  
  if(o.enableFastclick && typeof FastClick != 'undefined') {
    FastClick.attach(document.body);
  }

  /*
   * INITIALIZE BUTTON TOGGLE
   * ------------------------
   */
  $('.btn-group[data-toggle="btn-toggle"]').each(function () {
    var group = $(this);
    $(this).find(".btn").click(function (e) {
      group.find(".btn.active").removeClass("active");
      $(this).addClass("active");
      e.preventDefault();
    });

  });
});

/* ----------------------
 * - AdminLTE Functions -
 * ----------------------
 * All AdminLTE functions are implemented below.
 */

/* prepareLayout
 * =============
 * Fixes the layout height in case min-height fails.
 *
 * @type Object
 * @usage $.AdminLTE.layout.activate()
 *        $.AdminLTE.layout.fix()
 *        $.AdminLTE.layout.fixSidebar()
 */
$.AdminLTE.layout = {
  activate: function () {
    var _this = this;
    _this.fix();
    _this.fixSidebar();
    $(window, ".wrapper").resize(function () {
      _this.fix();
      _this.fixSidebar();
    });
  },
  fix: function () {
    //Get window height and the wrapper height
    var neg = $('.main-header').outerHeight() + $('.main-footer').outerHeight();
    var window_height = $(window).height();
    var sidebar_height = $(".sidebar").height();
    //Set the min-height of the content and sidebar based on the
    //the height of the document.
    if ($("body").hasClass("fixed")) {
      $(".content-wrapper, .right-side").css('min-height', window_height - $('.main-footer').outerHeight());
    } else {
      if (window_height >= sidebar_height) {
        $(".content-wrapper, .right-side").css('min-height', window_height - neg);
      } else {
        $(".content-wrapper, .right-side").css('min-height', sidebar_height);
      }
    }
  },
  fixSidebar: function () {
    //Make sure the body tag has the .fixed class
    if (!$("body").hasClass("fixed")) {
      if (typeof $.fn.slimScroll != 'undefined') {
        $(".sidebar").slimScroll({destroy: true}).height("auto");
      }
      return;
    } else if (typeof $.fn.slimScroll == 'undefined' && console) {
      console.error("Error: the fixed layout requires the slimscroll plugin!");
    }
    //Enable slimscroll for fixed layout
    if ($.AdminLTE.options.sidebarSlimScroll) {
      if (typeof $.fn.slimScroll != 'undefined') {
        //Distroy if it exists
        $(".sidebar").slimScroll({destroy: true}).height("auto");
        //Add slimscroll
        $(".sidebar").slimscroll({
          height: ($(window).height() - $(".main-header").height()) + "px",
          color: "rgba(0,0,0,0.2)",
          size: "3px"
        });
      }
    }
  }
};

/* PushMenu()
 * ==========
 * Adds the push menu functionality to the sidebar.
 *
 * @type Function
 * @usage: $.AdminLTE.pushMenu("[data-toggle='offcanvas']")
 */
$.AdminLTE.pushMenu = function (toggleBtn) {
  //Enable sidebar toggle
  $(toggleBtn).click(function (e) {
    e.preventDefault();
    //Enable sidebar push menu
    $("body").toggleClass('sidebar-collapse');
    $("body").toggleClass('sidebar-open');
  });
  $(".content-wrapper").click(function () {
    //Enable hide menu when clicking on the content-wrapper on small screens    
    if ($(window).width() <= 767 && $("body").hasClass("sidebar-open")) {
      $("body").removeClass('sidebar-open');
    }
  });

};

/* Tree()
 * ======
 * Converts the sidebar into a multilevel
 * tree view menu.
 *
 * @type Function
 * @Usage: $.AdminLTE.tree('.sidebar')
 */
$.AdminLTE.tree = function (menu) {
  $("li a", $(menu)).click(function (e) {
    //Get the clicked link and the next element
    var $this = $(this);
    var checkElement = $this.next();

    //Check if the next element is a menu and is visible
    if ((checkElement.is('.treeview-menu')) && (checkElement.is(':visible'))) {
      //Close the menu
      checkElement.slideUp('normal', function () {
        checkElement.removeClass('menu-open');
      });
      checkElement.parent("li").removeClass("active");
    }
    //If the menu is not visible
    else if ((checkElement.is('.treeview-menu')) && (!checkElement.is(':visible'))) {
      //Get the parent menu
      var parent = $this.parents('ul').first();
      //Close all open menus within the parent
      var ul = parent.find('ul:visible').slideUp('normal');
      //Remove the menu-open class from the parent
      ul.removeClass('menu-open');
      //Get the parent li
      var parent_li = $this.parent("li");

      //Open the target menu and add the menu-open class
      checkElement.slideDown('normal', function () {
        //Add the class active to the parent li
        checkElement.addClass('menu-open');
        parent.find('li.active').removeClass('active');
        parent_li.addClass('active');
      });
    }
    //if this isn't a link, prevent the page from being redirected
    if (checkElement.is('.treeview-menu')) {
      e.preventDefault();
    }
  });
};

/* BoxWidget
 * =========
 * BoxWidget is plugin to handle collapsing and
 * removing boxes from the screen.
 *
 * @type Object
 * @usage $.AdminLTE.boxWidget.activate()
 *								Set all of your option in the main $.AdminLTE.options object
 */
$.AdminLTE.boxWidget = {
  activate: function () {
    var o = $.AdminLTE.options;
    var _this = this;
    //Listen for collapse event triggers
    $(o.boxWidgetOptions.boxWidgetSelectors.collapse).click(function (e) {
      e.preventDefault();
      _this.collapse($(this));
    });

    //Listen for remove event triggers
    $(o.boxWidgetOptions.boxWidgetSelectors.remove).click(function (e) {
      e.preventDefault();
      _this.remove($(this));
    });
  },
  collapse: function (element) {
    //Find the box parent
    var box = element.parents(".box").first();
    //Find the body and the footer
    var bf = box.find(".box-body, .box-footer");
    if (!box.hasClass("collapsed-box")) {
      //Convert minus into plus
      element.children(".fa-minus").removeClass("fa-minus").addClass("fa-plus");
      bf.slideUp(300, function () {
        box.addClass("collapsed-box");
      });
    } else {
      //Convert plus into minus
      element.children(".fa-plus").removeClass("fa-plus").addClass("fa-minus");
      bf.slideDown(300, function () {
        box.removeClass("collapsed-box");
      });
    }
  },
  remove: function (element) {
    //Find the box parent
    var box = element.parents(".box").first();
    box.slideUp();
  },
  options: $.AdminLTE.options.boxWidgetOptions
};

/* ------------------
 * - Custom Plugins -
 * ------------------
 * All custom plugins are defined below.
 */

/*
 * BOX REFRESH BUTTON
 * ------------------
 * This is a custom plugin to use with the compenet BOX. It allows you to add
 * a refresh button to the box. It converts the box's state to a loading state.
 *
 *	@type plugin
 * @usage $("#box-widget").boxRefresh( options );
 */
(function ($) {

  $.fn.boxRefresh = function (options) {

    // Render options
    var settings = $.extend({
      //Refressh button selector
      trigger: ".refresh-btn",
      //File source to be loaded (e.g: ajax/src.php)
      source: "",
      //Callbacks
      onLoadStart: function (box) {
      }, //Right after the button has been clicked
      onLoadDone: function (box) {
      } //When the source has been loaded

    }, options);

    //The overlay
    var overlay = $('<div class="overlay"></div><div class="loading-img"></div>');

    return this.each(function () {
      //if a source is specified
      if (settings.source === "") {
        if (console) {
          console.log("Please specify a source first - boxRefresh()");
        }
        return;
      }
      //the box
      var box = $(this);
      //the button
      var rBtn = box.find(settings.trigger).first();

      //On trigger click
      rBtn.click(function (e) {
        e.preventDefault();
        //Add loading overlay
        start(box);

        //Perform ajax call
        box.find(".box-body").load(settings.source, function () {
          done(box);
        });
      });
    });

    function start(box) {
      //Add overlay and loading img
      box.append(overlay);

      settings.onLoadStart.call(box);
    }

    function done(box) {
      //Remove overlay and loading img
      box.find(overlay).remove();

      settings.onLoadDone.call(box);
    }

  };

})(jQuery);

/*
 * TODO LIST CUSTOM PLUGIN
 * -----------------------
 * This plugin depends on iCheck plugin for checkbox and radio inputs
 *
 * @type plugin
 * @usage $("#todo-widget").todolist( options );
 */
(function ($) {

  $.fn.todolist = function (options) {
    // Render options
    var settings = $.extend({
      //When the user checks the input
      onCheck: function (ele) {
      },
      //When the user unchecks the input
      onUncheck: function (ele) {
      }
    }, options);

    return this.each(function () {

      if (typeof $.fn.iCheck != 'undefined') {
        $('input', this).on('ifChecked', function (event) {
          var ele = $(this).parents("li").first();
          ele.toggleClass("done");
          settings.onCheck.call(ele);
        });

        $('input', this).on('ifUnchecked', function (event) {
          var ele = $(this).parents("li").first();
          ele.toggleClass("done");
          settings.onUncheck.call(ele);
        });
      } else {
        $('input', this).on('change', function (event) {
          var ele = $(this).parents("li").first();
          ele.toggleClass("done");
          settings.onCheck.call(ele);
        });
      }
    });
  };
}(jQuery));

function LoadDiagram()
{
  var activityDiagram = new UMLActivityDiagram ({id: 'activityDiagram', width: 1000, height: 580});
  // Create the horizontal swimlane
  var unhierarchicalSwimlane = new UMLHorizontalSwimlane ({x: 30, y: 35});
  // Create the nodes
  var initialNode = new UMLInitialNode ({x: 174, y: 44});
  
  var activityFinal = new UMLActivityFinal ({x: 780, y: 183});
  
  var fork_joinNode0 = new UMLFork_JoinNode ({x: 460, y: 185});
  var fork_joinNode1 = new UMLFork_JoinNode ({x: 610, y: 101});
  
  var decision_mergeNode0 = new UMLDecision_MergeNode ({x: 160, y: 136});
  var decision_mergeNode1 = new UMLDecision_MergeNode ({x: 635, y: 115});

  var receiveOrder = new UMLAction ({x: 125, y: 78});

  var fillOrder = new UMLAction ({x: 225, y: 190});

  var shipOrder = new UMLAction ({x: 485, y: 103});

  var closeOrder = new UMLAction ({x: 740, y: 115});

  var sendInvoice = new UMLAction ({x: 155, y: 349});

  var acceptPayment = new UMLAction ({x: 540, y: 352});

  var makePayment = new UMLAction ({x: 345, y: 485});

  // Create the relations
  var flow0 = new UMLFlow ({a: initialNode, b: receiveOrder});
  var flow1 = new UMLFlow ({a: receiveOrder, b: decision_mergeNode0});
  var flow2 = new UMLFlow ({a: decision_mergeNode0, b: fillOrder});
  var flow3 = new UMLFlow ({a: decision_mergeNode0, b: decision_mergeNode1});
  var flow4 = new UMLFlow ({a: fillOrder, b: fork_joinNode0});
  var flow5 = new UMLFlow ({a: fork_joinNode0, b: shipOrder});
  var flow6 = new UMLFlow ({a: fork_joinNode0, b: sendInvoice});
  var flow7 = new UMLFlow ({a: sendInvoice, b: makePayment});
  var flow8 = new UMLFlow ({a: makePayment, b: acceptPayment});
  var flow9 = new UMLFlow ({a: shipOrder, b: fork_joinNode1});
  var flow10 = new UMLFlow ({a: acceptPayment, b: fork_joinNode1});
  var flow11 = new UMLFlow ({a: fork_joinNode1, b: decision_mergeNode1});
  var flow12 = new UMLFlow ({a: decision_mergeNode1, b: closeOrder});
  var flow13 = new UMLFlow ({a: closeOrder, b: activityFinal});
  // Properties of the unhierarchical swimlane

// Set the height and name of the first swimlane

unhierarchicalSwimlane.getNodeChilds () [0] .setHeight (220);

unhierarchicalSwimlane.getNodeChilds () [0] .getComponents () [1] .setText ('Order Dept.');         

// Set the height and name of the second swimlane

unhierarchicalSwimlane.getNodeChilds () [1] .setHeight (216);

unhierarchicalSwimlane.getNodeChilds () [1] .setName ('Accountability Dept.');

// Create the third swimlane

unhierarchicalSwimlane.addRegion (new Swimlane ({parent: unhierarchicalSwimlane}));

unhierarchicalSwimlane.getNodeChilds () [2] .setName ('Customer');                  

// Set properties of the horizontal swimlane

unhierarchicalSwimlane.setWidth (807);

unhierarchicalSwimlane.setHeight (520);

unhierarchicalSwimlane.notifyChange ();

 

// Properties of the rest of elements

fork_joinNode0.setQuadrant (2);

fork_joinNode0.setHeight (61);

 

fork_joinNode1.setQuadrant (2);

fork_joinNode1.setHeight (61);

 

receiveOrder.setHeight (25);

receiveOrder.setName ('Complete order');

receiveOrder.notifyChange ();

 

fillOrder.setHeight (25);

fillOrder.setName ('Complete order');

fillOrder.notifyChange ();

 

shipOrder.setHeight (25);

shipOrder.setName ('Submit order');

shipOrder.notifyChange ();

 

closeOrder.setHeight (25);

closeOrder.setName ('Close order');

closeOrder.notifyChange ();

 

sendInvoice.setHeight (25);

sendInvoice.setName ('Send invoice');

sendInvoice.notifyChange ();

 

acceptPayment.setHeight (25);

acceptPayment.setName ('Accept payment');

acceptPayment.notifyChange ();

 

makePayment.setHeight (25);

makePayment.setName ('Make payment');

makePayment.notifyChange ();
// Add nodes to the diagram

activityDiagram.addElement (unhierarchicalSwimlane);

activityDiagram.addElement (initialNode);

activityDiagram.addElement (activityFinal);

activityDiagram.addElement (fork_joinNode0);

activityDiagram.addElement (fork_joinNode1);

activityDiagram.addElement (decision_mergeNode0);

activityDiagram.addElement (decision_mergeNode1);

activityDiagram.addElement (receiveOrder);

activityDiagram.addElement (fillOrder);

activityDiagram.addElement (shipOrder);

activityDiagram.addElement (closeOrder);

activityDiagram.addElement (sendInvoice);

activityDiagram.addElement (acceptPayment);

activityDiagram.addElement (makePayment);

 

// Add messages to the diagram

activityDiagram.addElement (flow0);

activityDiagram.addElement (flow1);

activityDiagram.addElement (flow2);

activityDiagram.addElement (flow3);

activityDiagram.addElement (flow4);

activityDiagram.addElement (flow5);

activityDiagram.addElement (flow6);

activityDiagram.addElement (flow7);

activityDiagram.addElement (flow8);

activityDiagram.addElement (flow9);

activityDiagram.addElement (flow10);

activityDiagram.addElement (flow11);

activityDiagram.addElement (flow12);

activityDiagram.addElement (flow13);
activityDiagram.draw ();
activityDiagram.interaction (true);
activityDiagram.setUpdateHeightCanvas (true);
}