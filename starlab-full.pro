system(qmake -set BUILD_PATH $$OUT_PWD) #for Windows, any better way?

TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += starlab-core
SUBDIRS += plugins-surfacemesh
SUBDIRS += plugins-curveskel
