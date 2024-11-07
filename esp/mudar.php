<?php
    function trocar_peso($NOVO_PESO,$peso_antigo,$mysqli){
        $sql_troca = "UPDATE usuarios SET nome = 'João' WHERE id = 1";
    if ($mysqli->query($sql_troca) === TRUE) {
        echo "Registro atualizado com sucesso!";
    } else {
        echo "Erro ao atualizar registro: " . $mysqli->error;
    }
    }
   