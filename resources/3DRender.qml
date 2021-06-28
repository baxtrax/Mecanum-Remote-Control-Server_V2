import QtQuick 2.0

Rectangle {
    id: backgroundRecBorder
    anchors.centerIn: parent
    anchors.fill: parent
    color: "#05050f"
    border.color: "#dd0000"
    border.width: 10

    Text {
        id: text1
        x: 272
        y: 110
        width: 96
        height: 53
        color: "#c40000"
        text: qsTr("TEST")
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 40
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
    }

}



/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
