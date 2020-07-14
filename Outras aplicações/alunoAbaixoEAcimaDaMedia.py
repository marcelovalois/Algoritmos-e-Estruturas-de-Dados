# https://www.thehuxley.com/problem/960?locale=pt_BR

# Input:
# Uma linha contendo um inteiro N que representa a quantidade de alunos. Nas linhas seguintes devem ser lidos o número de matrícula (inteiro), o nome (string) e a nota (ponto flutuante) de cada um dos N alunos, sendo todos os dados de um aluno fornecidos em uma linha e separados por um hífen (sinal de menos).


# Output:
# A saída consiste da lista com a nota (uma casa decimal), o número de matrícula e o nome dos alunos com nota abaixo da média, seguido de uma lista com os dados dos alunos com nota maior ou igual à média dos alunos. Os dados devem estar, ordenados pela nota. Em caso de empate na nota, a ordenação será pelo número de matrícula, que é único para cada aluno. Após os dados dos alunos, deve ser impressa a média, com 2 casas decimais.
# O formato de saída deve seguir o seguinte padrão:
# Alunos abaixo da media:
# Matricula: 999999 Nome: NNN Nota: 99.9
# Matricula: 999999 Nome: NNN Nota: 99.9
# Alunos acima ou iguais a media:
# Matricula: 999999 Nome: NNN Nota: 99.9
# Media = 99.99
# Note que há um espaço em branco após o caractere ':' e antes e depois do caractere '='. Observe também que é necessário colocar as strings “Alunos abaixo da media:” e “Alunos iguais ou acima da media:”.


class Node:
    def __init__(self, val=None, matricula=None, nome=None):
        self.left = None
        self.right = None
        self.val = val
        self.mat = matricula
        self.nome = nome

def insert(root, node):
    if root is None:
        root = node
    else:
        if root.val < node.val:
            if root.right is None:
                root.right = node
            else:
                insert(root.right, node)
        elif root.val > node.val:
            if root.left is None:
                root.left = node
            else:
                insert(root.left, node)
        else:
            if root.mat < node.mat:
                if root.right is None:
                    root.right = node
                else:
                    insert(root.right, node)
            else:
                if root.left is None:
                    root.left = node
                else:
                    insert(root.left, node)

def printFormat(root, flag):
    if flag[0]:
        print('Alunos abaixo da media:')
        flag[0] = False
    if root.val >= media and flag[1]:
        print('Alunos iguais ou acima da media:')
        flag[1] = False

def printAluno(root):
    print('Matricula:', root.mat, 'Nome:', root.nome, 'Nota:', '{:.1f}'.format(root.val))

def inorder(root, media, flag=[True, True]):
    if root:
        inorder(root.left, media, flag)
        printFormat(root, flag)
        printAluno(root)
        inorder(root.right, media, flag)



reg = None
acum = 0
n = int(input())

for i in range(n):
    str1 = input().split('-')
    aux = Node(float(str1[2]), int(str1[0]), str1[1])
    acum += float(str1[2])
    if not i:
        reg = aux
    else:
        insert(reg, aux)
media = acum/n
inorder(reg, media)
print('Media =', '{:.2f}'.format(media))
