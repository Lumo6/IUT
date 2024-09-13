<?php require "header.php"; ?>
<?php require "config.php"; ?>

<?php
session_start();

if ($conn->connect_error) {
    die('Erreur de connexion : ' . $conn->connect_error);
}

$query = isset($_GET['query']) ? $conn->real_escape_string($_GET['query']) : '';
$theme_id = isset($_GET['theme_id']) ? $conn->real_escape_string($_GET['theme_id']) : '';
$filter_sql = $theme_id ? "AND posts.theme_id = '$theme_id'" : '';

if ($query) {
    $sql = "SELECT posts.id, posts.title, posts.content, posts.votes, themes.name AS theme, users.username, posts.time 
            FROM posts 
            JOIN users ON posts.user_id = users.id 
            LEFT JOIN themes ON posts.theme_id = themes.id 
            WHERE (posts.title LIKE '%$query%' OR posts.content LIKE '%$query%') $filter_sql 
            ORDER BY posts.time DESC";
    $result = $conn->query($sql);
} else {
    $result = null;
}

$themes = $conn->query("SELECT * FROM themes");
?>

<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <title>Résultats de recherche</title>
    <link rel="stylesheet" href="">
</head>
<body>
    <h1>Résultats de recherche</h1>
    <a href="index.php">Retour à l'accueil</a>
    <form action="search.php" method="GET">
        <input type="text" name="query" placeholder="Rechercher des publications..." value="<?php echo htmlspecialchars($query); ?>">
        <label for="theme_id">Filtrer par thématique:</label>
        <select name="theme_id" id="theme_id">
            <option value="">Toutes les thématiques</option>
            <?php while ($row = $themes->fetch_assoc()): ?>
                <option value="<?php echo $row['id']; ?>" <?php if ($row['id'] == $theme_id) echo 'selected'; ?>>
                    <?php echo $row['name']; ?>
                </option>
            <?php endwhile; ?>
        </select>
        <button type="submit">Rechercher</button>
        <button type="button" onclick="window.location.href='search.php'">Effacer les résultats</button>
    </form>
    <?php if ($result): ?>
        <table>
            <thead>
                <tr>
                    <th>SUJET</th>
                    <th>AUTEUR</th>
                    <th>THEMATIQUE</th>
                    <th>VOTES</th>
                    <th>DERNIER MSG</th>
                    <th>VOTER</th>
                </tr>
            </thead>
            <tbody>
                <?php
                if ($result->num_rows > 0) {
                    while($row = $result->fetch_assoc()) {
                        echo "<tr>";
                        echo "<td><a href='view_post.php?id=" . $row['id'] . "'>" . $row['title'] . "</a></td>";
                        echo "<td>" . $row['username'] . "</td>";
                        echo "<td>" . $row['theme'] . "</td>";
                        echo "<td>" . $row['votes'] . "</td>";
                        echo "<td>" . $row['time'] . "</td>";
                        echo "<td><form action='vote_post.php' method='POST' style='display:inline;'>
                                <input type='hidden' name='post_id' value='" . $row['id'] . "'>
                                <button type='submit'>Vote</button>
                              </form></td>";
                        echo "</tr>";
                    }
                } else {
                    echo "<tr><td colspan='6'>Aucun résultat trouvé pour votre recherche.</td></tr>";
                }
            ?>
            </tbody>
        </table>
    <?php endif; ?>
</body>
</html>

<?php
$conn->close();
?>