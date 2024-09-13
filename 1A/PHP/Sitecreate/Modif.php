

<?php
    if(isset($_GET['id_client'])) {
        $id_client = $_GET['id_client'];

        $bdd = new PDO('mysql:host=localhost;dbname=r2_06','root','');
        $bdd->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

        $stmt = $bdd->prepare("SELECT * FROM clients WHERE id_client = ?");
        $stmt->execute([$id_client]);
        $client = $stmt->fetch(PDO::FETCH_ASSOC);

        if($client) {
            ?>
            <!DOCTYPE html>
            <html>
            <head>
                <meta charset="UTF-8">
                <link rel="stylesheet" href="Modif.css">
                <title>Modifier les informations du client</title>
            </head>
            <body>
                <h1>Modifier les informations du client</h1>
                <form action="ModifBD.php" method="post">
                    <input type="hidden" name="id_client" value="<?php echo $client['id_client']; ?>">
                    <label for="nom">Nom :</label>
                    <input type="text" id="nom" name="nom" value="<?php echo $client['nom']; ?>"><br>
                    <label for="prenom">Prénom :</label>
                    <input type="text" id="prenom" name="prenom" value="<?php echo $client['prenom']; ?>"><br>
                    <label for="age">Âge :</label>
                    <input type="text" id="age" name="age" value="<?php echo $client['age']; ?>"><br>
                    <label for="adresse">Adresse :</label>
                    <input type="text" id="adresse" name="adresse" value="<?php echo $client['adresse']; ?>"><br>
                    <label for="ville">Ville :</label>
                    <input type="text" id="ville" name="ville" value="<?php echo $client['ville']; ?>"><br>
                    <label for="email">E-mail :</label>
                    <input type="email" id="email" name="email" value="<?php echo $client['mail']; ?>"><br>
                    <button type="submit">Enregistrer les modifications</button>
                </form>
            </body>
            </html>
            <?php
        } else {
            echo "Client non trouvé.";
        }
    } else {
        echo "ID client non spécifié.";
    }
?>