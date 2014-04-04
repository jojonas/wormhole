TARGET = Wormhole
CONFIG += debug
QT += core gui widgets network

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

FORMS +=	wormhole.ui \
			droppanel.ui \
			connectioninputdialog.ui 

DESTDIR +=	../bin
UI_DIR +=	./tmp/ui
RCC_DIR +=	./tmp/rcc
MOC_DIR +=	./tmp/moc

INCLUDEPATH += ./tmp/ui ./tmp/rcc ./tmp/moc \
			. \
			./protobuf/include

DEPENDPATH += .

LIBS +=		-L"./protobuf/lib" \
			-llibprotobuf

OBJECTS_DIR += ./tmp/obj


win32:debug {
	CONFIG += console
}
