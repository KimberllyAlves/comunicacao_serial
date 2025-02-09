# Controle de Matriz RGB e Display OLED via Comunicação Serial

## Descrição do Projeto
Este projeto explora a comunicação serial (UART e I2C) para controle de dispositivos utilizando a placa Raspberry Pi Pico. A implementação abrange:

✅ Exibição de caracteres no display SSD1306 recebidos via Serial Monitor.
✅ Representação de números na matriz de LEDs WS2812 ao receber valores entre 0 e 9.
✅ Interação com botões para alternância do LED RGB, com mensagens no display e logs no Serial Monitor.
✅ Uso de interrupções (IRQs) e debounce para garantir leituras confiáveis dos botões.

## Requisitos
- Microcontrolador: Raspberry Pi Pico ou Raspberry Pi Pico W (opcional).
- Simulador: Wokwi.
- Editor de Código: Visual Studio Code (VS Code).
- SDK do Raspberry Pi Pico corretamente configurado.
- Ferramentas de build: CMake e Ninja.

## Instruções de Uso

### 1. Clone o Repositório
```sh
git clone https://github.com/KimberllyAlves/comunicacao_serial.git
cd seu_repositorio
code .
```

### 2. Instale as Dependências
No VS Code, instale as extensões recomendadas:
- C/C++ (Microsoft)
- CMake Tools
- Wokwi Simulator
- Raspberry Pi Pico

### 3. Configure e Compile o Projeto
Abra o projeto no VS Code e siga os passos:
- Verifique se todas as extensões estão instaladas.
- No terminal, compile o código clicando em **Compile Project** na extensão do Raspberry Pi Pico.
- Um arquivo .uf2 será gerado para ser carregado no hardware real.

### 4. Simulação no Wokwi
- Abra o arquivo `diagram.json` no VS Code.
- Clique em **Play** para iniciar a simulação.
- Interaja com os componentes do projeto no ambiente virtual.

### 5. Execução no Hardware
Para rodar no Raspberry Pi Pico:
- Conecte a placa no modo **BOOTSEL**:
  1. Pressione e segure o botão BOOTSEL.
  2. Pressione e solte o botão RESET.
  3. Solte o botão BOOTSEL após alguns segundos.
- No VS Code:
  - Compile o projeto (**Compile Project**).
  - Clique em **Run Project USB** para executar diretamente na placa.

## Mapeamento de Conexões

| Componente             | GPIO |
|------------------------|------|
| Matriz de LEDs WS2812  | 7    |
| LED RGB Verde         | 11   |
| LED RGB Azul         | 12   |
| Botão A              | 5    |
| Botão B              | 6    |
| Display SSD1306 SDA  | 14   |
| Display SSD1306 SCL  | 15   |

## Funcionamento do Sistema

### 1. Inicialização
- O sistema aguarda a entrada de caracteres via Serial Monitor.
- O display SSD1306 e a matriz RGB são preparados para exibir informações.

### 2. Entrada de Dados via Serial
- Um caractere digitado no Serial Monitor é imediatamente exibido no display SSD1306.
- Se for um número entre 0 e 9, ele é representado na matriz de LEDs WS2812.

### 3. Interação com Botões
- **Botão A (GPIO 5)**: Alterna o LED RGB verde (ON/OFF), exibindo mensagem no display.
- **Botão B (GPIO 6)**: Alterna o LED RGB azul (ON/OFF), também exibindo mensagem.
- As mudanças são registradas no Serial Monitor.

### 4. Interrupções e Debounce
- Uso de interrupções (IRQ) para resposta rápida aos botões.
- Implementação de debounce via software para leituras precisas.

### 5. Controle da Matriz de LEDs
- Quando um número entre 0 e 9 é enviado via Serial Monitor, a matriz de LEDs exibe um símbolo correspondente.

### 6. Registros na Serial (UART)
- Logs das interações são exibidos no Serial Monitor para depuração.

## Demonstração
📽️ Confira um vídeo do funcionamento: [**[Link do Vídeo](#)**](https://drive.google.com/file/d/1qFZ9pxgPlHVaem2PTpxlvllQp2vnID62/view?usp=sharing)

