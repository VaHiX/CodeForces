# Contest 2085, Problem A: Serval and String Theory
# URL: https://codeforces.com/contest/2085/problem/A

for t in range(int(input())):
    n, k = map(int, input().split())
    s = input()
    if n == 1 or set(s) == set(s[0]) or (k == 0 and s >= s[::-1]):
        print("NO")
    else:
        print("YES")
