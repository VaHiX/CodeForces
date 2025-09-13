# Contest 403, Problem A: Searching for Graph
# URL: https://codeforces.com/contest/403/problem/A


def main():
    t = int(input())

    for _ in range(t):
        n, p = map(int, input().split())
        total = 2 * n + p

        graph = [[0] * (n + 1) for _ in range(n + 1)]

        for i in range(1, n + 1):
            for j in range(1, n + 1):
                if i != j and graph[i][j] == 0:
                    print(i, j)
                    total -= 1
                    graph[i][j] = 1
                    graph[j][i] = 1
                if total == 0:
                    break
            if total == 0:
                break


if __name__ == "__main__":
    main()  # 1690457876.0419505
