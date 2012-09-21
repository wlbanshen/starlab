CONFIG += starlab 
STARLAB_TEMPLATE += plugin 
STARLAB_DEPENDS += ../surfacemesh
STARLAB_EXTERNAL += cholmod eigen

HEADERS += surfacemesh_mode_arapdeform.h arap_dialog.h ARAPDeformer.h ARAPDeformerHandle.h
SOURCES += surfacemesh_mode_arapdeform.cpp arap_dialog.cpp ARAPDeformer.cpp
RESOURCES += surfacemesh_mode_arapdeform.qrc

FORMS += arap_dialog.ui
