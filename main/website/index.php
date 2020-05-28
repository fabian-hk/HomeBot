<!DOCTYPE html>
<html>
    <head>
        <!-- Latest compiled and minified CSS -->
        <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css">

        <!-- jQuery library -->
        <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>

        <!-- Latest compiled JavaScript -->
        <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js"></script>

        <!-- Bootstrap Date-Picker Plugin -->
        <script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/bootstrap-datepicker/1.4.1/js/bootstrap-datepicker.min.js"></script>
        <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/bootstrap-datepicker/1.4.1/css/bootstrap-datepicker3.css"/>

        <!-- Latest compiled and minified CSS -->
        <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap-select@1.13.9/dist/css/bootstrap-select.min.css">

        <!-- Latest compiled and minified JavaScript -->
        <script src="https://cdn.jsdelivr.net/npm/bootstrap-select@1.13.9/dist/js/bootstrap-select.min.js"></script>

        <link rel="stylesheet" href="css/main.css" />
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
                            $file = fopen("/mnt/data/powerwall/current_values.csv", "r");

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
        <a href="download.php/?file=0" class="btn btn-info" role="button">Download current values</a>
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
                $file2 = fopen("/mnt/data/powerwall/month_values.csv", "r");
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
        <a href="download.php/?file=1" class="btn btn-info" role="button">Download month values</a>
        <br/>
        <br/>
        </div>
        <h1>Graphs:</h1>
        <div class="row">
            <div class="col-md-6 col-12">
                <img src="power.php?date=<?php echo $_POST['date']; ?>&start=<?php echo $_POST['start']; ?>&end=<?php echo $_POST['end']; ?>" id="graphs" class="graphs" alt="Plot of power data">
                <div class="loader center" <?php
                    if(empty($_POST['date']) || (empty($_POST['start']) && strcmp($_POST['start'], "0") != 0) || empty($_POST['end'])) {
                        echo 'style="display: none;"';
                    }
                ?> ></div>
            </div>
            <div class="col-md-6 col-12">
                <h3>Pick date and time:</h3>
                <form method="post" action="index.php">
                    <div class="form-group"> <!-- Date input -->
                    <label class="control-label" for="date">Date</label>
                    <input class="form-control" id="date" name="date" placeholder="YYYY_MM_DD" type="text"/>
                    </div>

                    <select name="start" class="form-control mb-3">
                        <option value="-1">Start hour</option>
                        <?php for ($i = 0; $i <= 24; $i++) : ?>
                        <option value="<?php echo $i; ?>"><?php echo $i; ?></option>
                        <?php endfor; ?>
                    </select>

                    <select name="end" class="form-control mb-3">
                        <option value="24">End hour</option>
                        <?php for ($i = 1; $i <= 24; $i++) : ?>
                        <option value="<?php echo $i; ?>"><?php echo $i; ?></option>
                        <?php endfor; ?>
                    </select>
                    <div class="form-group"> <!-- Submit button -->
                        <button class="btn btn-primary " name="submit" type="submit">Plot</button>
                    </div>
                </form>
                </div>
            </div>
        </div>
    </body>
    <script src="js/main.js"></script>
</html>
