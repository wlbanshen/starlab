system(qmake -set QMAKEFEATURES $$PWD/starlab-core) #QT BUG

TEMPLATE = subdirs
CONFIG += ordered 

#--- CORE LIBRARIES 
SUBDIRS += starlab-core/libraries/parameters
SUBDIRS += starlab-core/libraries/common
SUBDIRS += starlab-core/maingui
SUBDIRS += starlab-core/plugins_core/drawarea_meshlab
SUBDIRS += starlab-core/plugins_core/drawarea_starlab
SUBDIRS += starlab-core/plugins_core/render_bbox
SUBDIRS += starlab-core/plugins_core/gui_filemenu
SUBDIRS += starlab-core/plugins_core/gui_filter
SUBDIRS += starlab-core/plugins_core/gui_mode
SUBDIRS += starlab-core/plugins_core/gui_selection
SUBDIRS += starlab-core/plugins_core/gui_windows
SUBDIRS += starlab-core/plugins_core/gui_view
SUBDIRS += starlab-core/plugins_example

#--- NEW LIBRARIES
SUBDIRS += plugins_curveskel
#SUBDIRS += plugins_surfacemesh
