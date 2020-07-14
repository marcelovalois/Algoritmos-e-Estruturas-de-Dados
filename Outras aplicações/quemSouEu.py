# https://www.thehuxley.com/problem/513?locale=pt_BR

class Stack:
    def __init__(self):
        self.items = []

    def push(self, item):
        self.items.append(item)

    def pop(self):
        return self.items.pop()

    def size(self):
        return len(self.items)

class Queue:
    def __init__(self):
        self.queue = []

    def push(self, n):
        self.queue.append(n)
    
    def pop(self):
        return self.queue.pop(0)

    def size(self):
        return len(self.queue)

t = int(input())
for i in range(t):
    fila = Queue()
    pilha = Stack()
    flagPilha = True; flagFila = True
    n = int(input())
    for j in range(n):
        l = list(map(int, input().split(' ')))
        if l[0] == 1:
            fila.push(l[1])
            pilha.push(l[1])
        elif l[0] == 2:
            f = fila.pop()
            if f != l[1]:
                flagFila = False
            p = pilha.pop()
            if p != l[1]:
                flagPilha = False

    print('caso {}: '.format(i+1), end='')

    if flagFila and flagPilha:
        print('ambas')
    elif flagPilha:
        print('pilha')
    elif flagFila:
        print('fila')
    else:
        print('nenhuma')


