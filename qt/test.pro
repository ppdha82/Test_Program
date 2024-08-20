
INCLUDERPATH = $$PWD $$files("./include/*.h", true)

HEADERS = $$INCLUDERPATH

SOURCES = test.cpp $$files("./src/*.cpp", true)

DEFINES += "__DEBUG_ON__"

FORMS    += mainwindow.ui