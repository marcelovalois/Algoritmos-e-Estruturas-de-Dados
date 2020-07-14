# https://www.thehuxley.com/problem/845?locale=pt_BR

# Input:
# Na primeira linha você receberá 2 inteiros separados por espaço:

# n: indicando o número de árvores;
# m: indicando a quantidade de madeira necessária.

# A segunda linha contém n inteiros separados por espaços correspondendo a altura de cada árvore.

# Considere:

# 1 <= n <= 1 000 000
# 1 <= m <= 2 000 000 000


# Output:
# Um único número correspondendo a altura da configuração da super-serra.
# Atenção: a super-serra só pode ser configurada usando uma das alturas das árvores existentes. Ou seja, você não pode configurar a super-serra para uma altura de uma árvore que não exista.


def count(arv, hgt):
    soma = 0
    for i in arv:
        if i > hgt:
            soma += i - hgt
    return soma

def binarySearch(arr, l, r, x, menor=0):
    if r >= l:
        mid = l + (r-l)//2

        if count(arr, arr[mid]) == x:
            return mid

        elif count(arr, arr[mid]) > x:
            return binarySearch(arr, mid+1, r, x, mid)

        else:
            return binarySearch(arr, l, mid-1, x, menor)
    else:
        return menor


l = list(map(int, input().split(' ')))
n = l[0]; m = l[1]

arv = list(map(int, input().split(' ')))
arv.sort()

ind = binarySearch(arv, 0, n-1, m)
print(arv[ind])



