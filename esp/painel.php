<?php
include("conexao.php");
include("protect.php");

$error_message = "";

// Verifica se o formulário foi enviado para atualizar o peso
if(isset($_POST["novopeso"])) {
    // Verifica se o campo do peso foi preenchido
    if(strlen($_POST["novopeso"]) == 0) {
        $error_message = "Por favor, informe o novo peso.";
    } else {       
        $nome = $mysqli->real_escape_string($_SESSION['id']);
        $peso = $mysqli->real_escape_string($_POST["novopeso"]);
        $sql_troca = "UPDATE tabelin SET peso = '$peso' WHERE id=$nome";
        $sql_query = $mysqli->query($sql_troca) or die("Falha na execução do código SQL:" . $mysqli->error);
        
        // Atualiza a variável de sessão com o novo peso
        $_SESSION["peso"] = $peso;
        
        // Feedback de sucesso
        $error_message = "Peso atualizado com sucesso!";
    }
}








// Verifica se há uma sessão válida
if (isset($_SESSION['peso'])) {
    $peso = $_SESSION['peso'];

    // Caminho para o arquivo JSON onde o peso será salvo
    // Exemplo de escrita no arquivo JSON
$jsonFile = 'peso.json';

// Verifica se o arquivo JSON existe e é gravável
if (is_writable($jsonFile)) {
    
    file_put_contents("peso.json", $peso);
    
} else {
    echo "O arquivo JSON não é gravável!";
}
} else {
    echo "Peso não encontrado na sessão!";
}






// Verifica se o botão de treino foi pressionado
if(isset($_POST["acao"])) {
    if($_POST["acao"] == 1) {
        // Enviar valor 1 para peso.json
        file_put_contents("bool.json", "1");
    } elseif($_POST["acao"] == 0) {
        // Enviar valor 0 para peso.json
        file_put_contents("bool.json", "0");
    }
}









// Verifica se o botão de logout foi pressionado
if(isset($_POST["logout"])) {
    // Se o treino estiver em andamento (valor 1 em peso.json), finaliza o treino
    if(file_get_contents("bool.json") == 1) {
        file_put_contents("bool.json", "0");
    }
    
    // Realiza o logout do usuário
    session_destroy();
    header("Location: index.php"); // Redireciona para a página de login (ou outra página desejada após logout)
    exit;
}
?>

<!DOCTYPE html>
<html lang="pt-br">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible"  content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Painel</title>
    <link rel="stylesheet" href="styles.css"> <!-- Importando o arquivo CSS externo -->
    <style>
        /* Estilo adicional inline para ajuste do espaço entre header e login-container */
        header.banner {
            margin-bottom: 10px; /* Espaço inferior reduzido para 10px */
        }
        
        /* Estilo para adicionar outline preto nas palavras */
        header.banner h1, header.banner p {
            text-shadow: -2px -2px 0 #000,  
                         2px -2px 0 #000,
                        -2px  2px 0 #000,
                         2px  2px 0 #000;
        }
    </style>
</head>
<body>
    <header class="banner">
        <h1>Crias' Gym</h1>
        <p>Bem vindo ao painel, <?php echo $_SESSION["nome"]; ?></p>
    </header>

    <div class="login-container">
        <h2>Atualize seu Peso</h2>
        <p>Seu peso atual: <?php echo $_SESSION["peso"]; ?> kg</p>
        <form action="" method="POST">
            <div class="form-group">
                <label for="novopeso">Novo Peso</label>
                <input type="number" id="novopeso" name="novopeso" required>
            </div>
            <button type="submit">Atualizar</button>
            <?php if (!empty($error_message)) : ?>
                <p class="error"><?php echo $error_message; ?></p>
            <?php endif; ?>
        </form>
        
        <!-- Botão de Treino ou Finalizar Treino -->
        <form action="" method="POST">
            <?php if (file_get_contents("bool.json") == 0 || !file_exists("bool.json")) : ?>
                <button type="submit" name="acao" value="1" style="background-color: #28a745; margin-top: 10px; color: #fff; border: none; border-radius: 4px; cursor: pointer; padding: 10px;">Treinar</button>
            <?php else : ?>
                <button type="submit" name="acao" value="0" style="background-color: #ffc107; margin-top: 10px; color: #fff; border: none; border-radius: 4px; cursor: pointer; padding: 10px;">Finalizar Treino</button>
            <?php endif; ?>
        </form>
        
        <!-- Botão de Logout -->
        <form action="" method="POST">
            <button type="submit" name="logout" style="background-color: #dc3545; margin-top: 10px; color: #fff; border: none; border-radius: 4px; cursor: pointer; padding: 10px;">Logout</button>
        </form>
    </div>

    <footer>
        <p>Direitos reservados aos Crias</p>
        <a href="https://www.instagram.com/criasinthehouse/" target="_blank">
            <img src="instagram-icon.png" alt="Instagram">
        </a>
    </footer>
</body>
</html>
