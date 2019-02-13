# Minimal Drag'n'Drop application for Windows

This repository contains a minimal application sample showcasing how to do basic dragging-and-dropping of files from the Windows Explorer to an application window.

At launch, it shows both a blank application window and a console window. When you drag and drop files from the Windows explorer to the application window, the absolute paths are printed in the console window.

## How to Build
Using the Visual Studio compiler: Simply call the provided build_win32.bat file, after having set vcvarsall.bat in your environment.
This build method has been tested with Visual Studio 2015, under Windows 10.

You should be able to use any other compiler, provided you can link the relevant Windows SDK.

## Why does this even exist?
When I tried to integrate dragging and dropping in a bigger project, I had trouble finding the relevant documentation on the msdn website; and when I finally found a link to a code sample, the link was broken. So I did this little sample application so that future people who have basic drag'n'drop need for their application don't struggle as much.

In the end, all this sample does is summarized on this page, under "Extracting the File Names from the Data Object":
https://docs.microsoft.com/en-us/windows/desktop/shell/datascenarios

## License
Public domain and, in countries where Public Domain is not applicable, this license: you are granted a perpetual, irrevocable license to copy, modify, publish, and distribute this file as you see fit.

## More about the author
https://lhuillia.iiens.net/en

https://twitter.com/Guntha_en
