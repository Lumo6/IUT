<?php 
  session_start();
?>
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Blog</title>

    <h1>Bienvenue sur le Blog</h1>
    <?php if (isset($_SESSION['user_id'])): ?>
      <a href="create_post.php" class="create-post-button">Créer un nouveau post</a>
            <form action="logout.php" method="POST" style="display: inline;">
                <button type="submit">Déconnexion</button>
            </form>
            <div class="header-space"></div>
    <?php else: ?>
      <div class="header-buttons">
        <a href="login.php">Connexion</a>
        <a href="register.php">Inscription</a>
      </div>
    <?php endif; ?>