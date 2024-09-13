<?php require "header.php"; ?>
<?php require "config.php"; ?>

<?php
if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    $username = $_POST['username'];
    $password = password_hash($_POST['password'], PASSWORD_BCRYPT);

    try {
        $sql = "INSERT INTO users (username, password) VALUES (:username, :password)";
        $stmt = $conn->prepare($sql);
        $stmt->bindParam(':username', $username);
        $stmt->bindParam(':password', $password);

        if ($stmt->execute()) {
            header('Location: login.php');
            exit();
        } else {
            echo "Erreur : " . implode(", ", $stmt->errorInfo());
        }
    } catch (PDOException $e) {
        echo "Erreur : " . $e->getMessage();
    }

    $conn = null;
}
?>

<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <title>Inscription</title>
    <link rel="stylesheet" href="style/login.css">
</head>
<body>
    <h1>Inscription</h1>
    <form action="register.php" method="POST">
        <label for="username">Nom d'utilisateur</label>
        <input type="text" name="username" required>
        <label for="password">Mot de passe</label>
        <input type="password" name="password" required>
        <button type="submit">S'inscrire</button>
    </form>
    <a href="login.php">Déjà inscrit ? Connectez-vous ici</a>
</body>
</html>
