import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Universal
import QtQuick.Layouts
import Pts 1.0


ApplicationWindow {
    visible: true

    Universal.theme: Universal.Dark
    Universal.accent: Universal.Violet

    Points {
        id: pts
    }

    // update on points changed
    Connections {
        target: pts
        function onPointsChanged() { canvasArea.requestPaint() }
    }

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
                    id: heightBtn
                    text: "Высота"
                    checkable: true
                    Layout.fillWidth: true
                    onClicked: {
                        if (checked) {
                            medianBtn.checked = false
                            bisectorBtn.checked = false
                            canvasArea.requestPaint()
                        }
                    }
                }
                Button {
                    id: medianBtn
                    text: "Медиана"
                    checkable: true
                    Layout.fillWidth: true
                    onClicked: {
                        if (checked) {
                            heightBtn.checked = false
                            bisectorBtn.checked = false
                            canvasArea.requestPaint()
                        }
                    }
                }
                Button {
                    id: bisectorBtn
                    text: "Биссектриса"
                    checkable: true
                    Layout.fillWidth: true
                    onClicked: {
                        if (checked) {
                            heightBtn.checked = false
                            medianBtn.checked = false
                            canvasArea.requestPaint()
                        }
                    }
                }

                Button {
                    text: "Очистить"
                    Layout.fillWidth: true
                    onClicked: {
                        pts.removeAllPoints();
                    }
                }

                Button {
                    text: "Удалить\nпоследнюю\nточку"
                    Layout.fillWidth: true
                    onClicked: {
                        pts.removeLastPoint();
                    }
                }
            }
        }
        
        Rectangle {
            id: workspace
            implicitWidth: 800
            color: "transparent"
        
            Canvas {
                id: canvasArea
                anchors.centerIn: parent
                width: 700
                height: 700

                onPaint: {
                    const ctx = getContext("2d")
                    ctx.fillStyle = "white"
                    ctx.fillRect(0, 0, width, height)

                    function valid(p) { return !(isNaN(p.x) || isNaN(p.y)) }
                    
                    function dot(p, r) {
                        ctx.beginPath()
                        ctx.arc(p.x, p.y, r, 0, Math.PI * 2)
                        ctx.fillStyle = "black"
                        ctx.fill()
                    }

                    // dots
                    if (valid(pts.firstPoint))  dot(pts.firstPoint, 3)
                    if (valid(pts.secondPoint)) dot(pts.secondPoint, 3)
                    if (valid(pts.thirdPoint))  dot(pts.thirdPoint, 3)

                    // line between 1 - 2
                    if (valid(pts.firstPoint) && valid(pts.secondPoint)) {
                        ctx.beginPath()
                        ctx.moveTo(pts.firstPoint.x, pts.firstPoint.y)
                        ctx.lineTo(pts.secondPoint.x, pts.secondPoint.y)
                        ctx.stroke()
                    }

                    if (valid(pts.heightPoint) && heightBtn.checked) {
                        dot(pts.heightPoint, 3)
                        
                        ctx.beginPath()
                        ctx.moveTo(pts.thirdPoint.x, pts.thirdPoint.y)
                        ctx.lineTo(pts.heightPoint.x, pts.heightPoint.y)
                        ctx.stroke()
                    }
                }

                // add points by mouse
                MouseArea {
                    anchors.fill: parent
                    acceptedButtons: Qt.LeftButton
                    onClicked: function(mouse) {
                        const p = Qt.vector3d(mouse.x, mouse.y, 0)
                        const n = pts.pointsCount()
                        if (n === 0)      pts.firstPoint  = p
                        else if (n === 1) pts.secondPoint = p
                        else if (n === 2) pts.thirdPoint  = p
                        // if have 3 points - do nothing
                        canvasArea.requestPaint()
                    }
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

