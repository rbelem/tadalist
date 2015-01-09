
import QtQuick 2.2
import QtQuick.Controls 1.2

Item {

    property string name: ""

    ScrollView {
        id: todoListScrollView

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        ListView {
            id: todoListView

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
        color: "cyan"
    }
}
