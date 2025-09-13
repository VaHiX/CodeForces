# Contest 2140, Problem A: Shift Sort
# URL: https://codeforces.com/contest/2140/problem/A

for _ in range(int(input())):
    n = int(input())
    s = input()
    s1 = s.count("0")
    ans = s[:s1].count("1")
    print(ans)
