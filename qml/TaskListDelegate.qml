
import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQml.Models 2.1

MouseArea {
    id: mouseArea

    property int taskIndex: DelegateModel.itemsIndex

    anchors.left: parent.left
    anchors.right: parent.right
    height: 30

    drag.target: taskItem
    drag.axis: Drag.YAxis

    onClicked: console.log("onTaskClicked")

    Item {
        id: taskItem
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        height: 30

        Drag.active: mouseArea.drag.active
        Drag.source: mouseArea
        Drag.hotSpot.x: 15
        Drag.hotSpot.y: 15

        states: [
            State {
                when: taskItem.Drag.active
                ParentChange {
                    target: taskItem
                    parent: taskListView
                }

                AnchorChanges {
                    target: taskItem;
                    anchors.horizontalCenter: undefined;
                    anchors.verticalCenter: undefined
                }
            }
        ]

        CheckBox {
            id: checkbox

            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter

            checked: completed
        }

        Text {
            id: taskName
            anchors.left: checkbox.right
            anchors.leftMargin: 1
            anchors.verticalCenter: checkbox.verticalCenter
            text: name

            font.pixelSize: 16
        }
    }

    DropArea {
        anchors.fill: parent
        anchors.margins: 7
        onEntered: delegateModel.items.move(drag.source.taskIndex, mouseArea.taskIndex)
    }
}
