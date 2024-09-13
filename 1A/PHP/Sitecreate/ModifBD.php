<?php
    if($_SERVER['REQUEST_METHOD'] === 'POST') {
        if(isset($_POST['id_client'], $_POST['nom'], $_POST['prenom'], $_POST['age'], $_POST['adresse'], $_POST['ville'], $_POST['email'])) {
            $id_client = $_POST['id_client'];
            $nom = $_POST['nom'];
            $prenom = $_POST['prenom'];
            $age = $_POST['age'];
            $adresse = $_POST['adresse'];
            $ville = $_POST['ville'];
            $email = $_POST['email'];

            $bdd = new PDO('mysql:host=localhost;dbname=r2_06','root','');
            $bdd->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

            $stmt = $bdd->prepare("UPDATE clients SET nom = ?, prenom = ?, age = ?, adresse = ?, ville = ?, mail = ? WHERE id_client = ?");
            $stmt->execute([$nom, $prenom, $age, $adresse, $ville, $email, $id_client]);
            
            header("Location: Accueil.html");
            exit();
        } else {
            echo "Tous les champs sont requis pour effectuer la modification.";
        }
    } else {
        echo "La méthode de requête n'est pas prise en charge.";
    }
?>