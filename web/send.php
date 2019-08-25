<?php

$name_forma = $_POST['name_forma'];
$email = $_POST['email'];
$telephon = $_POST['telephon'];
$message = $_POST['message'];

$name_forma = htmlspecialchars($name_forma);
$email = htmlspecialchars($email);
$telephon = htmlspecialchars($telephon);
$message = htmlspecialchars($message);

$name_forma = urldecode($name_forma);
$email = urldecode($email);
$telephon = urldecode($telephon);
$message = urldecode($message);

$name_forma = trim($name_forma);
$email = trim($email);
$telephon = trim($telephon);
$message = trim($message);

mail("anna.drozzzdova@gmail.com", "Заявка с сайта", "Имя:".$name_forma.". E-mail: ".$email.". Tелефон:".$telephon.". Сообщение: ".$message ,"From: ann.red.fox75@gmail.com \r\n");
?>