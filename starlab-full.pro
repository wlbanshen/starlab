system(qmake -set QMAKEFEATURES $$PWD/starlab-core) #QT BUG

TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS += starlab-core

SUBDIRS += plugins-surfacemesh
#SUBDIRS += plugins-curveskel
