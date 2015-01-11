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
        color: "#ffffff"
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        height: 50

        Text {
            id: myListTextId
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 30
            text: qsTr("My List")
            font.pixelSize: 20

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    stackView.pop()
                    todoListTextId.opacity = 0
                }
            }
        }

        Text {
            id: todoListTextId
            anchors.verticalCenter: myListTextId.verticalCenter
            anchors.left: myListTextId.right
            anchors.leftMargin: 30
            opacity: 0
            text: qsTr("Todo List")
            font.pixelSize: 20
        }
    }

    StackView {
        id: stackView
        anchors.fill: parent

        initialItem: allTodoListView

        onDepthChanged: console.log("StackView depth changed")
    }
}
