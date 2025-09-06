# Contest 1500, Problem A: Going Home
# URL: https://codeforces.com/contest/1500/problem/A

def main():
    n = int(input())
    a = list(map(int, input().split()))
    counters = dict()
    for i in range(1, n):
        for j in range(i):
            s = a[i] + a[j]
            if s not in counters:
                counters[s] = (i, j)
                continue
            prev = counters[s]
            if i not in prev and j not in prev:
                print("YES")
                print(i + 1, j + 1, prev[0] + 1, prev[1] + 1)
                return
    print("NO")


main()
