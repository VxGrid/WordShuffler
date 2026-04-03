import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    visible: true
    width: 400
    height: 300

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 10

        Label {
            text: "Enter some text and press Enter<br>
                    The text will get shuffled<br>and copied to your clipboard"
        }

        TextField {
            id: inputField
            text: backend.text
            //anchors.centerIn: parent
            width: 300
            placeholderText: "Enter text"

            focus: true  // gives focus on startup → opens keyboard (on supported platforms)

            onAccepted: {
                    backend.processText(text)
                }
        }
    }
}