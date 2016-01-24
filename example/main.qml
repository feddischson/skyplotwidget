import QtQuick 2.0
import QtQuick.Controls 1.2
import SkyplotWidget 2.0
import SatelliteState 2.0

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
                  var state = SatelliteState.Visible
                  if( Math.floor( Math.random() * 2 ) )
                  {
                     state = SatelliteState.HalfVisible
                  }

                  if( Math.floor( Math.random() * 2 ) )
                  {
                     state = state | SatelliteState.Blinking
                  }

                  if( Math.floor( Math.random() * 2 ) )
                  {
                     state = state | SatelliteState.Marked
                  }

                  swid.insert( idx, 
                               Math.random() * 360 , 
                               Math.random() * 90 , 
                               idx, 
                               "red", 
                               "green", 
                               "white",
                               state
                               );
                  idx = idx + 1;
               }
            }
        }
    }
}
