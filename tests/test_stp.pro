CONFIG += qt console
message($$PWD)
INCLUDEPATH += $$PWD/../include $$PWD/../extlibs/headers
SOURCES += $$PWD/../src/STP/Core/*.*
SOURCES += $$PWD/../extlibs/pugixml/*.*

SOURCES += main_stp.cpp

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror
LIBS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

LIBS += -lboost_unit_test_framework

# zlib
LIBS += -lz
