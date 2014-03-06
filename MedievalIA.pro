  CONFIG -= qt
  LIBS += -lsfml-graphics -lsfml-window -lsfml-system
  QMAKE_CXXFLAGS += -std=c++11 -fpermissive

SOURCES += \
    main.cpp \
    board.cpp \
    map.cpp \
    player.cpp \
    control.cpp \
    Tiles/tile.cpp \
    Tiles/terrain.cpp \
    Tiles/prop.cpp \
    Tiles/npc.cpp \
    Tiles/Building.cpp \
    Utils/util.cpp \
    Utils/Textures.cpp \
    Utils/0templateclass.cpp \
    UI/Interface.cpp \
    UI/display.cpp \
    UI/Npcdisplayer.cpp \
    Tiles/Buildings/Base.cpp

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
    Interface.hpp \
    Building.h \
    0templateclass.h \
    Tiles/tile.h \
    Tiles/terrain.h \
    Tiles/prop.h \
    Tiles/npc.h \
    Tiles/Building.h \
    Utils/util.h \
    Utils/Textures.hpp \
    Utils/0templateclass.h \
    UI/Interface.hpp \
    UI/display.h \
    UI/Npcdisplayer.hpp \
    Tiles/Buildings/Base.hpp
