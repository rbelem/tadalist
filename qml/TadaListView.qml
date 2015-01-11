
import QtQuick 2.0
import QtQuick.Controls 1.1

Item {

    function onTodoListClicked(name) {
        stackView.push({item: taskListView, properties: {name: name}})
        todoListTextId.text = name
        todoListTextId.opacity = 1.0
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
            model: TodoListModel {}
            delegate: TodoListDelegate {}
        }
    }

    Item {
        id: completedListItem

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        height: 100

        Flow {
            anchors.fill: parent
            anchors.topMargin: 10
            anchors.margins: 4
            spacing: 5

            Repeater {
                id: completedListRepeater

                model: TodoListModel {}
                delegate: Text {
                    text: name + ","

                    MouseArea {
                        anchors.fill: parent
                        onClicked: onTodoListClicked(name)
                    }
                }
            }
        }
    }
}
