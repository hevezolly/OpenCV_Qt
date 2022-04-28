import QtQuick 2.15
import QtQuick.Window 2.15
import QtMultimedia 5.4
import QtQuick.Controls 2.0

import com.opencv.filter 1.0

Item {
    id: root
    signal processButtonPressed()

    VideoOutput {
        id: viewfinder
        visible: true
        width: parent.width
        autoOrientation: true
        height: parent.height
        fillMode: VideoOutput.PreserveAspectCrop
        //filters: [ filter ]
        source: camera

        OpencvFilter {
            id: filter
        }

    }

    Image {
        id: photoPreview
        objectName: "photoPreview"
        fillMode: VideoOutput.PreserveAspectCrop
        anchors.fill: parent
        visible: false
        source: ""
    }

    Button {
            id: processButton
            visible: true
            text: "Process"
            height: parent.height * 0.09
            anchors.margins: 10
            background: Rectangle {
                color: parent.down ? "#00805e" :
                        (parent.hovered ? "#00cc96" : "#00b386")
                radius: 20
            }
            onClicked : {
                backButton.visible = true;
                visible = false;
                root.processButtonPressed();
            }

            anchors.right: parent.right
            anchors.left: parent.left
            anchors.bottom: parent.bottom
        }

    Button {
            id: backButton
            visible: false
            text: "Back"
            height: parent.height * 0.09
            anchors.margins: 10
            background: Rectangle {
                color: parent.down ? "#00805e" :
                        (parent.hovered ? "#00cc96" : "#00b386")
                radius: 20
            }
            onClicked : {
                processButton.visible = true;
                photoPreview.visible = false;
                visible = false;
                photoPreview.source = ""
            }

            anchors.right: parent.right
            anchors.left: parent.left
            anchors.bottom: parent.bottom
        }

    Camera {
        focus.focusMode: CameraFocus.FocusContinuous
        id: camera
        objectName: "camera"
    }
}
