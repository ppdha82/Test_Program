
QT += core gui widgets

INCLUDERPATH = $$PWD $$files("./include/*.h", true)

HEADERS = $$INCLUDERPATH

SOURCES = test.cpp $$files("./src/*.cpp", true)

DEFINES += "__DEBUG_ON__"

FORMS    += mainwindow.ui

CONFIG -= ENABLE_QT4

ENABLE_QT4 {
    DEFINES += __ENABLE_QT4__
}
else {
}