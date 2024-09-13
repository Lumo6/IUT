<?php
session_start();
// Destruction de toutes les données de session
session_unset();
// Destruction de la session
session_destroy();
// Redirection vers la page de connexion
if(isset($_COOKIE['code_session'])){
    unset($_COOKIE['code_session']);
    setcookie('code_session', '', time() - 3600, '/',null,false,true);
}


header("Location: index.php");
exit();
?>