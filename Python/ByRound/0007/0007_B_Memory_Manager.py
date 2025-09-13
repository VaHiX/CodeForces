# Contest 7, Problem B: Memory Manager
# URL: https://codeforces.com/contest/7/problem/B


n, m = map(int, input().split())
a = [input() for i in range(n)]
M = [0] * m
I = 1


def alloc(x):
    global I
    x = int(x.split()[1])
    for i in range(m - x + 1):
        if M[i : i + x] == [0] * x:
            M[i : i + x] = [I] * x
            print(I)
            I += 1
            return ()
    print("NULL")


def erase(x):
    global M
    x = int(x.split()[1])
    if x < 1 or x not in M:
        print("ILLEGAL_ERASE_ARGUMENT")
    for i in range(m):
        if M[i] == x:
            M[i] = 0


def defragment(x):
    global M
    M = [i for i in M if i != 0]
    M += [0] * (m - len(M))


f = {"alloc": alloc, "erase": erase, "defragment": defragment}
for i in a:
    f[i.split()[0]](i)
