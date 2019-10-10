<?php
    header('Content-Type: image/svg+xml');
    if(!empty($_GET['date']) && (!empty($_GET['start']) || strcmp($_GET['start'], "0") == 0) && !empty($_GET['end'])) {
        $command = escapeshellcmd($_GET['date']." ".$_GET['start']." ".$_GET['end']);
        exec("python3 /media/sf_bot/main/powerwall/plot.py $command 2> /dev/null", $output, $status);
        echo implode("\n", $output);
    } else {
        readfile('/media/sf_data/powerwall/power.svg');
    }
?>
