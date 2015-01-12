
import QtQuick 2.0
import QtQuick.Controls 1.1

Component {

    Item {

        width: 200
        height: 30

        CheckBox {
            id: checkbox

            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter

            checked: completed
        }

        Text {
            id: taskName
            anchors.left: checkbox.right
            anchors.leftMargin: 1
            anchors.verticalCenter: checkbox.verticalCenter
            text: name

            MouseArea {
                anchors.fill: parent
                onClicked: console.log("onTaskClicked")
            }
        }
    }
}
