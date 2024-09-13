<?php
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    if (isset($_POST['clients']) && !empty($_POST['clients'])) {
        $bdd = new PDO('mysql:host=localhost;dbname=r2_06','root','');
        $bdd->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

        $clients_ids = implode(",", $_POST['clients']);
        $stmt = $bdd->prepare("DELETE FROM clients WHERE id_client IN (".str_repeat("?,", count($_POST['clients']) - 1)."?)");
        $stmt->execute($_POST['clients']);

        header("Location: confirmation_suppression.php");
        exit();
    } else {
        echo "Aucun client n'a été sélectionné.";
    }
} else {
    echo "La méthode de requête n'est pas prise en charge.";
}
?>