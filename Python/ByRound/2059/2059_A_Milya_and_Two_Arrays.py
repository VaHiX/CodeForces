# Contest 2059, Problem A: Milya and Two Arrays
# URL: https://codeforces.com/contest/2059/problem/A

for _ in range(int(input())):
    n = int(input())
    a = len(set(input().split()))
    b = len(set(input().split()))
    print("YES" if a * b >= 3 else "NO")
