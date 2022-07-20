import QtQuick 2.0
import Sailfish.Silica 1.0
import nl.netsoj.chris.tlstest 1.0

Item {
    id: delegateRoot
    property string url
    property var expectedErrors
    width: parent.width
    height: errorColumn.height + 2 * Theme.paddingMedium
    TlsTest {
        id: tlsTest
        url: delegateRoot.url
        onErrorsChanged: console.log(errors)
        expectedErrors: delegateRoot.expectedErrors
    }
    Column {
        id: errorColumn
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            topMargin: Theme.paddingMedium
            leftMargin: Theme.horizontalPageMargin
            rightMargin: Theme.horizontalPageMargin
        }
        Row {
            height: urlLabel.height
            anchors {
                left: parent.left
                right: parent.right
            }
            Label {
                id: urlLabel
                width: parent.width - busy.width
                text: tlsTest.url
                color: tlsTest.testSuccess ? "#00ff00" : "#ff0000";
            }

            BusyIndicator {
                id: busy
                size: BusyIndicatorSize.Small
                running: tlsTest.testRunning
            }
        }
        Repeater {
            model: tlsTest.errors
            Label {
                text: " - " + modelData
                width: errorColumn.width -  2 * Theme.horizontalPageMargin
            }
        }
    }
}
