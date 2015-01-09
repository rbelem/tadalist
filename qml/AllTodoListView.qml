
import QtQuick 2.0
import QtQuick.Controls 1.1

Item {

    ScrollView {
        id: todoListScrollView

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        ListView {
            id: allTodoListView

            anchors.fill: parent
        }
    }

    ScrollView {
        anchors.top: todoListScrollView.bottom
        anchors.left: parent.left
        anchors.right: parent.right
    }

    Rectangle {
        anchors.fill: parent
        color: "blue"
    }
}
