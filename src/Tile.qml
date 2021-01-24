import QtQuick 2.0

Rectangle {
    id: root

    property string displayText: ""

    color: "white"    
    Rectangle {
        width: 1
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        color: "black"
    }
    Text {
        id: _firstText
        anchors.top: root.top
        anchors.left: parent.left + 15
        text: root.displayText
        font {
            pointSize: Math.max(root.width / 6, 1)
        }
    }
}
