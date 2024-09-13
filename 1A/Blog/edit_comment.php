<?php
require "config.php";

if ($_SERVER["REQUEST_METHOD"] === "POST" && isset($_POST['comment_id'], $_POST['updated_comment'], $_POST['post_id'])) {
    $commentId = $_POST['comment_id'];
    $updatedComment = $_POST['updated_comment'];
    $postId = $_POST['post_id'];

    // Assurez-vous de valider et d'échapper vos entrées pour éviter les injections SQL
    $updatedComment = htmlspecialchars($updatedComment);

    $sql = "UPDATE comments SET comment = :updated_comment WHERE id = :comment_id";
    $stmt = $conn->prepare($sql);
    $stmt->bindParam(':updated_comment', $updatedComment, PDO::PARAM_STR);
    $stmt->bindParam(':comment_id', $commentId, PDO::PARAM_INT);

    if ($stmt->execute()) {
        // Réussite : retournez une réponse 200 OK
        http_response_code(200);
        echo "Commentaire modifié avec succès.";
        exit();
    } else {
        // Erreur de requête : retournez une erreur 500 Internal Server Error
        http_response_code(500);
        echo "Erreur lors de la modification du commentaire.";
        exit();
    }
} else {
    // Requête invalide : retournez une erreur 400 Bad Request
    http_response_code(400);
    echo "Requête invalide.";
    exit();
}
?>
