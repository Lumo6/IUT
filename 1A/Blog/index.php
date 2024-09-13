<?php 
require "header.php"; 
require "config.php"; 
?>

<?php
$query = isset($_GET['query']) ? $_GET['query'] : '';
$theme_id = isset($_GET['theme_id']) ? $_GET['theme_id'] : '';
$sort = isset($_GET['sort']) ? $_GET['sort'] : '';

$filter_sql = $theme_id ? "AND posts.theme_id = :theme_id" : '';
$order_by = $sort === 'best' ? 'posts.votes DESC' : 'posts.time DESC';

$sql = "SELECT posts.id, posts.title, posts.content, posts.votes, themes.name AS theme, users.username, posts.time 
        FROM posts 
        JOIN users ON posts.user_id = users.id 
        LEFT JOIN themes ON posts.theme_id = themes.id 
        WHERE (posts.title LIKE :query OR posts.content LIKE :query) $filter_sql 
        ORDER BY $order_by";

$stmt = $conn->prepare($sql);
$search_query = '%' . $query . '%';
$stmt->bindParam(':query', $search_query, PDO::PARAM_STR);

if ($theme_id) {
    $stmt->bindParam(':theme_id', $theme_id, PDO::PARAM_INT);
}

$stmt->execute();
$result = $stmt->fetchAll(PDO::FETCH_ASSOC);

$themes = $conn->query("SELECT * FROM themes");
?>


<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <title>Blog</title>
    <link rel="stylesheet" href="style/index.css">
</head>
<body>
    <form action="index.php" method="GET" style="display: flex; justify-content: center;">
        <input type="text" name="query" placeholder="Rechercher des publications..." value="<?php echo htmlspecialchars($query); ?>">
        <select name="theme_id" id="theme_id" style="margin-right: 10px;">
            <option value="">Toutes les thématiques</option>
            <?php while ($row = $themes->fetch(PDO::FETCH_ASSOC)): ?>
                <option value="<?php echo $row['id']; ?>" <?php if ($row['id'] == $theme_id) echo 'selected'; ?>>
                    <?php echo $row['name']; ?>
                </option>
            <?php endwhile; ?>
        </select>
        <button type="submit">Filtrer</button>
    </form>
    <form action="index.php" method="GET" style="margin-top: 20px;">
        <button type="submit" name="sort" value="best">Meilleures publications</button>
    </form>
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
            if (count($result) > 0) {
                foreach($result as $row) {
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
                echo "<tr><td colspan='6'>Aucune publication trouvée.</td></tr>";
            }
            ?>
        </tbody>
    </table>
</body>
</html>

<?php
$conn = null;
?>
