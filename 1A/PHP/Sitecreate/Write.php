<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <link rel="stylesheet" href="Write.css">
</head>
<body>

<?php
    session_start(); 
    
    try {
        $bdd = new PDO('mysql:host=localhost;dbname=r2_06','root','');
        $bdd->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
    }
    catch (PDOException $e) {
        exit("Echec de la connection." . $e->getMessage());
    }

    if ($_SERVER['REQUEST_METHOD'] === 'POST' && isset($_POST['Bouton'])) {
        $nom = $_POST['nom'];
        $prenom = $_POST['prenom'];
        $age = $_POST['Age'];
        $adresse = $_POST['Adresse'];
        $ville = $_POST['Ville'];
        $mail = $_POST['E-mail'];
    
        if($nom && $prenom && $age && $adresse && $ville && $mail) {
            $stmt = $bdd->prepare("INSERT INTO clients(nom, prenom, age, adresse, ville, mail) VALUES (?, ?, ?, ?, ?, ?)");
            $stmt->bindParam(1, $nom, PDO::PARAM_STR);
            $stmt->bindParam(2, $prenom, PDO::PARAM_STR);
            $stmt->bindParam(3, $age, PDO::PARAM_INT);
            $stmt->bindParam(4, $adresse, PDO::PARAM_STR);
            $stmt->bindParam(5, $ville, PDO::PARAM_STR);
            $stmt->bindParam(6, $mail, PDO::PARAM_STR);
    
            $stmt->execute();

            $last_id = $bdd->lastInsertId();

            $_SESSION['last_insert_id'] = $last_id;
    
            header("Location: {$_SERVER['PHP_SELF']}");
            exit();
        }
        else {
            echo "Il manque des paramètres !";
        }
    }

    if(isset($_SESSION['last_insert_id'])) {
        echo "ID de la dernière insertion : " . $_SESSION['last_insert_id'];
        unset($_SESSION['last_insert_id']);
    }
?>
    <div id="form">
        <H1>Vos coordonnées</H1>
        <form action="Write.php" method="post">
            <div>
                <label for="Nom">Nom&nbsp;:</label>
                <input type="text" id="Nom" name="nom" />
            </div>
            <div>
                <label for="prenom">Prénom&nbsp;:</label>
                <input type="text" id="Prenom" name="prenom" />
            </div>
            <div>
                <label for="Age">Age&nbsp;:</label>
                <input type="text" id="Age" name="Age" />
            </div>
            <div>
                <label for="Adresse">Adresse&nbsp;:</label>
                <input type="text" id="Adresse" name="Adresse" />
            </div>
            <div>
                <label for="ville">Ville&nbsp;:</label>
                <input type="text" id="Ville" name="Ville"></textarea>
            </div>
            <div>
                <label for="E-mail">E-mail&nbsp;:</label>
                <input type="email" id="E-mail" name="E-mail" />
            </div>
            
            <div class="button">
                <input type="submit" name="Bouton"/>
            </div>
        </form>
    </div>
</body>

</html>


