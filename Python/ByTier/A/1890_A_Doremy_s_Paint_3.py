# Contest 1890, Problem A: Doremy's Paint 3
# URL: https://codeforces.com/contest/1890/problem/A

for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    a.sort()
    mp = {}
    for i in a:
        if i not in mp:
            mp[i] = 0
        mp[i] += 1
    print("YES" if len(mp) < 3 and abs(mp[a[0]] - mp[a[-1]]) < 2 else "NO")
