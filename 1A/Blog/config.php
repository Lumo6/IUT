<?php 
    //host
    $host = "localhost";
    //dbname
    $dbname = "blog";
    //user
    $user = "root";
    //pass
    $pass = "";

    $conn = new PDO("mysql:host=$host;dbname=$dbname;", $user, $pass);
?>