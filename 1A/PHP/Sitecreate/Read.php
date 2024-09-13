<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <link rel="stylesheet" href="Read.css">
</head>
<body>

<?php
    $servername = 'localhost';
    $username = 'root';
    $password = '';
    $db = "r2_06";

    $conn = new mysqli($servername, $username, $password, $db);
    
    if ($conn->connect_error) {
        die("Connexion échouée: " . $conn->connect_error);
    }
    
    $sql = "SELECT * FROM clients";
    $result = $conn->query($sql);
    
    if ($result === false) {
        echo "Erreur lors de l'exécution de la requête : " . $conn->error;
    } elseif ($result->num_rows > 0) {
        echo "<h1>Tous les clients</h1>";
        echo "<h2>Il y a " . $result->num_rows . " contacts</h2>";
        echo "<table>";
        echo "<tr id=\"ligne1\"><th>Numéro</th><th>Nom</th><th>Prénom</th><th>Age</th><th>Adresse</th><th>Ville</th><th>mail</th></tr>";
        while($row = $result->fetch_assoc()) {
            echo "<tr><td>" . $row["id_client"]. "</td><td>" . $row["nom"]. "</td><td>" . $row["prenom"]. "</td><td>" . $row["age"]. "</td><td>" . $row["adresse"]. "</td><td>" . $row["ville"]. "</td><td>" . $row["mail"]. "</td></tr>";
        }
        echo "</table>";
    } else {
        echo "0 résultats";
    }
    
    // Fermer la connexion
    $conn->close();
    
?>

</body>
</html>