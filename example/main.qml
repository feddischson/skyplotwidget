import QtQuick 2.0
import QtQuick.Controls 1.2
import SkyplotWidget 0.1

ApplicationWindow {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("SkyplotWidget Example")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    SkyplotWidget {
        anchors.fill: parent
    }

}
