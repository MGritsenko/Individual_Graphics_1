import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.2

Window {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello Individual")

    //https://www.geeksforgeeks.org/quickhull-algorithm-convex-hull/

    property var points: []
    Canvas {
        id: canvas
        anchors.fill: parent
        property var ctx: null

        property int rough: 1

        onPaint: {
            drawDot(ctx, canvas)
        }

        MouseArea {
            id:mouseArea
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton | Qt.RightButton

            onPressed: {
                if((mouseArea.pressedButtons & Qt.RightButton) == 0) {
                    var tmp = points
                    tmp = 0
                    tmp = [mouseX, mouseY]
                    points.push(tmp)
                }

                canvas.clear()
                canvas.requestPaint()
            }
        }

        Button {
            id: plus
            text: "GO!"

            onClicked: {
                doQuickHull()
                canvas.requestPaint()
            }
        }

        function clear(){
            ctx = getContext("2d");
            ctx.clearRect(0, 0, canvas.width, canvas.height)
        }

        function drawDot(ctx, canvas) {
            ctx = canvas.getContext("2d");

            if(points.length == 0){
                return
            }

            ctx.fillStyle = "limegreen"
            for(var i = 0; i < points.length; i++) {
                ctx.beginPath();
                ctx.arc(points[i][0], points[i][1], 3, 0, 2 * Math.PI)
                ctx.fill();
            }
        }

        function doQuickHull(){

        }
    }
}
