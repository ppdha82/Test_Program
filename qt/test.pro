
QT += core gui widgets xml xmlpatterns svg

INCLUDERPATH = $$PWD $$files("./include/*.h", true)

HEADERS = $$INCLUDERPATH

SOURCES = test.cpp $$files("./src/*.cpp", true)

!isEmpty(VER_STR){
    VER_STR = ver\\:1.1.2\\($${VER_STR}\\)
}

DEFINES += VER=\\\"$${VER_STR}\\\"
DEFINES += "__DEBUG_ON__"

FORMS    += mainwindow.ui

CONFIG -= ENABLE_QT4

ENABLE_QT4 {
    DEFINES += __ENABLE_QT4__
}
else {
}

RESOURCES += XSD.qrc