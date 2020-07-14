# https://www.thehuxley.com/problem/150?locale=pt_BR

# Input:
# A primeira linha contém um inteiro positivo H (H<=15) significando a altura da árvore. A segunda linha contém os inteiros positivos correspondendo aos nós da árvore. O i-ésimo inteiro corresponde ao valor de Vi.

# Por exemplo, a árvore abaixo é representada pela entrada:
# 3
# 3 1 5 2 6 4 7

#      3
#     / \
#    /   \
#   1     5
#  / \   / \
# 2   6 4   7

# O valor de P1 nesse caso é de 105.


# Output:
# Imprima o valor de P1 encontrado.


class newNode():
    def __init__(self, data):
        self.key = data
        self.left = None
        self.right = None

def inorder(temp): 
    if (not temp): 
        return
    inorder(temp.left)  
    print(temp.key,end = " ") 
    inorder(temp.right)  

def insert(temp,key): 
    q = []  
    q.append(temp)    
    while (len(q)):  
        temp = q[0]  
        q.pop(0)  
        if (not temp.left): 
            temp.left = newNode(key)  
            break
        else: 
            q.append(temp.left)  
  
        if (not temp.right): 
            temp.right = newNode(key)  
            break
        else: 
            q.append(temp.right)

def max(a, b):
    if a>b:
        return a
    else:
        return b

def calculaP(temp):
    if not temp.left and not temp.right:
        return temp.key
    pl = calculaP(temp.left)
    pr = calculaP(temp.right)
    p = max(temp.key*pl, temp.key*pr)
    return p


### Main ###:
h = int(input())
strg = input()
strg = strg.split(" ")
lista = list(map(int, strg))

root = newNode(lista[0])
for i in range(1, len(lista)):
    insert(root, lista[i])

print(calculaP(root))