game.log("Eventing!");

if (typeof Object.addEventListener !== 'function') {
	Object.prototype.addEventListener = function (name, fn) {
		// If this object has yet to have any events attached, create a new object. 
		if (!this.events)
			this.events = {};

		// If this event listing has not yet been notified of this event, create a new array. 
		this.events[name] = this.events[name] || [];

		// add this callback to the list 
		this.events[name].push(fn);
	};
}

if (typeof Object.dispatchEvent !== 'function') {
	Object.prototype.dispatchEvent = function (ev) {
		// if there are no events, we don't care
		if (!this.events)
			return;

		// if this event has no listeners registered, we don't care either. 
		if (!this.events[ev.Name])
			return;

		// add this callback to the list 
		this.events[ev.Name].forEach(function (element) {
			element(ev.detail);
		});
	};
}

var CustomEvent = function (name, params) {
	params = params || {
		bubbles: false,
		cancelable: false,
		detail: undefined
	};

	this.Name = name;
	this.bubbles = params.bubbles || false;
	this.detail = params.detail || {};
	this.cancelable = params.cancelable || false;
};