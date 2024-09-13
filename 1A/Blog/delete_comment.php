<?php
require "config.php"; // Assurez-vous que ce fichier inclut la connexion à la base de données

if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    $comment_id = $_POST['comment_id'];

    try {
        $sql = "DELETE FROM comments WHERE id = :comment_id";
        $stmt = $conn->prepare($sql);
        $stmt->bindParam(':comment_id', $comment_id, PDO::PARAM_INT);

        if ($stmt->execute()) {
            // Redirection vers la page de visualisation du post après la suppression
            //header('Location: view_post.php?id=' . $_POST['post_id']);
            exit();
        } else {
            echo "Erreur lors de la suppression du commentaire.";
        }
    } catch (PDOException $e) {
        echo "Erreur : " . $e->getMessage();
    }
}

// Fermez la connexion à la base de données si nécessaire
$conn = null;
?>
