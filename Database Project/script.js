$(document).ready(function(){
    $("#logbut").click(function(){
        $(".login").show();
        $(".register").hide();
    });

    $("#regbut").click(function(){
        $(".login").hide();
        $(".register").show();
    });

}); 

