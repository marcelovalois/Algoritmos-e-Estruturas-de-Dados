# https://www.thehuxley.com/problem/2432?locale=pt_BR

# Input:
# A entrada começa com um número inteiro N que representa quantos conjuntos de entradas serão inseridos.
# Cada conjunto de entrada possuirá a descrição de um método que poderá ou não invocar outros, ou até mesmo a si próprio. A entrada é formada por várias strings (de no máximo 30 caracteres). As strings podem ser "return", indicando que o último método da pilha deve ser retornado, ou a string também pode ser algo diferente de "return" para indicar uma chamada de método. Você implementará uma pilha para simular as recursões. Use objetos para cada elemento dessa pilha. Listas/vetores ou estruturas de dados prontas são proibidas nessa questão. Quando um return deixar a pilha vazia, você saberá que o conjunto acabou. As strings estão espaçadas por um número arbitrário de espaços em brancos e quebras de linha.

# Output:
# A saída deve conter os nomes dos métodos na ordem em que são "retornados". Cada saída deve iniciar com "Conjunto #X", onde X será 1, 2, 3, ..., e deve ser impressa uma linha em branco ao final de cada conjunto.


class Stack:
    def __init__(self):
        self.items = []

    def push(self, item):
        self.items.append(item)

    def pop(self):
        return self.items.pop()

    def size(self):
        return len(self.items)

def excluiEspaco(string):
    string = string.split(" ")
    aux = []
    for i in string:
        if len(i)>0:
            aux.append(i)
    return aux

pilha = Stack()

n = int(input())
for i in range(n):
    print('Conjunto #{}'.format(i+1))
    while True:
        met = input()
        met = excluiEspaco(met)
        for j in met:
            if j == 'return':
                print(pilha.pop())
            else:
                pilha.push(j)
        
        if not pilha.size():
            break