
    var wrapper = ["(function (module, require){ \
                'use strict'; \
                var exports = module.exports = {}; \
                ", " \
                if (typeof(module.exports) === 'undefined') { \
                    module.exports = {}; \
                } \
                if (module.exports !== exports) { \
                    for (var attrname in exports) { module.exports[attrname] = exports[attrname]; } \
                } \
                return module; \
            });"];

    Object.defineProperty(global, "moduleHotReload", {
        value: function () {
            for (var fileID in cache) {
                var current = _fileModified(fileID);
                _log(current);
                if (current > cache[fileID].lastLoaded) {
                    var fileContents = _loadFile(fileID);

                    var results;

                    try { // Attempt to parse as JSON
                        results = JSON.parse(fileContents);

                        cache[fileID].exports = results;
                        cache[fileID].Type = "JSON";
                        cache[fileID].lastLoaded = Date.now();

                    } catch (e) { // otherwise, attempt to compile it as JS
                        results = _compileModule(fileID, wrapper[0] + fileContents + wrapper[1]);

                        if (typeof (results) !== 'undefined') {

                            if (typeof (cache[fileID].unload) === "function") {
                                cache[fileID].unload.call(global);
                            }

                            cache[fileID] = results.call(global, {}, global.require); // return module object;

                            if (typeof (cache[fileID]) !== 'undefined') {
                                cache[fileID].Type = 'Code';
                                cache[fileID].lastLoaded = Date.now();
                            }
                        }
                    }
                }
            }
        },
        writable: false
    });

    _v8 = undefined;
    _binding = undefined;

    Object.defineProperty(global, "require", {
        value: (function () {

            return function (fileID) {

                var fileContents = "";

                if (typeof cache[fileID] !== 'undefined') {
                    if (typeof (cache[fileID].exports) !== 'undefined') {
                        return cache[fileID].exports;
                    }

                    return;
                }

                fileContents = _loadFile(fileID);

                var results;

                try { // Attempt to parse as JSON
                    results = JSON.parse(fileContents);

                    cache[fileID].exports = results;
                    cache[fileID].Type = "JSON";
                    cache[fileID].lastLoaded = Date.now();

                    return cache[fileID].exports;
                } catch (e) { // otherwise, attempt to compile it as JS
                    results = _compileModule(fileID, wrapper[0] + fileContents + wrapper[1]);
                    if (typeof (results) !== 'undefined') {

                        cache[fileID] = results.call(global, {}, global.require); // return module object;

                        cache[fileID].Type = 'Code';
                        cache[fileID].lastLoaded = Date.now();

                        return cache[fileID].exports;
                    }
                }
            };
        })(),
        writable: false
    });
});
