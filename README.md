# DungeonCards

## Compilação

$ make

Precisa da SDL2 instalada.

Testado somente em Linux.

## Execução

$ ./GAME

## Regras
Cada carta pode realizar um movimento em cada turno.

Os turnos alteram entre Habiliaddes, Ataque, Inimigo, Evento.

O turno do jogador é alterado cada ver que o ponteiro do relógio aponta para 12.

### Habilidades

Cada jogador escolhe entre duas das habilidades que possui, em seguida escolhe o alvo da habilidade.

### Ataque

Cada jogador escolhe uma carta para atacar.

### Inimigo

Cada inimigo ataca uma carta de jogador aleatória.

### Evento

Uma carta de evento aleatória é escolhida e o evento correspondente ocorre.

### Fim do jogo

A partida termina quando todas as cartas de jogador ou de inimigo ficam com 0 de vida.

## Controles

### Menu inicial

#### w, s - Altera entre opções, para cima e para baixo

#### barra de espaço - Escolhe a opção selecionada

### Mapa

#### ESC - Volta a tela anterior

#### ALT + F4 - Fecha o jogo

#### a, d - Altera entre próxima fase e fase anterior

#### barra de espaço - Inicia a fase

### Durante a fase de ataque e habilidade:

#### w, a, s, d - Movimenta o cursor do P1 no tabuleiro

#### direcionais - Movimenta o cursor do P2 no tabuleiro

#### i, j, k, l - Movimenta o cursor do P3 no tabuleiro

#### q - P1 ataca/seleciona habilidade/usa habilidade que o cursor aponta

#### barra de espaço - P2 ataca/seleciona habilidade/usa habilidade que o cursor aponta

#### u - P3 ataca/seleciona habilidade/usa habilidade que o cursor aponta
