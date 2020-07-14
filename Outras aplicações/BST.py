# https://www.thehuxley.com/problem/516?locale=pt_BR

class Node:
    def __init__(self, val=None, level=None):
        self.left = None
        self.right = None
        self.val = val
        self.level = level

def maiores(root, x, count=0):
    if root:
        count = maiores(root.left, x, count)
        if root.val > x:
            count += 1
        count = maiores(root.right, x, count)
    return count

def kth(root, x, count=0):
    if root:
        count = kth(root.left, x, count)
        count += 1
        if count == x:
            print(root.val)
        count = kth(root.right, x, count)
    return count

def inOrder(root):
    if root:
        inOrder(root.left)
        print(root.val)
        inOrder(root.right)
    
def insert(root, key, count=-1):
    count += 1
    res = None  #Pra saber a altura
    if root.val is None:
        root.val = key
        root.level = count
        res = count
    else:
        if root.val < key:
            if root.right is None:
                root.right = Node(key, count)
                res = count + 1
            else:
                res = insert(root.right, key, count)
        elif root.val > key:
            if root.left is None:
                root.left = Node(key, count)
                res = count + 1
            else:
                res = insert(root.left, key, count)
        else:
            return count
    return res

def minValueNode(node):
    current = node
    while current.left is not None:
        current = current.left
    return current

def remove(root, key, count=-1):
    count += 1
    global level  #Pra saber a altura
    level = -1
    if root is None:
        return root
    if root.val is None:
        return root
    if key < root.val:
        root.left = remove(root.left, key, count)
    elif key > root.val:
        root.right = remove(root.right, key, count)
    else:
        level = count
        if root.left is None:
            temp = root.right
            root = None
            return temp
        elif root.right is None:
            temp = root.left
            root = None
            return temp
        
        temp = minValueNode(root.right)
        root.val = temp.val
        root.right = remove(root.right, temp.val)
        level = count
    return root


level = 0

t = int(input())
for i in range(t):
    root = Node()
    n = int(input())
    for j in range(n):
        entr = list(map(int, input().split(" ")))
        if entr[0] == 1:
            print(insert(root, entr[1]))
        if entr[0] == 2:
            remove(root, entr[1])
            print(level)
        if entr[0] == 3:
            print(maiores(root, entr[1]))
        if entr[0] == 4:
            kth(root, entr[1])
    print('')

