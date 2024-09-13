<?php
require_once("connexion_base.php");
session_start();

if (isset($_SESSION['username'])) {
    header("Location: doc.php");
    exit();
}

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $username = $_POST['username'];
    $password = $_POST['password'];
    $remember_me = isset($_POST['remember_me']) ? true : false;

    $stmt = $bdd->prepare("SELECT * FROM clients WHERE username = ?");
    $stmt->execute([$username]);
    $user = $stmt->fetch(PDO::FETCH_ASSOC);

    if ($user && password_verify($password, $user['password'])) {
        $_SESSION['username'] = $user['username'];
        $_SESSION['email'] = $user['email'];

        $code_session = bin2hex(random_bytes(32));
        
        $stmt = $bdd->prepare("UPDATE clients SET code_session = ? WHERE username = ?");
        $stmt->execute([$code_session, $username]);

        if ($remember_me) {
            setcookie('code_session', $code_session, time() + (30 * 24 * 3600), '/');
        }

        header("Location: doc.php");
        exit();
    } else {
        echo "Nom d'utilisateur ou mot de passe incorrect.";
    }
}
?>

<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Connexion</title>
</head>
<body>
    <h1>Connexion</h1>
    <form action="" method="post">
        <label for="username">Nom d'utilisateur:</label>
        <input type="text" id="username" name="username" required><br>

        <label for="password">Mot de passe:</label>
        <input type="password" id="password" name="password" required><br>

        <input type="checkbox" id="remember_me" name="remember_me">
        <label for="remember_me">Se souvenir de moi</label><br>

        <button type="submit">Se connecter</button>
    </form>
</body>
</html>