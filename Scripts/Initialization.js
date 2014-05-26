/// https://developer.mozilla.org/en-US/docs/Web/API/CustomEvent

require("Assertion");
require("Eventing");

game.log("Inititializing Flathead.");

Object.addEventListener("initialized", function (details) {
	game.log("Inititialized.", v8.version, v8.bindingVersion);
});
var event = new CustomEvent("initialized");

Object.dispatchEvent(event);

require("MathTests");