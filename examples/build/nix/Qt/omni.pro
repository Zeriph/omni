#-------------------------------------------------
#
# Project created by QtCreator 2013-11-03T11:03:08
#
#-------------------------------------------------

# Omni doesn't need any Qt links, core and gui are the default so remove them
QT       -= core gui

TARGET = omni
TEMPLATE = lib
CONFIG += staticlib

# defines the name of this .pro
DEFINES += OMNI_LIBRARY

# define the Omni framework source directory for Windows and *nix
# change to what you wish
win32:OMNI_SRC_DIR = C:/source/omni
unix:OMNI_SRC_DIR = /source/omni

INCLUDEPATH += $$OMNI_SRC_DIR

SOURCES += \
<zeriph_inline_source>/    $$OMNI_SRC_DIR/{0.nm_path} \</zeriph_inline_source>

HEADERS += \
<zeriph_inline_header>/    $$OMNI_SRC_DIR/{0.nm_path} \</zeriph_inline_header>
