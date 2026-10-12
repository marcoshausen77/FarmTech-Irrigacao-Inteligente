# Roteiro de demonstração

## Sequência sugerida

1. Apresente a FarmTech Solutions, o Grupo 83, o Projeto 2 — Iniciando a Coleta de Dados e o cultivo de tomate.
2. Mostre o circuito completo: ESP32, três botões verdes de NPK, LDR, DHT22, relé, resistor e LED azul que representa a bomba.
3. Explique que os componentes representam grandezas agrícolas: o LDR não mede pH real, o DHT22 não mede umidade do solo e os botões não medem concentração de nutrientes.
4. Mostre no código os pinos, a conversão analógica para pH, os limites 5,5–7,5 e os limiares de umidade de 55% e 65%.
5. Inicie a simulação e mostre o estado inicial bloqueado no monitor serial.
6. Deixe NPK presente, ajuste o pH para dentro da faixa e mantenha a umidade abaixo de 55%. Mostre a mensagem de irrigação ligada e o LED.
7. Eleve a umidade para 60% e depois 65%, mostrando a manutenção do estado e o desligamento. Reduza para 60% para demonstrar que a saída continua desligada.
8. Com umidade abaixo de 55%, demonstre separadamente o bloqueio pela ausência de um nutriente e pelo pH fora da faixa. Restaure as condições entre os testes.
9. Mostre o repositório, os três arquivos do Wokwi, o README e as evidências. Encerre explicando os limites acadêmicos do protótipo.

Use a duração e o formato exigidos no enunciado da atividade. Aguarde o monitor atualizar antes de narrar o resultado de cada mudança. As falas sobre acionamento devem acompanhar o estado efetivamente mostrado na gravação.
