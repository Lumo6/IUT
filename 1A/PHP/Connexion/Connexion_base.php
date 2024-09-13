<?php
// Connexion à la base de données
$bdd = new PDO('mysql:host=localhost;dbname=Infos_connexion','root','');
$bdd->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
?>