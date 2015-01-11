
import QtQuick 2.0
import QtQuick.Controls 1.1

Component {

    Item {

        width: 200
        height: 30

        Rectangle {
            id: dot

            width: 6
            height: 6
            radius: 3

            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            color: "gray"
        }

        Text {
            id: todoListName
            anchors.left: dot.right
            anchors.leftMargin: 10
            anchors.verticalCenter: dot.verticalCenter
            text: name
        }

        Text {
            id: todoListLeft
            anchors.left: todoListName.right
            anchors.leftMargin: 10
            anchors.verticalCenter: todoListName.verticalCenter
            text: "- " + lefting + " left"
        }
    }
}
