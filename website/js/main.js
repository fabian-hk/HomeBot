// code for the date picker
$(document).ready(function(){
    var date_input=$('input[name="date"]'); //our date input has the name "date"
    var container=$('.bootstrap-iso form').length>0 ? $('.bootstrap-iso form').parent() : "body";
    var options={
    format: 'yyyy_mm_dd',
    container: container,
    todayHighlight: true,
    autoclose: true,
    };
    date_input.datepicker(options);
})

// disable loading animation when the image is loaded
$('#graphs').one("load", function() {
    $('.loader').css('display', 'none');
});