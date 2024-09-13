<?php
session_start();
if (!isset($_SESSION['username'])) {
    if (isset($_COOKIE['code_session'])) {
        $code_session = $_COOKIE['code_session'];
        $stmt = $bdd->prepare("SELECT * FROM clients WHERE code_session = ?");
        $stmt->execute([$code_session]);
        $user = $stmt->fetch(PDO::FETCH_ASSOC);
        if ($user) {
            $_SESSION['username'] = $user['username'];
            $_SESSION['email'] = $user['email'];
        } else {
            setcookie('code_session', '', time() - 3600, '/',null,false,true);
        }
    } else {
        header("Location: Connexion.php");
        exit();
    }
}
?>

<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Informations du compte</title>
</head>
<body>
    <h1>Informations du compte</h1>
    <p>Pseudonyme : <?php echo $_SESSION['username']; ?></p>
    <p>Adresse email : <?php echo $_SESSION['email']; ?></p>

    <form action="deconnexion.php" method="post">
        <button type="submit">Se déconnecter</button>
    </form>
</body>
</html>