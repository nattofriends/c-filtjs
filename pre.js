var Module = {
    // jQuery will most definitely finish loading before we do.
    'preRun': function() {
        window['emscriptenLoaded'] = true;
        $(window).trigger('c++filtjsLoading');
    }
};
