# Cenários de teste

## Preparação

Abra o [circuito original](https://wokwi.com/projects/477646034464742401), inicie a simulação e aguarde a primeira leitura. O estado inicial do arquivo `diagram.json` é de 45% de umidade, 25 °C e 500 lux. No código, NPK começa ausente e a bomba desligada.

Para testar a decisão por umidade, primeiro deixe os três nutrientes presentes e ajuste o LDR para um pH próximo de 6,5, afastado dos limites. Use o valor de pH no monitor como referência, pois o controle do LDR mostra lux.

Após cada mudança, aguarde uma nova avaliação, realizada a cada dois segundos de tempo simulado. Uma simulação lenta exige mais tempo real. Confirme no monitor que a pressão do botão foi reconhecida antes de seguir.

Na demonstração da atividade, acompanhe cada alteração de NPK com um ajuste manual do LDR. Para isolar o efeito de um nutriente nos cenários T07 e T08, mude o pH entre valores internos à faixa permitida, por exemplo, de aproximadamente 6,2 para 6,5. Assim, há alteração nas duas entradas e o bloqueio continua sendo atribuível ao NPK. Os valores escolhidos não representam uma relação química calculada entre o nutriente e o pH.

## Registro de execução

Execução registrada no Wokwi em 12/10/2026, com os arquivos originais do projeto. A identificação da entrega foi corrigida posteriormente para Grupo 77. O registro serial e as capturas preservam a identificação usada na execução, Grupo 83; a lógica e as conexões permanecem iguais.

| Verificação executada | Resultado observado | Evidência |
| --- | --- | --- |
| Compilação e inicialização | A simulação iniciou e exibiu a identificação FarmTech Solutions — Grupo 83. | [Saída serial](registros/monitor-serial.txt) |
| Estado inicial | N, P e K ausentes; pH 3,42; umidade 45,0%; irrigação desligada; motivo: verificar NPK. | [Captura](imagens/02-bloqueio-npk.jpg) e [saída serial](registros/monitor-serial.txt) |

Nesse estado, tanto NPK quanto pH impedem a irrigação. A mensagem mostra NPK porque essa condição é verificada antes do pH na seleção do motivo. Portanto, a captura não isola o bloqueio por pH nem demonstra o acionamento da saída.

## Matriz de cenários para reprodução

Os resultados abaixo são os **resultados esperados a partir da lógica do código**. Com exceção do cenário inicial registrado acima, não são apresentados como execuções comprovadas pelas capturas deste repositório.

| ID | Preparação / alteração | Resultado esperado |
| --- | --- | --- |
| T01 | Reiniciar com os valores originais. | Irrigação desligada, NPK ausente. |
| T02 | NPK presente; pH próximo de 6,5; umidade 45%. | Irrigação ligada; LED azul acionado. |
| T03 | Partindo de T02, elevar a umidade para 60%. | Permanece ligada pela histerese. |
| T04 | Partindo de T03, elevar a umidade para 65%. | Desliga a irrigação. |
| T05 | Partindo de T04, reduzir a umidade para 60%. | Permanece desligada pela histerese. |
| T06 | Partindo de T05, reduzir a umidade para 54%. | Liga novamente. |
| T07 | Com a saída ligada, tornar N ausente, mantendo P/K presentes e pH permitido. | Desliga; motivo: verificar NPK. |
| T08 | Repetir T07 isoladamente para P e depois K, restaurando os outros nutrientes antes de cada tentativa. | Cada nutriente ausente bloqueia a saída. |
| T09 | NPK presente; umidade 45%; ajustar pH para um valor claramente abaixo de 5,5. | Desliga; motivo: pH fora da faixa definida. |
| T10 | NPK presente; umidade 45%; ajustar pH para um valor claramente acima de 7,5. | Desliga pelo mesmo motivo. |
| T11 | Corrigir NPK/pH após um bloqueio, mantendo umidade em 60%. | Continua desligada; só volta a ligar abaixo de 55%. |
| T12 | Ajustar umidade para exatamente 55%, primeiro vindo do estado ligado e depois do desligado. | Mantém o estado anterior em ambos os casos. |
| T13 | Reiniciar a simulação após alternar os nutrientes. | Nutrientes voltam a ausentes; saída começa desligada. |
| T14 | Com P/K presentes e umidade 45%, tornar N ausente e ajustar manualmente o pH para cerca de 5,0; depois restaurar N e pH próximo de 6,5. | Primeiro desliga, com prioridade da mensagem de NPK; depois liga quando todas as condições ficam permitidas. |

O código também prevê desligamento quando a umidade retorna `NaN`. A falha não foi injetada nesta execução e não há evidência de teste correspondente. Não é necessário alterar o circuito original para reproduzir os cenários T01–T14.

## Cuidados na interpretação

- O pH exibido é arredondado para duas casas; um valor visualmente igual a 5,50 ou 7,50 pode estar ligeiramente fora do limite interno. Para demonstrar a faixa válida, prefira um valor central.
- A mesma umidade de 60% pode produzir saída ligada ou desligada: isso é o comportamento previsto da histerese.
- A mudança de um botão precisa ultrapassar os 35 ms de estabilização no tempo do ESP32. Um clique muito breve pode não alternar o estado quando a simulação estiver lenta.
- Uma captura do estado desligado não comprova por si só o acionamento, a histerese ou todas as causas de bloqueio.
