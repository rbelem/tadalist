
import QtQuick 2.0
import QtQuick.Controls 1.1

Rectangle {

    function onTodoListClicked(id, name, description) {
        taskListModelProxy.setTodoListId(id)
        stackView.push({item: taskListView, properties: {}})
        todoListToolBar.currentTodoListId = id
        todoListTextId.text = name
        descriptionText.text = description
        descriptionTextArea.text = description

        var str = descriptionText.text
        if (str.trim().length === 0)
            todoListToolBar.state = "taskListScreenAddDescription"
        else
            todoListToolBar.state = "taskListScreenShowDescription"
    }

    ScrollView {
        id: todoListScrollView

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: completedListItem.top

        ListView {
            id: todoListView

            anchors.fill: parent
            anchors.leftMargin: 10
            model: todoListModelUnfinished
            delegate: TodoListDelegate {}
        }
    }

    Rectangle {
        id: completedListItem

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        height: 70

        Text {
            id: completedListText

            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.top: parent.top
            anchors.topMargin: 10

            text: qsTr("Completed lists:")
            font.pixelSize: 9
        }

        Flow {
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.left: completedListText.right
            anchors.leftMargin: 5
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            spacing: 5

            Repeater {
                id: completedListRepeater

                model: todoListModelCompleted
                delegate: Text {
                    text: todoListName + ","
                    color: "#03c"
                    font.pixelSize: 9
                    font.underline: true

                    MouseArea {
                        anchors.fill: parent
                        onClicked: onTodoListClicked(name)
                    }
                }
            }
        }
    }
}
