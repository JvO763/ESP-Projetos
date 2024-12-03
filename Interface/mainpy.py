import tkinter as tk
from tkinter import messagebox
from tkinter import PhotoImage
import serial
import time

# Configura a porta serial (ajuste a COM correta para seu sistema)
try:
    esp32 = serial.Serial("COM11", baudrate=115200, timeout=1)
    time.sleep(2)  # Dá um tempo para a conexão estabilizar
except Exception as e:
    messagebox.showerror("Erro", f"Erro ao conectar na porta serial: {e}")
    esp32 = None

# Função para enviar o valor selecionado
def enviar_valor():
    if esp32 and esp32.is_open:
        valor = int(slider.get())
        esp32.write(f"{valor}\n".encode('utf-8'))  # Envia o valor para a ESP32
        messagebox.showinfo("Enviado", f"Valor {valor} enviado para a ESP32!")
    else:
        messagebox.showerror("Erro", "Porta serial não está aberta.")

# Função para animação de fade-in
def fade_in():
    alpha = 0.0
    while alpha < 1.0:
        janela.attributes("-alpha", alpha)
        janela.update()
        time.sleep(0.02)
        alpha += 0.05

# Criação da interface gráfica
janela = tk.Tk()
janela.title("H.A.M. Project - Interface")
janela.geometry("400x300")
janela.configure(bg="#2b2b2b")
janela.attributes('-topmost', True)  # Janela sempre na frente
janela.update()

# Adicionando imagem de fundo
try:
    fundo = PhotoImage(file="background.png")  # Substitua por um caminho válido
    fundo_label = tk.Label(janela, image=fundo)
    fundo_label.place(relwidth=1, relheight=1)
except:
    janela.configure(bg="#2b2b2b")  # Se não houver imagem, usa um fundo sólido

# Título
titulo = tk.Label(
    janela,
    text="Controle H.A.M. - ESP32",
    font=("Helvetica", 18, "bold"),
    fg="#ffffff",
    bg="#2b2b2b"
)
titulo.pack(pady=10)

# Criando um frame para centralizar o slider e o rótulo
frame_slider = tk.Frame(janela, bg="#2b2b2b")
frame_slider.pack(pady=20)

# Rótulo centralizado acima do slider
label_slider = tk.Label(
    frame_slider,
    text="Selecione o valor",
    font=("Helvetica", 12),
    fg="#ffffff",
    bg="#2b2b2b"
)
label_slider.pack()

# Adicionando o slider
slider = tk.Scale(
    frame_slider,
    from_=0, to=40,
    orient=tk.HORIZONTAL,
    font=("Helvetica", 12),
    fg="#ffffff",
    bg="#4b4b4b",
    troughcolor="#2b2b2b",
    highlightbackground="#2b2b2b",
    length=300
)
slider.pack()

# Botão para enviar o valor
btn_enviar = tk.Button(
    janela,
    text="Enviar",
    command=enviar_valor,
    font=("Helvetica", 14, "bold"),
    fg="#ffffff",
    bg="#4caf50",
    activebackground="#45a049",
    relief=tk.RAISED,
    bd=3
)
btn_enviar.pack(pady=10)

# Rodapé
rodape = tk.Label(
    janela,
    text="© 2024 Projeto H.A.M.",
    font=("Helvetica", 10),
    fg="#aaaaaa",
    bg="#2b2b2b"
)
rodape.pack(side=tk.BOTTOM, pady=5)

# Aplica animação de fade-in
fade_in()

# Executa a interface gráfica
janela.mainloop()

# Fecha a porta serial ao encerrar
if esp32 and esp32.is_open:
    esp32.close()

