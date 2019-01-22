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
    color: "#202020"

    SkyplotWidget {
        anchors.fill:   parent
        id:             swid
        antialiased:    true
        crosses:        3
        ellipses:       5
        flashIntervall: 300
        marginScale:    0.70
        satelliteScale: 0.06
        fontScale:      0.04
        gridColor:      "steelblue"
        gridTextColor:  "#FF0000"
        gridWidth:      4
        textMargin:     8
        withGridLabels: true
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
                  if( Math.floor( Math.random()+0.5 ) )
                  {
                     state = SatelliteState.HalfVisible
                  }

                  if( Math.floor( Math.random()+0.5 ) )
                  {
                     state = state | SatelliteState.Flashing
                  }

                  if( Math.floor( Math.random()+0.5  ) )
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
