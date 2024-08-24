import QtQuick 2.14
import QtQuick.Window 2.14

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Weather in Tokyo")

    Rectangle {
        anchors.centerIn: parent
        width: childrenRect.width
        height: childrenRect.height
        color: "lightgray"
        border {
            width: 1.0
            color: "black"
        }

        Column {
            spacing: 20

            Text {
                id: label
                font.bold: true
                horizontalAlignment: Qt.AlignHCenter
                text: qsTr("Актуальные данные температуры, \nскорости ветра и влажности воздуха")
            }

            Text {
                id: dateText
                anchors.horizontalCenter: parent.horizontalCenter
                text: Qt.formatDateTime(_viewModel.currentDateTime, "dddd dd MMMM hh:mm")
                font.italic: true
            }

            Text {
                id: temperatureText
                anchors.horizontalCenter: parent.horizontalCenter
                text: _viewModel.temp + " " + _viewModel.tempUnits
                font.italic: true
            }

            Text {
                id: windspeedText
                anchors.horizontalCenter: parent.horizontalCenter
                text: _viewModel.windSpeed + " " + _viewModel.windSpeedUnits
                font.italic: true
            }

            Text {
                id: humidityText
                anchors.horizontalCenter: parent.horizontalCenter
                text: _viewModel.humidity + " " + _viewModel.windSpeedUnits
                font.italic: true
            }
        }
    }
}
