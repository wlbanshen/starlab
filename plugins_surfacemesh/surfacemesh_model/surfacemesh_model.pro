CONFIG += starlab
STARLAB_TEMPLATE = dynamic
STARLAB_DEPENDS = common

# Dependencies
QT += xml opengl

DEFINES += DYNAMIC_SURFACEMESH

OTHER_FILES = *.prf

# THIS IS FOR OUR MODEL WRAPPER
HEADERS += SurfaceMeshModel.h \
    dynamic_surfacemesh_global.h \
    SurfaceMeshRenderer.h \
    SurfaceMeshTypes.h \
    SurfaceMeshHelper.h \
    interfaces/SurfaceMeshModelPlugins.h \
    helpers/ColorMap.h \
    helpers/CurvatureEstimationHelper.h \
    helpers/LaplacianHelper.h \
    helpers/MatlabSurfaceMeshHelper.h \
    helpers/SurfaceMeshQForEachHelpers.h \
    helpers/ColorizeHelper.h \
    helpers/DoUndoHelper.h \
    helpers/LocalAnalysisHelper.h \
    helpers/StatisticsHelper.h
 
SOURCES += SurfaceMeshModel.cpp \
    SurfaceMeshRenderer.cpp

# SPECIALIZED TOOLBAR ICONS
RESOURCES = images.qrc

# THESE ARE THE ONES OF THE REAL LIBRARY
HEADERS += geometry/Vector.h
HEADERS += geometry/Quadric.h
HEADERS += surface_mesh/properties.h
HEADERS += surface_mesh/Surface_mesh.h
HEADERS += surface_mesh/IO.h
HEADERS += surface_mesh/gl_wrappers.h

SOURCES += surface_mesh/IO.cpp
SOURCES += surface_mesh/IO_stl.cpp
SOURCES += surface_mesh/IO_obj.cpp
SOURCES += surface_mesh/IO_off.cpp
SOURCES += surface_mesh/Surface_mesh.cpp



