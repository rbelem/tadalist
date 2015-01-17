import QtQuick 2.0
import QtQuick.Controls 1.1

ApplicationWindow {
    id: mainWindow
    title: qsTr("My List")
    width: 640
    height: 480
    visible: true

    property Component allTodoListView: TadaListView {}
    property Component taskListView: TaskListView {}

    toolBar: Rectangle {
        id: tadaListToolBar
        color: "#ffffff"
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        height: 70

        state: "tadaListScreen"

        states: [
            State {
                name: "tadaListScreen"
                PropertyChanges { target: myListTextIdMouseArea; enabled: false }
                PropertyChanges { target: sep; opacity: 0 }
                PropertyChanges { target: todoListTextId; opacity: 0; enabled: false }
                PropertyChanges { target: newListText; opacity: 1; enabled: true }
                PropertyChanges { target: newTaskText; opacity: 0; enabled: false }
                PropertyChanges { target: optionsSep; opacity: 0; enabled: false }
                PropertyChanges { target: reorderText; opacity: 0; enabled: false }
                PropertyChanges { target: tadaListInnerToolBar; width: 300 }
            },
            State {
                name: "taskListScreen"
                PropertyChanges { target: myListTextIdMouseArea; enabled: true }
                PropertyChanges { target: sep; opacity: 1 }
                PropertyChanges { target: todoListTextId; opacity: 1; enabled: true }
                PropertyChanges { target: newListText; opacity: 0; enabled: false }
                PropertyChanges { target: newTaskText; opacity: 1; enabled: true }
                PropertyChanges { target: optionsSep; opacity: 1; enabled: true }
                PropertyChanges { target: reorderText; opacity: 1; enabled: true }
                PropertyChanges { target: tadaListInnerToolBar;
                    width: myListTextId.width + sep.width + todoListTextId.width
                            + newTaskText.width + optionsSep.width + reorderText.width + 100 }
            }
        ]

        Image {
            id: tadaListLogo

            z: 1
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 10

            source: "tada-mark-bg.gif"
        }

        Rectangle {
            id: tadaListInnerToolBar
            anchors.left: tadaListLogo.right
            anchors.leftMargin: -15
            anchors.bottom: tadaListLogo.bottom
            anchors.bottomMargin: 2

            height: 39
            width: 300
            radius: 20
            color: "#efefef"

            Text {
                id: myListTextId
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 24
                text: qsTr("My List")
                font.pixelSize: 23
                font.family: "Arial"
                font.weight: Font.Bold

                MouseArea {
                    id: myListTextIdMouseArea
                    anchors.fill: parent
                    onClicked: {
                        stackView.pop()
                        tadaListToolBar.state = "tadaListScreen"
                    }
                }
            }

            Text {
                id: sep
                anchors.verticalCenter: myListTextId.verticalCenter
                anchors.left: myListTextId.right
                anchors.leftMargin: 5
                text: "/"
                font.pixelSize: 23
            }

            Text {
                id: todoListTextId
                anchors.verticalCenter: sep.verticalCenter
                anchors.left: sep.right
                anchors.leftMargin: 5
                text: qsTr("Todo List Name")
                font.pixelSize: 23
            }

            Text {
                id: newListText
                anchors.left: myListTextId.right
                anchors.leftMargin: 12
                anchors.bottom: myListTextId.bottom
                anchors.bottomMargin: 2
                text: qsTr("Create a new list")
                color: "#f00"
                font.family: "Verdana"
                font.pixelSize: 10
                font.underline: true
            }

            Text {
                id: newTaskText
                anchors.left: todoListTextId.right
                anchors.leftMargin: 12
                anchors.bottom: myListTextId.bottom
                anchors.bottomMargin: 2
                text: qsTr("Add another item")
                color: "#f00"
                font.family: "Verdana"
                font.pixelSize: 10
                font.underline: true
            }

            Text {
                id: optionsSep
                anchors.left: newTaskText.right
                anchors.leftMargin: 3
                anchors.bottom: myListTextId.bottom
                anchors.bottomMargin: 2
                text: "|"
                color: "#000000"
                font.family: "Verdana"
                font.pixelSize: 10
            }

            Text {
                id: reorderText
                anchors.left: optionsSep.right
                anchors.leftMargin: 3
                anchors.bottom: myListTextId.bottom
                anchors.bottomMargin: 2
                text: qsTr("Reorder")
                color: "#f00"
                font.family: "Verdana"
                font.pixelSize: 10
                font.underline: true

                MouseArea {
                    id: reorderMouseArea
                    anchors.fill: parent
                }
            }
        }
    }

    StackView {
        id: stackView
        anchors.fill: parent

        initialItem: allTodoListView

        onDepthChanged: console.log("StackView depth changed")
    }
}
