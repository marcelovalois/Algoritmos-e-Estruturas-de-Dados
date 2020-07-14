# https://www.thehuxley.com/problem/890?locale=pt_BR

# Input:
# Dado três inteiros L, C e N, indicando respectivamente número de linhas, número de colunas do tabuleiro e número de rotações. Você receberá mais L linhas com C inteiros representando os valores do tabuleiro. 

# 1 <= L, C <= 10000

# -10000 <= N <= 10000


# Output:
# O estado que o tabuleiro ficará após as rotações, em cada linha os números serão separados com um espaço em branco.


def rotaciona(tab, l, c):
    newTab = []
    for i in range(c):
        aux = []
        for j in range(l-1, -1, -1):
            aux.append(tab[j][i])
        newTab.append(aux)
    return newTab

lis = list(map(int, input().split(' ')))
l = lis[0]; c = lis[1]; n = lis[2]
tab = []

for i in range(l):
    aux = list(map(int, input().split(' ')))
    tabAux = []
    for j in range(c):
        tabAux.append(aux[j])
    tab.append(tabAux)

for i in range(n%4):
    tab = rotaciona(tab, l, c)
    l = len(tab)
    c = len(tab[0])

for i in tab:
    for j in range(len(i)):
        if j+1 == len(i):
            print(i[j], end='')
        else:
            print(i[j], end=' ')
    print()