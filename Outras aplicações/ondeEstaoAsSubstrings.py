# https://www.thehuxley.com/problem/970?locale=pt_BR

# Input:
# Duas Frases A e B, uma por linha contendo apenas caracteres maiúsculos e espaços.
# obs: os espaços fazem parte da frase, ou seja, eles contam como um caractere normal.
# o tamanho de B sempre é menor ou igual ao tamanho de A.
# A terá no máximo 250 caracteres.


# Output:
# Todas as sequências de incides de A que formam B.
# uma por linhas, e em ordem crescente de seus índices.
# caso não ache nenhuma sequência válida imprima -1.

def printTable(table, szb):
    for i in range(szb):
        if i == szb-1:
            print(table[i])
        else:
            print(table[i], end=' ')
    
def solve(table, sza, szb, a, b, posB, posA, flag): 
    for i in range(posA, sza):
        if b[posB] == a[i]:
            table[posB] = i+1
            if posB+1 == szb:
                printTable(table, szb)
                flag = False
            else:
               flag = solve(table, sza, szb, a, b, posB+1, i+1, flag)
    if flag and not posB:
        print(-1)
    return flag

a = input()
b = input()
table = []
for i in b:
    table.append(0)
sza = len(a)
szb = len(b)

solve(table, sza, szb, a, b, 0, 0, True)