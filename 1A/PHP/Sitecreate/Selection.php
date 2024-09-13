<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Sélectionner un client à modifier</title>
</head>
<body>
    <h1>Sélectionner un client à modifier</h1>
    <form action="Modif.php" method="get">
        <label for="client">Choisir un client :</label>
        <select id="client" name="id_client">
            <?php
                $bdd = new PDO('mysql:host=localhost;dbname=r2_06','root','');
                $bdd->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

                $stmt = $bdd->query("SELECT id_client, nom, prenom FROM clients");
                
                while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
                    echo "<option value='{$row['id_client']}'>{$row['nom']} {$row['prenom']}</option>";
                }
            ?>
        </select>
        <button type="submit">Modifier</button>
    </form>
</body>
</html>