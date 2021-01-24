import QtQuick 2.0
import QtQuick.Controls 1.0
import rogov 1.0

ApplicationWindow
{
    id: mainWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Minimal Qml")
    color: "white"

    ListView {
        id: ruler
        orientation: ListView.Horizontal
        anchors.top: mainWindow.top
        anchors.right: mainWindow.right
        anchors.left: mainWindow.left
        height: 100
        width: mainWindow.width
        model: rulerData
        delegate: Item {
            id: _backgroundDelegate
            width: ruler.width / 24
            height: 100
            Tile {
                displayText: modelData
                anchors.fill: _backgroundDelegate
            }
        }
        onWidthChanged: {
            bookmarksEngine.prepareData(ruler.contentItem.children[0].width)
        }
    }

    Repeater {
        model: bookmarksModel
        anchors.right: mainWindow.right
        anchors.left: mainWindow.left
        delegate: Rectangle {
            x: ruler.contentItem.children[model.startTime].x
            y: ruler.contentItem.children[model.startTime].y + ruler.contentItem.children[model.startTime].height
            width: ruler.contentItem.children[0].width * model.duration
            height: 40
            color: model.count > 1 ? "red" : "blue"
            opacity: 0.5
            border.width: 1
            border.color: "black"
            clip: true
            Text {
                anchors.centerIn: parent
                text: model.display
            }
        }
    }

    Rectangle {
        id: bottomPanel
        color: "grey"
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        height:50

        Rectangle {
            id: itemsCountRect
            anchors.left: bottomPanel.left + 10
            anchors.verticalCenter: parent.verticalCenter
            border.color: "black"
            border.width: 1
            width: 200
            height: 30
            TextInput {
                id: itemsCount
                anchors.fill: parent
                anchors.margins: 2
                text: ""
                property string placeholderText: "Введите число закладок"
                font {
                    pointSize: height / 1.7
                }

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    text: itemsCount.placeholderText
                    color: "#aaa"
                    visible: !itemsCount.text
                }
            }
        }

        Button {
            id: buttonLabel
            anchors.left: itemsCountRect.right
            anchors.verticalCenter: parent.verticalCenter
            text: "Генерировать"
            height: itemsCountRect.height
            onClicked: {
                bookmarksEngine.generateData(parseInt(itemsCount.text), ruler.contentItem.children[0].width)
            }
        }
    }
}
