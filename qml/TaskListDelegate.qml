
import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQml.Models 2.1
import com.ics.tadalist 0.1

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

        state: reorderState

        states: [
            State {
                when: taskItem.Drag.active
                ParentChange {
                    target: taskItem
                    parent: taskListView
                }

                AnchorChanges {
                    target: taskItem
                    anchors.horizontalCenter: undefined
                    anchors.verticalCenter: undefined
                }
            },
            State {
                when: checkbox.checked
                PropertyChanges { target: mouseArea; enabled: false }
                PropertyChanges { target: deleteImage; visible: false  }
                PropertyChanges { target: dragImage; visible: false  }
                PropertyChanges { target: checkbox; enabled: true  }
                PropertyChanges { target: taskNameText; enabled: true; visible: true; font.pixelSize: 10; color: "#999" }
                PropertyChanges { target: taskNameMouseArea; enabled: false }
                PropertyChanges { target: taskNameField; enabled: false; visible: false }
            },
            State {
                when: checkbox.checked == false
                PropertyChanges { target: mouseArea; enabled: true}
                PropertyChanges { target: deleteImage; visible: false  }
                PropertyChanges { target: dragImage; visible: false  }
                PropertyChanges { target: checkbox; enabled: true  }
                PropertyChanges { target: taskNameText; enabled: true; visible: true; font.pixelSize: 16; color: "#000" }
                PropertyChanges { target: taskNameMouseArea; enabled: true }
                PropertyChanges { target: taskNameField; enabled: false; visible: false }
            },
            State {
                name: "DragActive"
                AnchorChanges { target: checkbox; anchors.left: dragImage.right }

                PropertyChanges { target: mouseArea; enabled: true  }
                PropertyChanges { target: deleteImage; visible: false  }
                PropertyChanges { target: dragImage; visible: true  }
                PropertyChanges { target: checkbox; enabled: false  }
                PropertyChanges { target: taskNameText; enabled: true; visible: true }
                PropertyChanges { target: taskNameMouseArea; enabled: false }
                PropertyChanges { target: taskNameField; enabled: false; visible: false }
            },
            State {
                name: "DragInactive"
                AnchorChanges { target: checkbox; anchors.left: parent.left }

                PropertyChanges { target: mouseArea; enabled: false  }
                PropertyChanges { target: deleteImage; visible: false  }
                PropertyChanges { target: dragImage; visible: false  }
                PropertyChanges { target: checkbox; enabled: true  }
                PropertyChanges { target: taskNameText; enabled: true; visible: true }
                PropertyChanges { target: taskNameMouseArea; enabled: true }
                PropertyChanges { target: taskNameField; enabled: false; visible: false }
            }
        ]

        Image {
            id: deleteImage
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            source: "grey_delete.gif"

            MouseArea {
                anchors.fill: parent
                onClicked: taskListModelProxy.removeItem(index)
            }
        }

        Image {
            id: dragImage
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            source: "drag.gif"
        }

        CheckBox {
            id: checkbox

            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            checked: taskCompleted

            onClicked: taskListModelProxy.updateItem(index, checked, TaskListModel.CompletedRole)
        }

        Text {
            id: taskNameText
            anchors.left: checkbox.right
            anchors.leftMargin: 1
            anchors.verticalCenter: checkbox.verticalCenter
            text: taskName

            font.pixelSize: 16

            MouseArea {
                id: taskNameMouseArea
                anchors.fill: parent

                onClicked: {
                    taskListView.currentIndex = index
                    deleteImage.visible = true
                    checkbox.anchors.left = deleteImage.right
                    taskNameText.visible = false
                    taskNameText.enabled = false
                    taskNameField.visible = true
                    taskNameField.enabled = true
                    taskNameField.focus = true
                }
            }
        }

        TextField {
            id: taskNameField
            anchors.left: checkbox.right
            anchors.leftMargin: 1
            anchors.verticalCenter: checkbox.verticalCenter
            text: taskName

            font.pixelSize: 16

            onEditingFinished: {
                taskListModelProxy.updateItem(index, text, TaskListModel.TaskNameRole)
                deleteImage.visible = false
                checkbox.anchors.left = parent.left
                taskNameText.visible = true
                taskNameText.enabled = true
                taskNameField.visible = false
                taskNameField.enabled = false
            }
        }
    }

    DropArea {
        anchors.fill: parent
        anchors.margins: 7
        onEntered: delegateModel.items.move(drag.source.taskIndex, mouseArea.taskIndex)
        onDropped: console.log("dropped")
        onPositionChanged: {
            mouseArea.state = "DragActive"
            mouseArea.enabled = true
            deleteImage.visible = false
            dragImage.visible = true
            checkbox.anchors.left = dragImage.right
            checkbox.enabled = false
            taskNameText.enabled = true
            taskNameText.visible = true
            taskNameMouseArea.enabled = false
            taskNameField.enabled = false
            taskNameField.visible = false
        }
    }
}
