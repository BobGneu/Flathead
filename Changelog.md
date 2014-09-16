Unreleased
==========

  * Updated to V8 3.29.58 (Candidate)

1.0.0 - 05/26/2014
===============================

  * Exposing of variables as properties and using accessors is now working
  * Most of the UE4 float/double math library is exposed.
  * Started exposing UObject basics.

RC1 - 03/29/2014
================

  * Repurposed as Plugin. It is now fully self contained.
  * Executing Raw JS code from any point after the module StartModule method is functional. The plugin loads before game modules do.
  * addEventListener, CustomEvent dispatchEvent are now defined.
  * Load method added to API.
  * V8 is linked into UE4 via a module
  * Added a game object, which has a function for each level of UE4 logging as well as a property for the version of the game, defined in a constant.
  * Added a v8 object, providing a property to query the version of the binding, incremented as the API evolves, and a property to query the version of v8 included in the binding.
  * Loading of scripts based in the modules Source/JS directory from the console as well as from module loading.
  * String Conversion between V8 and UE4.
  * Exposing static methods in the form of an object
