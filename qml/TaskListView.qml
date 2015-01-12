
import QtQuick 2.0
import QtQuick.Controls 1.1

Item {

    ScrollView {

        anchors.fill: parent

        ListView {
            id: listView

            anchors.fill: parent
            model: TaskListModel {}
            delegate: TaskListDelegate {}
        }
    }
}
