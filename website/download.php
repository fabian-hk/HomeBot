<?php
   header('Content-Type: application/CSV');
   header("Content-Disposition: attachment; filename=".$_GET["file"]);

   readfile('/home/pi/bot/data/powerwall/'.$_GET["file"]);
?>
