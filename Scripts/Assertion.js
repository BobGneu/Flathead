if (typeof assert !== 'function') {
	var assert = function (condition, message) {
		if (!condition) {
			throw message || "Assertion failed";
		}
	}
}