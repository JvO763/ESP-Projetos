<?php
// Lê o conteúdo do arquivo bool.json
$valor_bool = file_get_contents("bool.json");

// Imprime na tela o valor lido
echo "O valor atual em bool.json é: " . $valor_bool;
?>
