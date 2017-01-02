# ofxOSSIA

## Introduction

This openFrameworks addon is a wrapper for the [OSSIA API](https://github.com/OSSIA/API) , 
allowing you to share parameters with i-score: the class `ossia::Parameter` 
inheriting the openFrameworks' class `ofParameter` can be controlled both via the UI and [i-score](http://www.i-score.org).

## Dependencies 

* Tested on Linux (Debian/stretch, Antergos), macOS, Windows

* The OSSIA API require some boost libs not available in OpenFrameworks. To handle this :
    * Download http://sourceforge.net/projects/boost/files/boost/1.58.0/boost_1_58_0.zip
    * Extract the content of the `boost/` folder, in `of_v0.9.8_release/libs/boost/include/boost/`.
    * If done correctly you should have file replacement warnings for various `.hpp` files. Replace them all.
    
## Installation (OS X, Linux) 

* Compile the OSSIA library: go to the folder `libs/` and run the script `build.sh`
* **Copy the dynamic library** (libossia) created in `libs/ossia/libs/(OS_name)` to your app's `bin/` folder
* Include the header file `ofxOssia.hpp` to use the addon

* compilation of the project under OSX has to be made with the project makefile and not xcode.
* For OSX : after compiling, do the following.
```
    cp bin/libossia.dylib bin/myApp.app/Contents/MacOS
    
    install_name_tool -change "libossia.dylib" "@executable_path/libossia.dylib" bin/myApp.app/Contents/MacOS/myApp
```

## Installation (Windows)

* The simplest way is to use one of the releases.
* Once your application is built, do not forget to **copy the relevant DLL** from the libs/ossia/bin folder, to your executable folder.
* For compiling the OSSIA API by hand, refer to the [OSSIA API wiki](https://github.com/OSSIA/API/wiki).
## Troubleshooting

In case of the following error : `execvp: /bin/sh: Argument list too long`: check that you do not have a boost folder in your example folder.

## Main features

* Parameters of various types (int, float, bool, ofVec2f, ofVec3f, ofColor) can be shared with i-score
* Can be exposed in the openFrameworks GUI (modified via slider, button, etc.)
* Can be modified using i-score (automation ...)

## Usage

* Define an attribute of class `Network` in your app source header (e.g. `ofApp.h`)
* N.B. if the constructor for the attribute is not called explicitly, the attribute `Network` will be initialized with the default values (e.g. "newDevice", "i-score", "127.0.0.1", 13579, 9998)
* The `ossia::Parameter` is initialized using the method `setup` similar to `ofParameter::setup`. The only difference is the first value which is the base node obtained calling the method `getSceneNode()` on the `Network` instance
