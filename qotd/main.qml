import QtQuick 2.3
import QtQuick.Controls 1.2

Rectangle {
    visible: true
    width: 640
    height: 480

    Button{
        text: "Fetch";
        onClicked: {
            var result = TcpSocket.send("BUNDE!", 6, 17)
            console.debug(" RESULT IS " + result)
        }
    }
    Label {
        id : label;
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }
    Connections {
        target : TcpSocket
        onDataReceived:{
            label.text = text;
        }
    }
}
