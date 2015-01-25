import QtQuick 2.0
import QtQuick.Controls 1.1
import com.ics.tadalist 0.1

ApplicationWindow {
    id: mainWindow
    title: qsTr("My List")
    width: 640
    height: 480
    visible: true

    property Component allTodoListView: TodoListView {}
    property Component taskListView: TaskListView {}

    toolBar: Rectangle {
        id: todoListToolBar

        property int currentTodoListId: -1

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        height: 70

        state: "todoListScreen"

        states: [
            State {
                name: "todoListScreen"
                PropertyChanges { target: todoListToolBar; height: 70 }
                PropertyChanges { target: myListTextIdMouseArea; enabled: false }
                PropertyChanges { target: sep; opacity: 0 }
                PropertyChanges { target: todoListTextField; opacity: 0; enabled: false }
                PropertyChanges { target: todoListTextId; opacity: 0; enabled: false }
                PropertyChanges { target: newListText; opacity: 1; enabled: true }
                PropertyChanges { target: newTaskText; opacity: 0; enabled: false }
                PropertyChanges { target: optionsSep; opacity: 0; enabled: false }
                PropertyChanges { target: reorderText; opacity: 0; enabled: false }
                PropertyChanges { target: todoListInnerToolBar; width: 300 }
                PropertyChanges { target: descriptionItem; opacity: 0; enabled: false }
            },
            State {
                name: "taskListScreen"
                PropertyChanges { target: todoListToolBar; height: 70 + descriptionItem.height  }
                PropertyChanges { target: myListTextIdMouseArea; enabled: true }
                PropertyChanges { target: sep; opacity: 1 }
                PropertyChanges { target: todoListTextField; opacity: 0; enabled: false }
                PropertyChanges { target: todoListTextId; opacity: 1; enabled: true }
                PropertyChanges { target: newListText; opacity: 0; enabled: false }
                PropertyChanges { target: newTaskText; opacity: 1; enabled: true }
                PropertyChanges { target: optionsSep; opacity: 1; enabled: true }
                PropertyChanges { target: reorderText; opacity: 1; enabled: true }
                PropertyChanges { target: todoListInnerToolBar;
                    width: myListTextId.width + sep.width + todoListTextId.width
                            + newTaskText.width + optionsSep.width + reorderText.width + 100 }
                PropertyChanges { target: descriptionItem; opacity: 1; enabled: true }
            },
            State {
                name: "taskListScreenNameEdit"
                PropertyChanges { target: todoListToolBar; height: 70 }
                PropertyChanges { target: myListTextIdMouseArea; enabled: false }
                PropertyChanges { target: sep; opacity: 1 }
                PropertyChanges { target: todoListTextField; opacity: 1; enabled: true; focus: true }
                PropertyChanges { target: todoListTextId; opacity: 0; enabled: false }
                PropertyChanges { target: newListText; opacity: 0; enabled: false }
                PropertyChanges { target: newTaskText; opacity: 0; enabled: false }
                PropertyChanges { target: optionsSep; opacity: 0; enabled: false }
                PropertyChanges { target: reorderText; opacity: 0; enabled: false }
                PropertyChanges { target: todoListInnerToolBar;
                    width: myListTextId.width + sep.width + todoListTextId.width
                            + newTaskText.width + optionsSep.width + reorderText.width + 100 }
                PropertyChanges { target: descriptionItem; opacity: 0; enabled: false }
            },
            State {
                name: "taskListScreenDescriptionEdit"
                PropertyChanges { target: todoListToolBar; height: 70 }
                PropertyChanges { target: myListTextIdMouseArea; enabled: false }
                PropertyChanges { target: sep; opacity: 1 }
                PropertyChanges { target: todoListTextField; opacity: 0; enabled: false }
                PropertyChanges { target: todoListTextId; opacity: 1; enabled: true }
                PropertyChanges { target: newListText; opacity: 0; enabled: false }
                PropertyChanges { target: newTaskText; opacity: 0; enabled: false }
                PropertyChanges { target: optionsSep; opacity: 0; enabled: false }
                PropertyChanges { target: reorderText; opacity: 0; enabled: false }
                PropertyChanges { target: todoListInnerToolBar;
                    width: myListTextId.width + sep.width + todoListTextId.width
                            + newTaskText.width + optionsSep.width + reorderText.width + 100 }
                PropertyChanges { target: descriptionItem; opacity: 1; enabled: true }
            }
        ]

        Image {
            id: todoListLogo

            z: 1
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 10

            source: "tada-mark-bg.gif"
        }

        Rectangle {
            id: todoListInnerToolBar
            anchors.left: todoListLogo.right
            anchors.leftMargin: -15
            anchors.bottom: todoListLogo.bottom
            anchors.bottomMargin: 2

            height: 39
            width: 300
            radius: 20
            color: "#efefef"

            Text {
                id: myListTextId
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 24
                text: qsTr("My List")
                font.pixelSize: 23
                font.family: "Arial"
                font.weight: Font.Bold

                MouseArea {
                    id: myListTextIdMouseArea
                    anchors.fill: parent
                    onClicked: {
                        stackView.pop()
                        todoListToolBar.state = "todoListScreen"
                    }
                }
            }

            Text {
                id: sep
                anchors.verticalCenter: myListTextId.verticalCenter
                anchors.left: myListTextId.right
                anchors.leftMargin: 5
                text: "/"
                font.pixelSize: 23
            }

            TextField {
                id: todoListTextField
                anchors.verticalCenter: sep.verticalCenter
                anchors.left: sep.right
                anchors.leftMargin: 5
                font.pixelSize: 23

                onEditingFinished: {
                    todoListModel.updateItem(todoListToolBar.currentTodoListId, TodoListModel.TodoListNameRole, text)
                    todoListTextId.text = text
                    todoListToolBar.state = "taskListScreen"
                }
            }

            Text {
                id: todoListTextId
                anchors.verticalCenter: sep.verticalCenter
                anchors.left: sep.right
                anchors.leftMargin: 5
                text: qsTr("Todo List Name")
                font.pixelSize: 23
            }

            Text {
                id: newListText
                anchors.left: myListTextId.right
                anchors.leftMargin: 12
                anchors.bottom: myListTextId.bottom
                anchors.bottomMargin: 2
                text: qsTr("Create a new list")
                color: "#f00"
                font.family: "Verdana"
                font.pixelSize: 10
                font.underline: true

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        var currentTodoListItem = todoListModel.addItem()
                        todoListToolBar.currentTodoListId = currentTodoListItem.id
                        taskListModelProxy.setTodoListId(currentTodoListItem.id)
                        todoListTextField.text = currentTodoListItem.name
                        descriptionText.text = ""
                        descriptionTextArea.text = ""
                        stackView.push({item: taskListView, properties: {}})
                        todoListToolBar.state = "taskListScreenNameEdit"
                        descriptionItem.state = "NoDescriptionAvailable"
                    }
                }
            }

            Text {
                id: newTaskText
                anchors.left: todoListTextId.right
                anchors.leftMargin: 12
                anchors.bottom: myListTextId.bottom
                anchors.bottomMargin: 2
                text: qsTr("Add another item")
                color: "#f00"
                font.family: "Verdana"
                font.pixelSize: 10
                font.underline: true

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        console.log("New task")
                    }
                }
            }

            Text {
                id: optionsSep
                anchors.left: newTaskText.right
                anchors.leftMargin: 3
                anchors.bottom: myListTextId.bottom
                anchors.bottomMargin: 2
                text: "|"
                color: "#000000"
                font.family: "Verdana"
                font.pixelSize: 10
            }

            Text {
                id: reorderText
                anchors.left: optionsSep.right
                anchors.leftMargin: 3
                anchors.bottom: myListTextId.bottom
                anchors.bottomMargin: 2
                text: qsTr("Reorder")
                color: "#f00"
                font.family: "Verdana"
                font.pixelSize: 10
                font.underline: true

                MouseArea {
                    id: reorderMouseArea
                    anchors.fill: parent
                }
            }
        }

        Item {
            id: descriptionItem

            anchors.top: todoListInnerToolBar.bottom
            anchors.topMargin: 15
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: parent.right

            state: "NoDescriptionAvailable"
            states: [
                State {
                    name: "NoDescriptionAvailable"
                    PropertyChanges { target: descriptionItem; height: addDescriptonText.height + 5 }
                    PropertyChanges { target: addDescriptonText; opacity: 1; enabled: true }
                    PropertyChanges { target: descriptionText; opacity: 0; enabled: false }
                    PropertyChanges { target: descriptionTextArea; opacity: 0; enabled: false }
                },
                State {
                    name: "DescriptionAvailable"
                    PropertyChanges { target: descriptionItem; height: descriptionText.height + 5 }
                    PropertyChanges { target: addDescriptonText; opacity: 0; enabled: false }
                    PropertyChanges { target: descriptionText; opacity: 1; enabled: true }
                    PropertyChanges { target: descriptionTextArea; opacity: 0; enabled: false }
                },
                State {
                    name: "AddingDescription"
                    PropertyChanges { target: todoListToolBar; state: "taskListScreenDescriptionEdit" }
                    PropertyChanges { target: descriptionItem; height: 50 }
                    PropertyChanges { target: addDescriptonText; opacity: 0; enabled: false }
                    PropertyChanges { target: descriptionText; opacity: 0; enabled: false }
                    PropertyChanges { target: descriptionTextArea; opacity: 1; enabled: true }
                }
            ]

            Text {
                id: addDescriptonText
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.leftMargin: 10
                text: qsTr("Add description")
                color: "#f00"
                font.family: "Verdana"
                font.pixelSize: 10
                font.underline: true

                MouseArea {
                    id: addDescriptonTextMouseArea
                    anchors.fill: parent
                    onClicked: {
                        descriptionItem.state = "AddingDescription"
                    }
                }
            }

            Text {
                id: descriptionText
                anchors.fill: parent
                anchors.leftMargin: 10
                opacity: 0
                enabled: false
            }

            TextArea {
                id: descriptionTextArea
                anchors.fill: parent
                anchors.margins: 5
                opacity: 0
                enabled: false

                function saveDescription(description) {
                    todoListModel.updateItem(todoListToolBar.currentTodoListId, TodoListModel.TodoListDescriptionRole, description)
                    descriptionText.text = text

                    if (descriptionTextArea.length > 0)
                        descriptionItem.state = "DescriptionAvailable"
                    else
                        descriptionItem.state = "NoDescriptionAvailable"
                }

                Keys.onPressed: {
                    if ((Qt.Key_Escape === event.key) || ((Qt.Key_Return === event.key) && (event.modifiers === 0))) {
                        saveDescription(text)
                    }
                }
            }
        }
    }

    StackView {
        id: stackView
        anchors.fill: parent

        initialItem: allTodoListView

        onDepthChanged: console.log("StackView depth changed")
    }
}
