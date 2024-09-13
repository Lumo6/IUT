<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Inscription</title>
</head>
<body>
    <h1>Inscription</h1>
    <form action="register.php" method="post">
        <label for="username">Pseudonyme:</label>
        <input type="text" id="username" name="username" required><br>

        <label for="email">Adresse email:</label>
        <input type="email" id="email" name="email" required><br>

        <label for="password">Mot de passe:</label>
        <input type="password" id="password" name="password" required><br>

        <label for="confirm_password">Confirmation du mot de passe:</label>
        <input type="password" id="confirm_password" name="confirm_password" required><br>

        <button type="submit">S'inscrire</button>
    </form>


</body>
</html>