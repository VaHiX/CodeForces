# Contest 2050, Problem G: Tree Destruction
# URL: https://codeforces.com/contest/2050/problem/G

# 9cfe1c64-5846-45ee-b17c-d0f6983d8c7c
import sys


def main():
    input = sys.stdin.read().split()
    ptr = 0
    t = int(input[ptr])
    ptr += 1
    for _ in range(t):
        n = int(input[ptr])
        ptr += 1
        adj = [[] for _ in range(n + 1)]
        for __ in range(n - 1):
            u = int(input[ptr])
            v = int(input[ptr + 1])
            adj[u].append(v)
            adj[v].append(u)
            ptr += 2
        degrees = [0] * (n + 1)
        for u in range(1, n + 1):
            degrees[u] = len(adj[u])
        max_deg = max(degrees[1:])
        max_sum = -float("inf")
        max_single = [0] * (n + 1)
        stack = [(1, -1, False)]
        while stack:
            u, parent, visited = stack.pop()
            if not visited:
                stack.append((u, parent, True))
                for v in adj[u]:
                    if v != parent:
                        stack.append((v, u, False))
            else:
                max1 = max2 = 0
                for v in adj[u]:
                    if v == parent:
                        continue
                    current = max_single[v]
                    if current > max1:
                        max2 = max1
                        max1 = current
                    elif current > max2:
                        max2 = current
                current_sum = max1 + max2 + (degrees[u] - 2)
                if current_sum > max_sum:
                    max_sum = current_sum
                max_single[u] = (degrees[u] - 2) + max1
        answer = max(max_deg, max_sum + 2)
        print(answer)


if __name__ == "__main__":
    main()
