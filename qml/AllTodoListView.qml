
import QtQuick 2.0
import QtQuick.Controls 1.1

Item {

    ScrollView {
        id: todoListScrollView

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: doneListItem.top

        ListView {
            id: allTodoListView

            anchors.fill: parent
            model: FakeListModel {}
            delegate: AllTodoListDelegate {}
        }
    }

    Item {
        id: doneListItem

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
                id: allDoneListView

                model: FakeListModel {}
                delegate: Text {
                    text: name + ","

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            stackView.push({item: todoListView, properties: {name: name}})
                            todoListTextId.text = name
                            todoListTextId.opacity = 1.0
                        }
                    }
                }
            }
        }
    }
}
