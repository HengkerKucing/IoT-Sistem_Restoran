<!DOCTYPE html>
<html>
<head>
    <title>Tabel Meja Restoran</title>
</head>
<body>

<?php
    $host = 'localhost';
    $username = 'root';
    $password = '';
    $database = 'binary_data';

    $koneksi = mysqli_connect($host, $username, $password, $database);

    if (mysqli_connect_errno()) {
        die("Koneksi database gagal: " . mysqli_connect_error());
    }

    $query = "SELECT id, binary_value FROM binary_values";
    $result = mysqli_query($koneksi, $query);

    if (mysqli_num_rows($result) > 0) {
        while ($row = mysqli_fetch_assoc($result)) {
            $id = $row['id'];
            $binary_value = $row['binary_value'];

            echo "Meja Ke-$id: " . ($binary_value ? '1' : '0') . "<br>";
            if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST["toggle$id"])) {
                $new_value = !$binary_value;

                $update_query = "UPDATE binary_values SET binary_value = '$new_value' WHERE id = $id";
                mysqli_query($koneksi, $update_query);

                header("Location: index.php");
                exit;
            }

            echo "<form method='post'>";
            echo "<input type='submit' name='toggle$id' value='Pesanan-$id'>";
            echo "</form>";
        }
    } else {
        echo "Tidak ada data ditemukan dalam database.";
    }
?>

</body>
</html>
