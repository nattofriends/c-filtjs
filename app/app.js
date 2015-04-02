
$(function() {
    window['domLoaded'] = true;
    $(window).trigger('c++filtjsLoading');
});

$(window).on('c++filtjsLoading', function() {

    if (!(window['emscriptenLoaded'] && window['domLoaded'])) {
        return;
    }

    var undname = Module.cwrap('undname', 'string', ['string'])
    var demangle = Module.cwrap('demangle', 'string', ['string'])

    var inputField = $('#in');
    inputField.keyup(function(evt) {
        var input = $(this).val();
        var output = "Not a mangled C++ symbol";
          
        var undnameOutput = undname(input);
        var demangleOutput = demangle(input);

        if (undnameOutput !== '') {
            output = undnameOutput;
        } else if (demangleOutput !== '') {
            output = demangleOutput;
        }

        $("#out").text(output);
    }).keyup();
});
