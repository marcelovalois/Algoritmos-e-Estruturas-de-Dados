global N
global M
N = 8
M = 1

def printSolutionC(board): 
    for i in range(N): 
        for j in range(N): 
            print (board[i][j], end = " ") 
        print() 

def printSolution(board):
    if M >= 10:
        print('{}      '.format(M), end='')
    else:
        print(' {}      '.format(M), end='')
    for i in range(N):
        for j in range(N):
            if board[j][i]:
                if i+1 == N:
                    print(j+1)
                else:
                    print(j+1, end=' ')

def isSafe(board, row, col):
    for i in range(N):
        if board[row][i]:
            return False
    for i, j in zip(range(row, -1, -1), range(col, -1, -1)):
        if board[i][j]:
            return False
    for i, j in zip(range(row, N), range(col, N)):
        if board[i][j]:
            return False
    
    for i, j in zip(range(row, N), range(col, -1, -1)):
        if board[i][j]:
            return False
    for i, j in zip(range(row, -1, -1), range(col, N)):
        if board[i][j]:
            return False
    return True
        

def solveNQUtil(board, col, b):
    if col >= N:
        printSolution(board)
        global M
        M += 1
        return
    for i in range(N):
        if col == b:
            solveNQUtil(board, col+1, b)
            break
        if isSafe(board, i, col):
            board[i][col] = 1
            solveNQUtil(board, col+1, b)
            board[i][col] = 0

def solveNQ(a, b):
    board = [[0 for x in range(N)] for x in range(N)]
    board[a-1][b-1] = 1

    print('SOLN       COLUMN')
    print(' #      1 2 3 4 5 6 7 8')
    print()

    solveNQUtil(board, 0, b-1)


t = int(input())
for q in range(t):
    l = list(map(int, input().split(' ')))
    solveNQ(l[0], l[1])
    print()
    M = 1



# https://www.thehuxley.com/problem/422?locale=pt_BR

# Input:
# A primeira linha da entrada contém o número de casos de teste e é seguida de uma linha em branco.
# Cada caso de teste conterá dois números separados por um espaço. Nos números representam o quadrado no qual uma das oito rainhas está posicionada.
# Para padronizar a nossa notação, assuma que o canto superior esquerdo do tabuleiro é a posição (1,1). As linhas crescem horizontalmente e a primeira linha (mais acima) é 1. As colunas são verticais e a primeira coluna (mais a esquerda) é 1.
# Qualquer referência a uma posição é dada por linha e então por coluna. Por exemplo, a posição (4,6) representa a linha 4, coluna 6.


# Output:
# Para cada caso de teste a saída consiste de uma representação que mostra uma solução em uma única linha.

# Cada solução será numerada sequencialmente de 1 a n. Cada solução consiste de 8 números. Cada um dos 8 números será a linha daquela solução. A coluna da solução será indicada pela ordem na qual os 8 números são impressos. Isto é, o primeiro número representa a linha na qual a rainha está posicionada na coluna 1; o segundo número representa a linha da rainha na coluna 2; e assim por diante.

 

# Por exemplo, se a entrada for:

# 1

# 1 1

 

# Teríamos 4 soluções. A representação completa das soluções no tabuleiro seria:

 

#    SOLUÇÃO 1            SOLUÇÃO 2            SOLUÇÃO 3            SOLUÇÃO 4

 

# 1 0 0 0 0 0 0 0      1 0 0 0 0 0 0 0      1 0 0 0 0 0 0 0      1 0 0 0 0 0 0 0

# 0 0 0 0 0 0 1 0      0 0 0 0 0 0 1 0      0 0 0 0 0 1 0 0      0 0 0 0 1 0 0 0

# 0 0 0 0 1 0 0 0      0 0 0 1 0 0 0 0      0 0 0 0 0 0 0 1      0 0 0 0 0 0 0 1

# 0 0 0 0 0 0 0 1      0 0 0 0 0 1 0 0      0 0 1 0 0 0 0 0      0 0 0 0 0 1 0 0

# 0 1 0 0 0 0 0 0      0 0 0 0 0 0 0 1      0 0 0 0 0 0 1 0      0 0 1 0 0 0 0 0

# 0 0 0 1 0 0 0 0      0 1 0 0 0 0 0 0      0 0 0 1 0 0 0 0      0 0 0 0 0 0 1 0

# 0 0 0 0 0 1 0 0      0 0 0 0 1 0 0 0      0 1 0 0 0 0 0 0      0 1 0 0 0 0 0 0

# 0 0 1 0 0 0 0 0      0 0 1 0 0 0 0 0      0 0 0 0 1 0 0 0      0 0 0 1 0 0 0 0

 

# Nesse caso, você deve usar a seguinte representação para esse exemplo:

 

# SOLN       COLUMN

#  #      1 2 3 4 5 6 7 8

 

#  1      1 5 8 6 3 7 2 4

#  2      1 6 8 3 7 4 2 5

#  3      1 7 4 6 8 2 5 3

#  4      1 7 5 8 2 4 6 3

 

# Veja que, por exemplo, a solução 1: na primeira coluna, a dama está na linha 1; na segunda coluna, ela está na linha 5; na terceira coluna, na linha 8; e assim por diante.

 

# Inclua as duas linhas de cabeçalho como mostrado no exemplo. 

# Imprima as soluções na ordem lexicográfica.

# Imprima uma linha em branco entre casos de testes.

# Quando existirem mais do que 9 soluções, o alinhamento deve ser à esquerda, por exemplo:

# SOLN       COLUMN

#  #      1 2 3 4 5 6 7 8

 

#  1      5 3 1 6 8 2 4 7

#  2      5 3 1 7 2 8 6 4

#  3      5 3 8 4 7 1 6 2

#  4      6 3 1 7 5 8 2 4

#  5      6 3 1 8 4 2 7 5

#  6      6 3 1 8 5 2 4 7

#  7      6 3 5 7 1 4 2 8

#  8      6 3 5 8 1 4 2 7

#  9      6 3 7 2 4 8 1 5

# 10      6 3 7 2 8 5 1 4

# 11      6 3 7 4 1 8 2 5

# 12      7 3 1 6 8 5 2 4

# 13      7 3 8 2 5 1 6 4

# 14      8 3 1 6 2 5 7 4

 

# O número máximo de soluções é menor que 100.