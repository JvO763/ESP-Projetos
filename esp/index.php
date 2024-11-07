<?php
include('conexao.php');

if(isset($_POST["nome"]) || isset($_POST['senha'])) {

    if(strlen($_POST['nome']) == 0) {
        $error_message = "Preencha seu e-mail";
    } else if(strlen($_POST['senha']) == 0) {
        $error_message = "Preencha sua senha";
    } else {

        $nome = $mysqli->real_escape_string($_POST['nome']);
        $senha = $mysqli->real_escape_string($_POST['senha']);

        $sql_code = "SELECT * FROM tabelin WHERE nome = '$nome' AND senha = '$senha'";
        $sql_query = $mysqli->query($sql_code) or die("Falha na execução do código SQL:" . $mysqli->error);

        $quantidade = $sql_query->num_rows;

        if($quantidade == 1) {
            
            $usuario = $sql_query->fetch_assoc();

            if(!isset($_SESSION)) {
                session_start();
            }

            $_SESSION['id'] = $usuario['id'];
            $_SESSION['nome'] = $usuario['nome'];
            $_SESSION['peso'] = $usuario['peso'];

            header("Location: painel.php");

        } else {
            $error_message = "Falha ao logar! E-mail ou senha incorretos";
        }

    }

}
?>
<!DOCTYPE html>
<html lang="pt-br">
<style>
        /* Estilo adicional inline para ajuste do espaço entre header e login-container */
        header.banner {
            margin-bottom: 10px; /* Espaço inferior reduzido para 10px */
        }
        
        /* Estilo para adicionar outline preto nas palavras */
        header.banner h1, header.banner p {
            text-shadow: -2px -2px 0 #000,  
                         2px -2px 0 #000,
                        -2px 2px 0 #000,
                         2px 2px 0 #000;
        }
    </style>
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Login - Crias' Gym</title>
    <link rel="stylesheet" href="styles.css">
</head>
<body>
    <header class="banner">
        <h1>Crias' Gym</h1>
    </header>
    <div class="login-container">
        <h2>Acesse sua conta</h2>
        <form action="" method="POST">
            <p>
                <label>Usuário</label>
                <input type="text" name="nome" required>
            </p>
            <p>
                <label>Senha</label>
                <input type="password" name="senha" required>
            </p>
            <p>
                <button type="submit">Entrar</button>
            </p>
        </form>
        <?php
            if (isset($error_message)) {
                echo '<p class="error">' . $error_message . '</p>';
            }
        ?>
    </div>
    <footer>
        <p>Direitos reservados aos Crias</p>
        <a href="https://www.instagram.com/criasinthehouse/" target="_blank">
            <img src="instagram-icon.png" alt="Instagram">
        </a>
    </footer>
</body>
</html>
