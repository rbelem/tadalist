
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
            id: todoListNameText
            anchors.left: dot.right
            anchors.leftMargin: 10
            anchors.verticalCenter: dot.verticalCenter
            text: todoListName

            color: "#03c"
            font.family: "Lucinda Grande"
            font.pixelSize: 16
            font.weight: Font.Bold
            font.underline: true

            MouseArea {
                anchors.fill: parent
                onClicked: onTodoListClicked(todoListId, todoListName, todoListDescription)
            }
        }

        Text {
            id: todoListLeft
            anchors.left: todoListNameText.right
            anchors.leftMargin: 10
            anchors.verticalCenter: todoListNameText.verticalCenter
            text: "—  " + tasksLeft + " left"
        }
    }
}
