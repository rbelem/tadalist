
import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQml.Models 2.1

Rectangle {
    ScrollView {
        anchors.fill: parent

        ListView {
            id: taskListView
            anchors.fill: parent
            spacing: 3
            displaced: Transition {
                NumberAnimation { properties: "x,y"; easing.type: Easing.OutQuad }
            }

            model: DelegateModel {
                id: delegateModel
                model: TaskListModel {}
                delegate: TaskListDelegate {}
            }
        }
    }
}
