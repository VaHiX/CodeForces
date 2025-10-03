# Contest 9, Problem E: Interestring graph and Apples
# URL: https://codeforces.com/contest/9/problem/E

N, M = [int(w) for w in input().split()]

data = list(range(N + 1))


def find(x: int) -> int:
    if data[x] == x:
        return x
    data[x] = find(data[x])
    return data[x]


def join(x: int, y: int):
    x = find(x)
    y = find(y)
    data[y] = x


degrees = [0] * (N + 1)
for i in range(M):
    u, v = [int(w) for w in input().split()]
    degrees[u] += 1
    degrees[v] += 1
    if degrees[u] > 2 or degrees[v] > 2 or (u == v and N > 1):
        print("NO")
        exit(0)
    if find(u) == find(v):
        if i == M - 1 and (degrees.count(2) == N):
            print("YES")
            print("0")
            exit(0)
        else:
            print("NO")
            exit(0)
    join(u, v)

nodes = (
    [i for i in range(1, N + 1) if degrees[i] == 1]
    + [i for i in range(1, N + 1) if degrees[i] == 0]
    + [i for i in range(1, N + 1) if degrees[i] == 0]
)
nodes.sort(reverse=True)

if len(nodes) % 2 == 1:
    print("NO")
    exit(0)

print("YES")
k = len(nodes) // 2
print(k)
for i in range(k):
    a, b = -1, -1
    a = nodes[-1]
    nodes.pop()
    if i == k - 1:
        for j in range(len(nodes) - 1, -1, -1):
            if nodes[j] > 0:
                print(a, nodes[j])
                nodes[j] = -1
                break
    else:
        for j in range(len(nodes) - 1, -1, -1):
            if nodes[j] > 0 and find(a) != find(nodes[j]):
                join(a, nodes[j])
                print(a, nodes[j])
                nodes[j] = -1
                break
    while nodes and nodes[-1] == -1:
        nodes.pop()
