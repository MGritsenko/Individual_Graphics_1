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
    property var rotPolygon: []
    property var rotPolygon2: []
    Canvas {
        id: canvas
        anchors.fill: parent
        property var ctx: null

        property int rough: 1

        onPaint: {
            drawDot(ctx, canvas)
            drawPolygon(ctx, canvas)
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
                canvas.doQuickHull()
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
            rotPolygon = QuickHull.printHull(points, false);
            rotPolygon2 = QuickHull.printHull(points, true);

            canvas.requestPaint()
        }

        function drawPolygon(ctx, canvas){
            ctx = canvas.getContext("2d");

            if(rotPolygon.length === 0 || rotPolygon2.length == 0){
                return
            }

            ctx.lineWidth = 2;
            ctx.strokeStyle = "limegreen"

            ctx.beginPath()
            ctx.moveTo(rotPolygon[0][0], rotPolygon[0][1])

            for(var i = 1; i < rotPolygon.length; i++) {
                ctx.lineTo(rotPolygon[i][0], rotPolygon[i][1])
            }

            ctx.moveTo(rotPolygon2[0][0], rotPolygon2[0][1])

            for(i = 1; i < rotPolygon2.length; i++) {
                ctx.lineTo(rotPolygon2[i][0], rotPolygon2[i][1])
            }

            ctx.stroke()
        }
    }
}
