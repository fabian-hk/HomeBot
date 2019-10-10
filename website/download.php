<?php
    if(strcmp($_GET["file"], "0") == 0) {
        header('Content-Type: application/CSV');
        header("Content-Disposition: attachment; filename=current_values.csv");
        readfile('/media/sf_data/powerwall/current_values.csv');
    } elseif(strcmp($_GET["file"], "1") == 0) {
        header('Content-Type: application/CSV');
        header("Content-Disposition: attachment; filename=month_values.csv");
        readfile('/media/sf_data/powerwall/month_values.csv');
    } else {
        echo "Error 404";
    }
?>
