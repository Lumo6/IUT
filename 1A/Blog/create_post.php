<?php 
  session_start();
?>

<?php 
require "config.php"; 

if (!isset($_SESSION['user_id'])) {
    header('Location: login.php');
    exit();
}

$themesStmt = $conn->query("SELECT * FROM themes");
$themes = $themesStmt->fetchAll(PDO::FETCH_ASSOC);

if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    $title = $_POST['title'];
    $content = $_POST['content'];
    $theme_id = $_POST['theme_id'];
    $user_id = $_SESSION['user_id'];
    $images = null;

    if ($_SERVER['REQUEST_METHOD'] == 'POST') {
        $title = $_POST['title'];
        $content = $_POST['content'];
        $theme_id = $_POST['theme_id'];
        $user_id = $_SESSION['user_id'];
        $images = null;
    
        if (!empty($_FILES['image']['name'])) {
            $target_dir = "images/";
            $target_file = $target_dir . basename($_FILES['image']['name']);
            $imageFileType = strtolower(pathinfo($target_file, PATHINFO_EXTENSION));
            
            $check = getimagesize($_FILES['image']['tmp_name']);
            if ($check !== false) {
                if (move_uploaded_file($_FILES['image']['tmp_name'], $target_file)) {
                    $images = $target_file;
                } else {
                    echo "Erreur lors de l'upload de l'image.";
                }
            } else {
                echo "Le fichier n'est pas une image.";
            }
        }
    
        $userCheckSql = "SELECT id FROM users WHERE id = :user_id";
        $userCheckStmt = $conn->prepare($userCheckSql);
        $userCheckStmt->bindParam(':user_id', $user_id);
        $userCheckStmt->execute();
    
        if ($userCheckStmt->rowCount() > 0) {
            $sql = "INSERT INTO posts (user_id, title, content, theme_id, images) VALUES (:user_id, :title, :content, :theme_id, :images)";
            $stmt = $conn->prepare($sql);
            $stmt->bindParam(':user_id', $user_id);
            $stmt->bindParam(':title', $title);
            $stmt->bindParam(':content', $content);
            $stmt->bindParam(':theme_id', $theme_id);
            $stmt->bindParam(':images', $images);
    
            if ($stmt->execute()) {
                header('Location: index.php');
                exit();
            } else {
                echo "Erreur : " . $stmt->errorInfo()[2];
            }
        } else {
            echo "Utilisateur non trouvé.";
        }
    
        $conn = null;
    }
}
?>

<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <title>Créer un nouveau post</title>
    <link rel="stylesheet" href="style/create_post.css">
</head>
<body>
    <h1>Créer un nouveau post</h1>
    <form action="create_post.php" method="POST" enctype="multipart/form-data">
        <label for="title">Titre</label>
        <input type="text" name="title" required>
        <label for="content">Contenu</label>
        <textarea name="content" required></textarea>
        <label for="theme_id">Thématique</label>
        <select name="theme_id" id="theme_id" required>
            <option value="" disabled selected>Sélectionnez une thématique</option>
            <?php foreach ($themes as $theme): ?>
                <option value="<?php echo htmlspecialchars($theme['id']); ?>"><?php echo htmlspecialchars($theme['name']); ?></option>
            <?php endforeach; ?>
        </select>
        <label for="image">Image</label>
        <input type="file" name="image" accept="image/*">
        <button type="submit">Publier</button>
    </form>
    <a href="index.php">Retour à l'accueil</a>
</body>
</html>
