<?php 
require "config.php"; 
require "header.php";

if (!isset($_SESSION['user_id'])) {
    header('Location: login.php');
    exit();
}

if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    $comment = $_POST['comment'];
    $post_id = $_POST['post_id'];
    $user_id = $_SESSION['user_id'];

    $sql = "INSERT INTO comments (post_id, user_id, comment) VALUES (?, ?, ?)";
    $stmt = $conn->prepare($sql);

    $stmt->bindParam(1, $post_id, PDO::PARAM_INT);
    $stmt->bindParam(2, $user_id, PDO::PARAM_INT);
    $stmt->bindParam(3, $comment, PDO::PARAM_STR);

    if ($stmt->execute()) {
        header('Location: view_post.php?id=' . $post_id);
        exit();
    } else {
        $errorInfo = $stmt->errorInfo();
        echo "Erreur : " . $errorInfo[2];
    }
    
    $conn = null;
}
?>
