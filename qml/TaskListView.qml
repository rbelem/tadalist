
import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQml.Models 2.1

Rectangle {
    id: taskListViewItem
    property string reorderState: "DragInactive"

    Connections {
        target: reorderMouseArea
        onClicked: {
            console.log("reorderState: " + reorderState)
            reorderState = (reorderState === "DragInactive") ? "DragActive": "DragInactive"
        }
    }

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
                model: taskListModelProxy
                delegate: TaskListDelegate {}
            }
        }
    }
}
