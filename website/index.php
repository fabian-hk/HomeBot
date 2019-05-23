<!DOCTYPE html>
<html>
   <head>
      <!-- Latest compiled and minified CSS -->
      <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css">

      <!-- jQuery library -->
      <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>

      <!-- Latest compiled JavaScript -->
      <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js"></script>
      <style>
         .table-wrapper-scroll-y {
            display: block;
            max-height: 290px;
            overflow-y: auto;
            -ms-overflow-style: -ms-autohiding-scrollbar;
         }
      </style>
   </head>
   <body style="margin: 20px">
      <div>
         <div>
            <h1>Current values (in Wh):</h1>
            <div class="table-wrapper-scroll-y">
               <table class="table table-bordered table-striped">
                  <thead>
                     <tr>
                        <th>Day</th>
                        <th>Home</th>
                        <th>From Grid</th>
                        <th>To Grid</th>
                        <th>Solar</th>
                        <th>From Powerwall</th>
                        <th>To Powerwall</th>
                     </tr>
                  </thead>
                  <tbody>
                     <?php
                        $file = fopen("/home/pi/bot/data/powerwall/current_values.csv", "r");

                        // read first line with header data
                        fgets($file);

                        // function to print the csv file in reverse order
                        function display_file($file, $data) {
                           if (($d = fgetcsv($file, 1000, ";")) !== false) {
                              display_file($file, $d);
                           } 
                           echo "<tr><td>".$data[1]."</td>";
                           echo "<td>".round(str_replace(',', '.', $data[2]), 2)."</td>";
                           echo "<td>".round(str_replace(',', '.', $data[3]), 2)."</td>";
                           echo "<td>".round(str_replace(',', '.', $data[4]), 2)."</td>";
                           echo "<td>".round(str_replace(',', '.', $data[5]), 2)."</td>";
                           echo "<td>".round(str_replace(',', '.', $data[6]), 2)."</td>";
                           echo "<td>".round(str_replace(',', '.', $data[7]), 2)."</td>";
                           echo "</tr>";
                        }
                        if (($d = fgetcsv($file, 1000, ";")) !== false) {
                           display_file($file, $d);
                        }
                     ?>
                  </tbody>
               </table>
            </div>
	         <br/>
            <a href="download.php/?file=current_values.csv" class="btn btn-info" role="button">Download current values</a>
            <br/>
	         <br/>
            <h1>Month values (in kWh):</h1>
            <div class="table-wrapper-scroll-y">
               <table class="table table-bordered table-striped">
                  <thead>
                        <tr>
                           <th>Day</th>
                           <th>Home</th>
                           <th>From Grid</th>
                           <th>To Grid</th>
                           <th>Solar</th>
                           <th>From Powerwall</th>
                           <th>To Powerwall</th>
                        </tr>
                     </thead>
                     <tbody>
                     
                     <?php
                        $file2 = fopen("/home/pi/bot/data/powerwall/month_values.csv", "r");
                         // read first line with header data
                        fgets($file2);
                        
                        // function to print the csv file in reverse order
                        function display_file2($file2, $data) {
                           if (($d = fgetcsv($file2, 1000, ";")) !== false) {
                              display_file2($file2, $d);
                           }
                           echo "<tr><td>".$data[1]."</td>";
                           echo "<td>".round(str_replace(',', '.', $data[2])/1000, 2)."</td>";
                           echo "<td>".round(str_replace(',', '.', $data[3])/1000, 2)."</td>";
                           echo "<td>".round(str_replace(',', '.', $data[4])/1000, 2)."</td>";
                           echo "<td>".round(str_replace(',', '.', $data[5])/1000, 2)."</td>";
                           echo "<td>".round(str_replace(',', '.', $data[6])/1000, 2)."</td>";
                           echo "<td>".round(str_replace(',', '.', $data[7])/1000, 2)."</td>";
                           echo "</tr>";
                        }
                        if (($d = fgetcsv($file2, 1000, ";")) !== false) {
                           display_file2($file2, $d);
                        }
                     ?>
                  </tbody>
               </table>
            </div>
            <br/>
            <a href="download.php/?file=month_values.csv" class="btn btn-info" role="button">Download month values</a>
            <br/>
            <br/>
         </div>
         <div>
            <h1>Graphs from today:</h1>
            <img src="power.php" alt="Plot from power usage">
         </div>
      </div>
   </body>
</html>
