# General Setup
TARGET = Wormhole
CONFIG += debug

QT += core gui network
greaterThan(QT_MAJOR_VERSION, 4) {
	QT += widgets
} 

# Platform specific debug code
win32:debug:CONFIG += console

# Google Protocol Buffers
PROTOS +=	file.proto
include(protobuf.pri)

# Files
SOURCES +=	checksum.cpp \
			connectionhandler.cpp \
			connectioninputdialog.cpp \
			debug.cpp \
			droppanel.cpp \
			main.cpp \
			nethandler.cpp \
			peer.cpp \
			qtprotobuf.cpp \
			wormhole.cpp \
			wormholeservice.cpp

HEADERS +=	checksum.h \
			connectionhandler.h \
			connectioninputdialog.h \
			debug.h \
			droppanel.h \
			nethandler.h \
			peer.h \
			qtprotobuf.h \
			wormhole.h \
			wormholeservice.h 

# this is a bug workaround for Visual Studio
win32 {
	SOURCES += file.pb.cc
	HEADERS += file.pb.h
}


FORMS +=	wormhole.ui \
			droppanel.ui \
			connectioninputdialog.ui 

			
# Directories
DESTDIR +=	../bin
UI_DIR +=	./tmp/ui
RCC_DIR +=	./tmp/rcc
MOC_DIR +=	./tmp/moc
OBJECTS_DIR += ./tmp/obj

# Paths
INCLUDEPATH += . $$UI_DIR $$RCC_DIR $$MOC_DIR 

DEPENDPATH += .
LIBS +=		-lprotobuf


