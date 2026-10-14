# Roteiro de demonstração

Vídeo da entrega: **[FarmTech Solutions — Irrigação inteligente com ESP32](https://youtu.be/kmIAH3_Zi18)**, com **1 minuto e 49 segundos**, publicado como **não listado**.

A sequência abaixo é um roteiro de apoio para uma apresentação de até 5 minutos, não uma transcrição ou indicação dos tempos do vídeo publicado.

| Tempo sugerido | Conteúdo |
| --- | --- |
| 0:00–0:25 | Identificação do Grupo 77, objetivo e cultivo de tomate. |
| 0:25–1:05 | Circuito, conexões e caráter simulado dos sensores. |
| 1:05–1:40 | Pesquisa sobre o tomate e regras do código. |
| 1:40–2:20 | Estado inicial, ajuste de NPK e LDR, acionamento com umidade baixa. |
| 2:20–3:15 | Umidade em 60%, desligamento em 65% e retorno a 60%. |
| 3:15–4:15 | Bloqueios por NPK e pH, com ajustes manuais no LDR. |
| 4:15–4:40 | Repositório, documentação e encerramento. |

## Sequência sugerida

1. Apresente a FarmTech Solutions, o Grupo 77, o Projeto 2 — Iniciando a Coleta de Dados e o cultivo de tomate.
2. Mostre o circuito completo: ESP32, três botões verdes de NPK, LDR, DHT22, relé, resistor e LED azul que representa a bomba.
3. Explique que os componentes representam grandezas agrícolas: o LDR não mede pH real, o DHT22 não mede umidade do solo e os botões não medem concentração de nutrientes.
4. Resuma a importância de NPK, pH e água para o tomate usando as referências da Embrapa no README. Mostre no código os pinos, a conversão analógica para pH, os limites 5,5–7,5 e os limiares de umidade de 55% e 65%. Diferencie a pesquisa agronômica dos limites didáticos adotados.
5. Inicie a simulação e mostre o estado inicial bloqueado no monitor serial.
6. Deixe NPK presente, ajuste o pH para dentro da faixa e mantenha a umidade abaixo de 55%. Mostre a mensagem de irrigação ligada e o LED.
7. Eleve a umidade para 60% e depois 65%, mostrando a manutenção do estado e o desligamento. Reduza para 60% para demonstrar que a saída continua desligada.
8. Com umidade abaixo de 55%, demonstre separadamente o bloqueio pela ausência de um nutriente e pelo pH fora da faixa. Ao alterar NPK, ajuste também o LDR manualmente. Para isolar o bloqueio por nutriente, altere o pH entre valores permitidos, como 6,2 e 6,5. Para demonstrar o bloqueio por pH, deixe NPK presente e leve o pH para fora da faixa. Restaure as condições entre os testes.
9. Mostre o repositório, os três arquivos do Wokwi, o README e as evidências. Encerre explicando os limites acadêmicos do protótipo.

Mostre o módulo de relé e o LED indicador junto com a leitura serial. Aguarde o monitor atualizar antes de narrar o resultado de cada mudança. As falas sobre acionamento devem acompanhar o estado efetivamente mostrado na gravação. Se necessário, corte tempos de espera sem alterar a ordem das ações e dos resultados.

Antes de entregar, confira que o vídeo tem no máximo 5:00, está como **não listado** (e não privado), abre pelo link e demonstra tanto o acionamento quanto o desligamento da irrigação. Os opcionais de Python/API meteorológica e R não fazem parte desta apresentação.
