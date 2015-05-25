cd `dirname $0`/../../..
cp src/ghost/qmldir qml/GtGhost/qmldir
qmlplugindump GtGhost 1.0 qml >> qml/GtGhost/plugins.qmltypes
