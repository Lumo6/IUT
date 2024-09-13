<?php
session_start();
require "config.php"; 

if (!isset($_SESSION['user_id'])) {
    header('Location: login.php');
    exit();
}

$post_id = $_GET['id'];

$sql = "SELECT posts.id, posts.title, posts.content, users.username, posts.user_id, posts.time, posts.images FROM posts JOIN users ON posts.user_id = users.id WHERE posts.id = :post_id";
$stmt = $conn->prepare($sql);
$stmt->bindParam(':post_id', $post_id, PDO::PARAM_INT);
$stmt->execute();

if ($stmt->rowCount() > 0) {
    $post = $stmt->fetch(PDO::FETCH_ASSOC);
} else {
    echo "Publication non trouvée.";
    exit();
}

$comment_sql = "SELECT comments.id, comments.comment, comments.user_id, users.username, comments.time FROM comments JOIN users ON comments.user_id = users.id WHERE comments.post_id = :post_id ORDER BY comments.time DESC";
$stmt = $conn->prepare($comment_sql);
$stmt->bindParam(':post_id', $post_id, PDO::PARAM_INT);
$stmt->execute();
$comments = $stmt->fetchAll(PDO::FETCH_ASSOC);
?>

<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <title><?php echo htmlspecialchars($post['title']); ?></title>
    <link rel="stylesheet" href="style/view_post.css">
    <style>
        .edit-comment-button,
        .delete-comment-button,
        .save-comment-button {
            padding: 8px 16px;
            border: none;
            border-radius: 5px;
            background-color: #ff9800;
            color: #1a1a1a;
            cursor: pointer;
            font-weight: bold;
            margin-right: 10px;
        }

        .edit-comment-button:hover,
        .delete-comment-button:hover,
        .save-comment-button:hover {
            background-color: #e68900;
        }

        .comment .delete-comment-button {
            margin-left: auto; /* Pour aligner à droite */
        }
    </style>
</head>
<body>
    <div class="container">
        <div class="post-title-container">
            <h1><?php echo htmlspecialchars($post['title']); ?></h1>
            <p>par <?php echo htmlspecialchars($post['username']); ?> le <?php echo htmlspecialchars($post['time']); ?></p>
        </div>
        <h2>Contenu</h2>
        <div class="post-content">
            <?php if (!empty($post['images'])): ?>
                <img src="<?php echo htmlspecialchars($post['images']); ?>" alt="Image du post" style="max-width: 100%; height: auto; margin-bottom: 20px;">
            <?php endif; ?>
            <p><?php echo nl2br(htmlspecialchars($post['content'])); ?></p>
        </div>
        
        <div class="comments-section">
            <h2>Commentaires</h2>
            <div class="comments">
                <?php
                if (count($comments) > 0) {
                    foreach ($comments as $comment) {
                        echo "<div class='comment' id='comment-" . $comment['id'] . "'>";
                        echo "<p><strong>" . htmlspecialchars($comment['username']) . "</strong> le " . htmlspecialchars($comment['time']) . "</p>";
                        echo "<p>" . htmlspecialchars($comment['comment']) . "</p>";

                        if (isset($_SESSION['user_id']) && $_SESSION['user_id'] == $comment['user_id']) {
                            echo "<div class='comment-buttons'>";
                            
                            // Bouton "Modifier" pour afficher le formulaire de modification
                            echo "<button class='edit-comment-button' data-comment-id='" . $comment['id'] . "'>Modifier</button>";
                            
                            // Formulaire de modification du commentaire (initialisé à caché)
                            echo "<form id='edit-form-" . $comment['id'] . "' action='edit_comment.php' method='POST' style='display: none;'>";
                            echo "<input type='hidden' name='comment_id' value='" . $comment['id'] . "'>";
                            echo "<input type='hidden' name='post_id' value='" . $post_id . "'>";
                            echo "<textarea name='updated_comment' required>" . htmlspecialchars($comment['comment']) . "</textarea>";
                            echo "<div class='form-buttons'>"; // Wrapper pour les boutons
                            echo "<button type='submit' class='save-comment-button' data-comment-id='" . $comment['id'] . "'>Enregistrer</button>";
                            echo "</div>"; // Fermeture du wrapper
                            echo "</form>";
                            
                            echo "<button class='delete-comment-button' data-comment-id='" . $comment['id'] . "' data-post-id='" . $post_id . "'>Supprimer</button>";
                            echo "</div>"; // Fermeture de .comment-buttons
                        }
                    }
                }
                else {
                    echo "<p>Aucun commentaire pour cette publication.</p>";
                }
                ?>
            </div>
        </div>
        
        <div class="add-comment">
            <h3>Ajouter un commentaire</h3>
            <form id="comment-form" action="add_comment.php" method="POST">
                <input type="hidden" name="post_id" value="<?php echo $post_id; ?>">
                <label for="comment">Commentaire</label>
                <textarea id="comment" name="comment" required></textarea>
                <button id="submit-comment" type="submit">Commenter</button>
            </form>
        </div>

        <?php if (isset($_SESSION['user_id']) && $_SESSION['user_id'] == $post['user_id']): ?>
            <form action="delete_post.php" method="POST">
                <input type="hidden" name="post_id" value="<?php echo $post_id; ?>">
                <button class="delete-post" type="submit" onclick="return confirm('Êtes-vous sûr de vouloir supprimer ce post ?');">Supprimer le post</button>
            </form>
        <?php endif; ?>
    </div>

    <div class="footer">
        <a href="index.php">Retour à l'accueil</a>
    </div>

    <script>
    document.addEventListener('DOMContentLoaded', function() {
        // Gestion de l'affichage/masquage du champ de modification
        var editButtons = document.querySelectorAll('.edit-comment-button');
        editButtons.forEach(function(button) {
            button.addEventListener('click', function(event) {
                event.preventDefault();
                var commentId = this.dataset.commentId;
                var editForm = document.getElementById('edit-form-' + commentId);
                if (editForm) {
                    editForm.style.display = 'block'; // Afficher le formulaire de modification
                }
                // Masquer le bouton "Modifier" après avoir affiché le formulaire
                this.style.display = 'none';
            });
        });

        // Gestion de l'enregistrement du commentaire modifié
        var saveButtons = document.querySelectorAll('.save-comment-button');
        saveButtons.forEach(function(button) {
            button.addEventListener('click', function(event) {
                event.preventDefault();
                var commentId = this.dataset.commentId;
                var editForm = document.getElementById('edit-form-' + commentId);
                var updatedComment = editForm.querySelector('textarea').value.trim();
                if (updatedComment === '') {
                    alert('Veuillez saisir un commentaire.');
                    return;
                }
                var formData = new FormData(editForm);
                var xhr = new XMLHttpRequest();
                xhr.open('POST', 'edit_comment.php', true);
                xhr.onreadystatechange = function() {
                    if (xhr.readyState === 4) {
                        if (xhr.status === 200) {
                            // Succès : affichez la réponse ou effectuez toute autre action nécessaire
                            console.log(xhr.responseText);
                            
                            // Mettre à jour le commentaire sur l'interface utilisateur
                            var commentElement = document.getElementById('comment-' + commentId);
                            if (commentElement) {
                                var commentText = commentElement.querySelector('p:last-of-type');
                                if (commentText) {
                                    commentText.textContent = updatedComment;
                                }
                            }
                            // Cacher le formulaire de modification
                            editForm.style.display = 'none';
                            // Réafficher le bouton "Modifier"
                            var editButton = document.querySelector('.edit-comment-button[data-comment-id="' + commentId + '"]');
                            if (editButton) {
                                editButton.style.display = 'inline-block';
                            }
                        } else {
                            // Erreur : affichez un message d'erreur ou effectuez une action en cas d'échec
                            console.error('Erreur lors de la modification du commentaire.');
                        }
                    }
                };
                xhr.send(formData);
            });
        });

        // Fonction pour supprimer un commentaire
        function deleteComment(commentId, postId) {
            if (confirm('Êtes-vous sûr de vouloir supprimer ce commentaire ?')) {
                var xhr = new XMLHttpRequest();
                xhr.open('POST', 'delete_comment.php', true);
                xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
                xhr.onreadystatechange = function() {
                    if (xhr.readyState === 4 && xhr.status === 200) {
                        // Supprimer le commentaire de l'interface utilisateur
                        var commentElement = document.getElementById('comment-' + commentId);
                        if (commentElement) {
                            commentElement.remove();
                        }
                    }
                };
                xhr.send('comment_id=' + encodeURIComponent(commentId) + '&post_id=' + encodeURIComponent(postId));
            }
        }

        // Attacher les gestionnaires d'événements pour les boutons de suppression
        var deleteButtons = document.querySelectorAll('.delete-comment-button');
        deleteButtons.forEach(function(button) {
            button.addEventListener('click', function(event) {
                event.preventDefault();
                var commentId = this.dataset.commentId;
                var postId = this.dataset.postId;
                deleteComment(commentId, postId);
            });
        });
    });
    </script>
</body>
</html>

<?php
$conn = null;
?>
