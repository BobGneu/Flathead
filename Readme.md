Installation
============

Unzip the package into the Plugins directory of your game. To add it as an engine plugin you will need to unzip the module into the plugin directory under where you installed UE4.

Loading JS
==========

The IV8Plugin class has two static methods, one to check and see if the plugin is present, the other to get an instance of it. Once you have the instance you can load a file, as follows:

    if (IV8Plugin::IsAvailable())
    {
	    IV8Plugin::Get().Load("myJavascriptFile.js");
    }

This can be called from any location in your module. I recommend loading a global initialization file from the module's StartModule method, and that you use this opportunity to hook into any number of events that would then be fired off by the C++ code. 

The Global Context
==================

There are two global objects to note. 

 * **game** takes the place of what you may have worked with on the web - console. All five levels of logging in UE4 are functions attached to this object: Log, Display, Warning, Error, Fatal. game also has a readonly version property, allowing you to query for the version of unreal engine. 

 * **v8** has two readonly properties: version to query for the current version of V8 bound to the plugin; and bindingVersion which is incrementing as the API for the plugin is iterated over. 

Contact 
=======

If you have any Questions, Comments, Bug reports or feature requests for this plugin, or you wish to contact me you can and should email me - bob@gneu.org

Alternatively, you can join me in #gneu on irc.freenode.net or irc.gamesurge.net