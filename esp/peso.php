<?php
// Lê o conteúdo do arquivo peso.json
$valor_peso = file_get_contents("peso.json");

// Imprime na tela o valor lido
echo "O valor atual em peso.json é: " . $valor_peso;
?>

