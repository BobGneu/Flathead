Basic Installation & Configuration
==================================

1. Clone the project into your Plugins directory. 

  1. Download ThirdParty.zip and unzip it into the Plugins directory. 
  
2. Add this Flathead to the PrivateDependencyModuleNames list.

    ```csharp
    PrivateDependencyModuleNames.Add("Flathead");
	```
	
3. Overwrite the base module, hooking into the StartupModule method.

	```cpp
	class FMyJSSampleModule : public FDefaultGameModuleImpl
	{
		virtual void StartupModule() OVERRIDE;
	};
	
	void FMyJSSampleModule::StartupModule()
	{
		if (IFlathead::IsAvailable())
		{
			IFlathead::Get().LoadGameScript("GameInit.js");
		}
	}
	```

4. Add your script file to the /Scripts directory of your project.

	```javascript
	game.log("Game Initialization");
	
	Object.addEventListener("game.tick", function (ev) {
		game.log("tick.", ev.deltaTime);
	});
	```
	
5. Expose your types to JS

	```cpp
	void AFH_FlyingPawn::Expose()
	{
		if (!IFlathead::IsAvailable())
			return;
	
		IFlathead &ref = IFlathead::Get();
		HandleScope handle_scope(ref.GetIsolate());
	
		Local<Context> context = ref.GetGlobalContext();
		Context::Scope ContextScope(context);
	
		Local<Object> Bob = ref.Expose(this, TEXT("Bob"));
	
		Bob->Set(String::NewFromUtf8(ref.GetIsolate(), "value", String::kInternalizedString), Number::New(ref.GetIsolate(), 42));
	
		Local<String> key = String::NewFromUtf8(ref.GetIsolate(), "test", String::kInternalizedString);
	
		ref.LoadGameScript("BobTest.js");
	 }
	```

6. Enjoy!

Please consult the Wiki for further documentation. 
If you run into any issues, please file a ticket in the GH Tracker. 

Sample Projects & Code
===============
* Flying Game: https://github.com/BobGneu/UE4FlyingGame

Known Issues
============
Exposing Functions is currently not working, but may be addressed with updating to a later build of V8. You can contribute to the discussion on this topic here: https://groups.google.com/forum/#!topic/v8-users/cYkuljdJEJ8

Contact 
=======

If you have any Questions, Comments, Bug reports or feature requests for this plugin, or you wish to contact me you can and should email me - bob@gneu.org

Alternatively, you can join me in #gneu on irc.freenode.net or irc.gamesurge.net
