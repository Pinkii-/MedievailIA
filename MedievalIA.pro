  CONFIG -= qt
  LIBS += -lsfml-graphics -lsfml-window -lsfml-system
  QMAKE_CXXFLAGS += -std=c++11 -fpermissive

SOURCES += \
    main.cpp \
    board.cpp \
    map.cpp \
    player.cpp \
    tile.cpp \
    terrain.cpp \
    npc.cpp \
    display.cpp \
    util.cpp \
    prop.cpp \
    control.cpp \
    Textures.cpp \
    Interface.cpp

OTHER_FILES += \
    Resources/mapa.txt \
    Resources/mapa2.txt \
    Resources/pruebaTile2.png \
    Resources/pruebaTile.png \
    Resources/npc.png

HEADERS += \
    board.h \
    map.h \
    player.h \
    tile.h \
    terrain.h \
    npc.h \
    display.h \
    util.h \
    prop.h \
    control.h \
    Textures.hpp \
    Interface.hpp
