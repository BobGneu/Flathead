/// https://developer.mozilla.org/en-US/docs/Web/API/CustomEvent

game.log("Inititializing Flathead.");

require("Assertion");
require("Eventing");

Object.addEventListener("initialized", function (details) {

    game.display("Engine: " + game.engine.version);
    game.display("V8: " + game.v8.version);
    game.display("binding: " + game.binding.version);

});

var event = new CustomEvent("initialized");

Object.dispatchEvent(event);

// require("MathTests");

true;