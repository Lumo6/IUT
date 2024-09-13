<?php require "header.php"; ?>
<?php require "config.php"; ?>
<?php

if (!isset($_SESSION['user_id'])) {
    header('Location: login.php');
    exit();
}

if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    $post_id = $_POST['post_id'];
    $user_id = $_SESSION['user_id'];

    try {
        $sql = "SELECT COUNT(*) FROM votes WHERE user_id = :user_id AND post_id = :post_id";
        $stmt = $conn->prepare($sql);
        $stmt->bindParam(':user_id', $user_id, PDO::PARAM_INT);
        $stmt->bindParam(':post_id', $post_id, PDO::PARAM_INT);
        $stmt->execute();
        $count = $stmt->fetchColumn();

        if ($count == 0) {
            $conn->beginTransaction();

            $sql = "UPDATE posts SET votes = votes + 1 WHERE id = :post_id";
            $stmt = $conn->prepare($sql);
            $stmt->bindParam(':post_id', $post_id, PDO::PARAM_INT);

            if ($stmt->execute()) {
                $sql = "INSERT INTO votes (user_id, post_id) VALUES (:user_id, :post_id)";
                $stmt = $conn->prepare($sql);
                $stmt->bindParam(':user_id', $user_id, PDO::PARAM_INT);
                $stmt->bindParam(':post_id', $post_id, PDO::PARAM_INT);
                $stmt->execute();

                $conn->commit();
                header('Location: index.php');
                exit();
            } else {
                $conn->rollBack();
                echo "Erreur : " . $stmt->errorInfo()[2];
            }
        } else {
            header('Location: index.php');
            exit();
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
