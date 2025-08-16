# Contest 2124, Problem I: Lexicographic Partition
# URL: https://codeforces.com/contest/2124/problem/I

from collections import deque

def solve(b, inv):
    n = len(b)
    if len(inv[1]) > 1:
        return []

    a = [0] * n
    s = deque()
    if len(inv[2]) > 1:
        a[0] = 1
        s.append((0, n-1, 2, n, 1))
    else:
        a[0] = n
        s.append((0, n-1, 1, n-1, 1))

    while s:
        l, r, leftNum, rightNum, ok = s.pop()
        if l == r:
            continue
        if b[l + 1] != b[l] + 1:
            return []
        num = b[l] + 1
        if num >= len(inv):
            return []

        nxt = []
        while inv[num] and inv[num][-1] > l:
            nxt.append(inv[num].pop())
        if not nxt:
            return []
        if not ok and len(nxt) != 1:
            return []
        if len(nxt) == 1:
            if num + 1 < len(inv) and len(inv[num + 1]) > 1 and inv[num + 1][-2] > l:
                a[nxt[0]] = leftNum
                leftNum += 1
            else:
                a[nxt[0]] = rightNum
                rightNum -= 1
            s.append((l + 1, r, leftNum, rightNum, 1))
        else:
            rightNum -= len(nxt)
            nx = rightNum + 1
            nxt.reverse()
            curLeft = leftNum
            for i in range(len(nxt)):
                pos = nxt[i]
                a[pos] = nx
                nx += 1
                nextInd = nxt[i + 1] - 1 if i + 1 < len(nxt) else r
                sz = nextInd - pos - 1
                s.append((pos, nextInd, curLeft, curLeft + sz, 0))
                curLeft += sz + 1

    return a

def main():
    import sys
    input = sys.stdin.read
    data = input().splitlines()
    
    t = int(data[0])
    index = 1
    results = []
    
    for _ in range(t):
        n = int(data[index])
        x = list(map(int, data[index + 1].split()))
        index += 2
        
        inv = [[] for _ in range(n + 3)]
        for i in range(n):
            inv[x[i]].append(i)

        a = solve(x, inv)
        if not a:
            results.append("NO")
        else:
            results.append("YES")
            results.append(" ".join(map(str, a)))

    print("\n".join(results))

if __name__ == "__main__":
    main()