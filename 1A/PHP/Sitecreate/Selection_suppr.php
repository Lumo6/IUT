<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Supprimer des clients</title>
</head>
<body>
    <h1>Supprimer des clients</h1>
    <form action="Suppr.php" method="post">
        <?php
            $bdd = new PDO('mysql:host=localhost;dbname=r2_06','root','');
            $bdd->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

            $stmt = $bdd->query("SELECT id_client, nom, prenom FROM clients");
            
            while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
                echo "<input type='checkbox' name='clients[]' value='{$row['id_client']}'>{$row['nom']} {$row['prenom']}<br>";
            }
        ?>
        <button type="submit">Supprimer</button>
    </form>
</body>
</html>
