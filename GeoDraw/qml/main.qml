import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Universal
import QtQuick.Layouts


ApplicationWindow {
    visible: true

    Universal.theme: Universal.Dark
    Universal.accent: Universal.Violet

    SplitView {
        anchors.fill: parent
        orientation: Qt.Horizontal
        
        Rectangle {
            id: toolBar
            implicitWidth: 100
            color: "transparent"

            ColumnLayout {
                id: toolColumn
                width: parent.width
                spacing: 8
                anchors.margins: 8
                anchors.centerIn: parent

                Button {
                    text: "Высота"
                    checkable: true
                    Layout.fillWidth: true
                }
                Button {
                    text: "Медиана"
                    checkable: true
                    Layout.fillWidth: true
                }
                Button {
                    text: "Биссектриса"
                    checkable: true
                    Layout.fillWidth: true
                }

                Button {
                    text: "Очистить"
                    Layout.fillWidth: true
                }
            }
        }
        
        Rectangle {
            id: workspace
            implicitWidth: 800
            color: "transparent"
        
            Canvas {
                id: mycanvas
                anchors.centerIn: parent
		width: 700
		height: 700
                onPaint: {
                    var ctx = getContext("2d");
                    ctx.fillStyle = "white"; 
                    ctx.fillRect(0, 0, width, height);
                }
            }
        }
        
        Rectangle {
            id: statusBar
            implicitWidth: 200
            color: "transparent"
        }
    }
}

