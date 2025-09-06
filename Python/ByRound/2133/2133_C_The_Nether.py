# Contest 2133, Problem C: The Nether
# URL: https://codeforces.com/contest/2133/problem/C

for _ in range(int(input())):
    n = int(input())
    S = [[] for i in range(n+1)]

    all_n = " ".join([str(k) for k in range(1, n+1)])
    m = 0

    for v in range(1, n+1):
        print("?", v, n, all_n)
        ans = int(input())
        S[ans].append(v)
        m = max(ans, m)

    x = [S[m][0]]
    for i in range(m-1, 0, -1):
        for next_x in S[i]:
            print("?", x[-1], 2, x[-1], next_x)
            ans = int(input())
            if ans == 2:
                x.append(next_x)
                break

    print("!", len(x), *x)
    
