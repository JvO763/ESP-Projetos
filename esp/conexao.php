<?php

$usuario="root";
$senha="";
$database="clients";
$host=`localhost`;

$mysqli = new mysqli($host,$usuario,$senha,$database);

if($mysqli->connect_error){
    die("falha ao conectar ao banco de dados: " .$mysqli->connect_error);
}