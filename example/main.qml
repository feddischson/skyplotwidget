import QtQuick 2.0
import QtQuick.Controls 1.2
import SkyplotWidget 0.1

ApplicationWindow {

   property int idx: 0

    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("SkyplotWidget Example")

    SkyplotWidget {
        anchors.fill:   parent
        id:             swid
        antialiased:    true
        crosses:        3
        ellipses:       5
    }


    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
            MenuItem {
                text: qsTr("Add Satellite")
                onTriggered: {
                  swid.addSatellite( idx, 
                                     Math.random() * 360 , 
                                     Math.random() * 90 , 
                                     idx, 
                                     "red", 
                                     "green", 
                                     "white", 
                                     true, 
                                     Math.floor( Math.random() * 2 ), 
                                     Math.floor( Math.random() * 2 ), 
                                     Math.floor( Math.random() * 2 ) 
                                     );
                  idx = idx + 1;
               }
            }
        }
    }
}
