# extra steps to be taken after compiling the library to produce a standalone application

once you successfully compile the app in OSX you will only be able to use the application on that same machine, or in one where a QtSDK of the same version was installed at the same path.

Indeed, if you inspect the runtime dependencies of the binary with **otool**, note the _/Users/ata2/Developer/QtSDK/Desktop/Qt/4.8.1/gcc/lib/_ below:

```
ata2 @ pluto ~/Desktop: otool -L Starlab.app/Contents/MacOS/starlab 
Starlab.app/Contents/MacOS/starlab:
	@executable_path/../lib/libcommon.1.dylib (compatibility version 1.0.0, current version 1.0.0)
	@executable_path/../lib/libparameters.1.dylib (compatibility version 1.0.0, current version 1.0.0)
	/Users/ata2/Developer/QtSDK/Desktop/Qt/4.8.1/gcc/lib/QtOpenGL.framework/Versions/4/QtOpenGL (compatibility version 4.8.0, current version 4.8.1)
	/Users/ata2/Developer/QtSDK/Desktop/Qt/4.8.1/gcc/lib/QtGui.framework/Versions/4/QtGui (compatibility version 4.8.0, current version 4.8.1)
	/Users/ata2/Developer/QtSDK/Desktop/Qt/4.8.1/gcc/lib/QtCore.framework/Versions/4/QtCore (compatibility version 4.8.0, current version 4.8.1)
	/System/Library/Frameworks/OpenGL.framework/Versions/A/OpenGL (compatibility version 1.0.0, current version 1.0.0)
	/System/Library/Frameworks/AGL.framework/Versions/A/AGL (compatibility version 1.0.0, current version 1.0.0)
	/usr/lib/libstdc++.6.dylib (compatibility version 7.0.0, current version 56.0.0)
	/usr/lib/libgcc_s.1.dylib (compatibility version 1.0.0, current version 1669.0.0)
	/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 169.3.0)
```

This can be solved by using the macdeployqt which can be found (for my QtSDK) at:
**/Users/ata2/Developer/QtSDK/Desktop/Qt/4.8.1/gcc/bin/macdeployqt**

By running it against the app bundle:

```
ata2 @ pluto ~/Desktop: macdeployqt Starlab.app
```

We can see we have removed the dependencies from a local version of the Qt libraries:

```
ata2 @ pluto ~/Desktop: otool -L Starlab.app/Contents/MacOS/starlab 
Starlab.app/Contents/MacOS/starlab:
	@executable_path/../lib/libcommon.1.dylib (compatibility version 1.0.0, current version 1.0.0)
	@executable_path/../lib/libparameters.1.dylib (compatibility version 1.0.0, current version 1.0.0)
	@executable_path/../Frameworks/QtOpenGL.framework/Versions/4/QtOpenGL (compatibility version 4.8.0, current version 4.8.1)
	@executable_path/../Frameworks/QtGui.framework/Versions/4/QtGui (compatibility version 4.8.0, current version 4.8.1)
	@executable_path/../Frameworks/QtCore.framework/Versions/4/QtCore (compatibility version 4.8.0, current version 4.8.1)
	/System/Library/Frameworks/OpenGL.framework/Versions/A/OpenGL (compatibility version 1.0.0, current version 1.0.0)
	/System/Library/Frameworks/AGL.framework/Versions/A/AGL (compatibility version 1.0.0, current version 1.0.0)
	/usr/lib/libstdc++.6.dylib (compatibility version 7.0.0, current version 56.0.0)
	/usr/lib/libgcc_s.1.dylib (compatibility version 1.0.0, current version 1669.0.0)
	/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 169.3.0)
```



# More information #
http://qt-project.org/doc/qt-4.8/deployment-mac.html