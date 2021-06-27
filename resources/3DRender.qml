import QtQuick 2.0

Item {
    id: item1

    Text {
        id: text1
        x: 275
        y: 8
        width: 91
        height: 64
        color: "#b70000"
        text: qsTr("Test")
        font.pixelSize: 40
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }


}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
