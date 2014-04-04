# General Setup
TARGET = Wormhole
CONFIG += debug
QT += core gui widgets network

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
			file.pb.cc \ # I shouldn't have to do this....
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
			file.pb.h \ # I shouldn't have to do this.... (2)
			nethandler.h \
			peer.h \
			qtprotobuf.h \
			wormhole.h \
			wormholeservice.h 

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
INCLUDEPATH += . $$UI_DIR $$RCC_DIR $$MOC_DIR \
			./protobuf/include

DEPENDPATH += .
LIBS +=		-L"./protobuf/lib" \
			-llibprotobuf


