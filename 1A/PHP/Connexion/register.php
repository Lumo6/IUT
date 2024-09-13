<?php

require_once("connexion_base.php");

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $username = $_POST['username'];
    $email = $_POST['email'];
    $password = $_POST['password'];
    $confirm_password = $_POST['confirm_password'];

    if ($password !== $confirm_password) {
        echo "Les mots de passe ne correspondent pas.";
        exit();
    }

    $hashed_password = password_hash($password, PASSWORD_DEFAULT);


    $stmt = $bdd->prepare("SELECT * FROM clients WHERE username = ?");
    $stmt->execute([$username]);
    if ($stmt->rowCount() > 0) {
        echo "Ce pseudonyme est déjà utilisé.";
        exit();
    }

    $stmt = $bdd->prepare("INSERT INTO clients (username, email, password) VALUES (?, ?, ?)");
    $stmt->execute([$username, $email, $hashed_password]);

    header("Location: Connexion.php?registered=true");
    exit();
} else {
    echo "La méthode de requête n'est pas prise en charge.";
}
?>