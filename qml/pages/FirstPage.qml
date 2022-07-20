import QtQuick 2.6
import Sailfish.Silica 1.0
import QtQml.Models 2.2


import "../components"

Page {
    id: page

    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.All

    ObjectModel {
        id: errorsList
        TlsTestDelegate { url: "https://badssl.com/"; expectedErrors: [] }
        TlsTestDelegate { url: "https://expired.badssl.com/"; expectedErrors: [6 /* expired */] }
        TlsTestDelegate { url: "https://wrong.host.badssl.com/"; expectedErrors: [22 /* host name mismatch*/] }
        TlsTestDelegate { url: "https://self-signed.badssl.com/"; expectedErrors: [9 /* self signed certificate */] }
        TlsTestDelegate { url: "https://untrusted-root.badssl.com/"; expectedErrors: [10 /* self signed certificate in chain */] }
    }

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaListView {
        anchors.fill: parent

        // Place our content in a Column.  The PageHeader is always placed at the top
        // of the page, followed by our content.
        header: PageHeader {
            title: qsTr("TLS test")
        }

        model: errorsList
    }
}
