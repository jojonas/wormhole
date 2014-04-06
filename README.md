Wormhole
========

Motivation
----------
Since the beginning of the networking age, file transfer between computers has always been a problem that users had to face in every day situations. First solutions, like `sendfile` or `ftp`, have long been outdate but not replaced. Instead, the trend has moved on to two separate directions: file sharing (Dropbox, Windows/Samba shares, Torrents) or messaging services that support sending of files (Email, Skype, facebook). In all of this, the simple problem of "just transfering files" has not been addressed.

This project aims to provide an easy-to-use solution for file sending in local networks. 


Setup
-----
Since the project is currently in development, there are no pre-built binaries for it yet. Thus, one has to check out and compile the source oneself.

### Prerequisites
* [Qt 4.8 or higher](http://qt-project.org/downloads)
* [Google Protocol buffers](https://code.google.com/p/protobuf/downloads/list)

On Windows, install the protocol buffers into the `protobuf` subdirectory, such that `protobuf/include` contains the header files, `protobuf/lib` contains the lib library binaries and the protocol buffer compiler exists at `protobuf/protoc.exe`.

On Linux, the protocol buffers can be installed by the package manager, e.g. `sudo apt-get install libprotobuf-dev` on Ubuntu (tested on Ubuntu 12.04 LTS)

For Qt, installers are available for all platforms that automatically configure the environment.

### Building
There is aQMake project file `wormhole.pro` inside the source folder `src`. To generate a Visual Studio project on Windows, run `qmake -tp vc`. On Linux, the command `qmake` generates a Makefile, such that the project can be build running `make`.

Usage
-----
One aim of this project is to make usage as easy as possible. Drag and drop plays an important role, one can drop files onto the main panel to send them to connected peers. To connect to a peer, right-click into the main window, choose "Connect..." and enter an IP and port to connect to.



