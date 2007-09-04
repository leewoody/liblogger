liblogger : A logging framework for C / C++
---------------------------------------------------------
Copyright : Vineeth Neelakant - nvineeth _A_T_ gmail _D_O_T_ com 
License : GNU LGPL
Website : http://liblogger.sourceforge.net
---------------------------------------------------------

BUILDING - UNIX
----------------
liblogger uses scons (http://scons.org) build system.
You may need to install scons from the above system.
The sources are available under the folder src.
To build run "scons" from the folder src/build.
To see various build options, run the command "scons -h" under folder src/build.
ex : To build in release mode with O3 optimization, use "scons RELEASE=1"
ex : To cross compile for arm, use "scons CROSS_COMPILE=arm-linux- "

BUILDING - WINDOWS
----------------
For windows, the Visual Studio solution is provided under build folder.

DOCUMENTATION
----------------
Documentation is provided at the website : http://liblogger.sourceforge.net,
alternatively you can build the documentation  if you have doxygen installed.
Under the folder docs/ run command "doxygen" and the html docs are generated in ./docs/docs/html

DOUBTS / BUGS / SUGGESTIONS
----------------------------
If you have any doubts, 
* you can ask them at the discussion forum: http://sourceforge.net/forum/forum.php?forum_id=721800
* or at the users mailing list : http://sourceforge.net/mail/?group_id=202343

Pls file the bug reports here: http://sourceforge.net/tracker/?group_id=202343&atid=981202

Pls file the feature requests here: http://sourceforge.net/tracker/?group_id=202343&atid=981205

You can also mail the developer(s) at nvineeth _A_T_ gmail _D_O_T_ com

-------------
Thanks for your interest in liblogger, hope it will be helpful...
