# qml-gridsystem

A gridsystem for QML similar to grid systems that are available for CSS. You specify how many columns
a object should occupy and the GSGrid does the layout for you.


## Installation

### qpm

with qpm just go to your project directory and install with this command:

```
qpm install com.bckmnn.gridsystem
```

after installation you just need to add `include(vendor/vendor.pri)` to your *.pro file if it's not
there already.

## Usage

To use the grid system you will need to import it in your qml files.

```
import com.bckmnn.gridsystem 1.0
```

You can then use the `GSGrid{}` to layout your qml. The `GSGrid` will layout all child items that have
a `GSGrid` attached property specifing the number of columns this object should occupy. See the following
example how to use it.

```
import QtQuick 2.12
import QtQuick.Window 2.12

import com.bckmnn.gridsystem 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    GSGrid{
        id: grid
        anchors.fill: parent

        columns: 12                     // sets the number of columns
        gutter: 20                      // sets the gutter width between the columns in px
        columnColor: "#3300ff00"        // sets the color of the columns for the grid overlay
                                        // see showGrid

        showGrid: true                  // displays the grid overlay

        fillStrategy: GSGrid.ITEM_BREAK   // sets the fill strategy (ITEM_BREAK / ITEM_SQUEEZE)

        onColumnWidthChanged: {
            console.log("a column is", columnWidth, "px wide")
        }

        onContentHeightChanged: {
            console.log("the layouted content of the grid have a height of ", contentHeight, "px")
        }

        MouseArea{
            anchors.fill: parent
            onClicked: parent.showGrid = !parent.showGrid
        }

        Rectangle{
            color: "red"
            height: 100
            GSGrid.colWidth: 6
        }
        Rectangle{
            color: "yellow"
            height: 110
            GSGrid.colWidth: 3
        }
        Rectangle{
            color: "orange"
            height: 80
            GSGrid.colWidth: 3
        }
        Rectangle{
            color: "blue"
            height: 80
            GSGrid.colWidth: 7
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    if(grid.fillStrategy == GSGrid.ITEM_BREAK){
                        grid.fillStrategy = GSGrid.ITEM_SQUEEZE
                    }else{
                        grid.fillStrategy = GSGrid.ITEM_BREAK
                    }
                }
            }
        }
        Rectangle{
            color: "purple"
            height: 80
            GSGrid.colWidth: 7
        }
    }
}
```
