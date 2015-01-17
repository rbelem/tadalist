
import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQml.Models 2.1

Rectangle {
    id: taskListViewItem
    property string reorderState: "DragInactive"

    Connections {
        target: reorderMouseArea
        onClicked: {
            console.log("reorderState: " + reorderState)
            reorderState = (reorderState === "DragInactive") ? "DragActive": "DragInactive"
        }
    }

    Rectangle {
        id: descriptionItem

        property string todoListDescription: ""

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        state: "NoDescriptionAvailable"
        states: [
            State {
                name: "NoDescriptionAvailable"
                PropertyChanges { target: descriptionItem; height: addDescriptonText.height + 5 }
                PropertyChanges { target: addDescriptonText; opacity: 1; enabled: true }
                PropertyChanges { target: descriptionText; opacity: 0; enabled: false }
                PropertyChanges { target: descriptionTextArea; opacity: 0; enabled: false }
            },
            State {
                name: "DescriptionAvailable"
                PropertyChanges { target: descriptionItem; height: descriptionText.height + 5 }
                PropertyChanges { target: addDescriptonText; opacity: 0; enabled: false }
                PropertyChanges { target: descriptionText; opacity: 1; enabled: true }
                PropertyChanges { target: descriptionTextArea; opacity: 0; enabled: false }
            },
            State {
                name: "AddingDescription"
                PropertyChanges { target: descriptionItem; height: 50 }
                PropertyChanges { target: addDescriptonText; opacity: 0; enabled: false }
                PropertyChanges { target: descriptionText; opacity: 0; enabled: false }
                PropertyChanges { target: descriptionTextArea; opacity: 1; enabled: true }
            }
        ]

        Text {
            id: addDescriptonText
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: 10
            text: qsTr("Add description")
            color: "#f00"
            font.family: "Verdana"
            font.pixelSize: 10
            font.underline: true

            MouseArea {
                id: addDescriptonTextMouseArea
                anchors.fill: parent
                onClicked: {
                    descriptionItem.state = "AddingDescription"
                }
            }
        }

        Text {
            id: descriptionText
            anchors.fill: parent
            anchors.leftMargin: 10
            opacity: 0
            enabled: false
            text: parent.todoListDescription
        }

        TextArea {
            id: descriptionTextArea
            anchors.fill: parent
            anchors.margins: 5
            opacity: 0
            enabled: false
            text: parent.todoListDescription
        }
    }

    ScrollView {
        anchors.top: descriptionItem.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        ListView {
            id: taskListView
            anchors.fill: parent
            spacing: 3
            displaced: Transition {
                NumberAnimation { properties: "x,y"; easing.type: Easing.OutQuad }
            }

            model: DelegateModel {
                id: delegateModel
                model: TaskListModel {}
                delegate: TaskListDelegate {}
            }
        }
    }
}
