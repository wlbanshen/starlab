CONFIG += starlab
STARLAB_TEMPLATE += plugin
STARLAB_DEPENDS += ../surfacemesh
STARLAB_EXTERNAL += cholmod eigen

HEADERS += geodistance.h
SOURCES += geodistance.cpp

HEADERS += GeoHeatHelper.h
HEADERS += GeoDrawObjects.h
