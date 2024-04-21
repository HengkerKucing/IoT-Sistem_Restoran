<?php
    $servername = "localhost";
    $username = "root";
    $password = "";
    $dbname = "binary_data";
    $conn = mysqli_connect($servername, $username, $password, $dbname);
    if (!$conn) {
        die("Koneksi gagal: " . mysqli_connect_error());
    }
    $sql = "SELECT * FROM binary_values order by id";
    $result = mysqli_query($conn, $sql);
    if (mysqli_num_rows($result) > 0) {
        while($row = mysqli_fetch_assoc($result)) {
            echo $row["binary_value"].",";
        }
    } else {
        echo "0 results";
    }
    mysqli_close($conn);
?>
 