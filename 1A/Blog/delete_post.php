<?php
require "header.php";
require "config.php";

if (!isset($_SESSION['user_id'])) {
    header('Location: login.php');
    exit();
}

if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    $post_id = $_POST['post_id'];
    $user_id = $_SESSION['user_id'];

    try {
        $sql = "SELECT * FROM posts WHERE id = :post_id AND user_id = :user_id";
        $stmt = $conn->prepare($sql);
        $stmt->bindParam(':post_id', $post_id, PDO::PARAM_INT);
        $stmt->bindParam(':user_id', $user_id, PDO::PARAM_INT);
        $stmt->execute();

        if ($stmt->rowCount() > 0) {
            $conn->beginTransaction();

            $sql = "DELETE FROM comments WHERE post_id = :post_id";
            $stmt = $conn->prepare($sql);
            $stmt->bindParam(':post_id', $post_id, PDO::PARAM_INT);
            $stmt->execute();

            $sql = "DELETE FROM votes WHERE post_id = :post_id";
            $stmt = $conn->prepare($sql);
            $stmt->bindParam(':post_id', $post_id, PDO::PARAM_INT);
            $stmt->execute();

            $sql = "DELETE FROM posts WHERE id = :post_id";
            $stmt = $conn->prepare($sql);
            $stmt->bindParam(':post_id', $post_id, PDO::PARAM_INT);
            
            if ($stmt->execute()) {
                $conn->commit();
                header('Location: index.php');
                exit();
            } else {
                $conn->rollBack();
                echo "Erreur : " . $stmt->errorInfo()[2];
            }
        } else {
            echo "Vous n'avez pas la permission de supprimer ce post.";
        }
    } catch (PDOException $e) {
        echo "Erreur : " . $e->getMessage();
        if ($conn->inTransaction()) {
            $conn->rollBack();
        }
    }

    $conn = null;
}
?>
