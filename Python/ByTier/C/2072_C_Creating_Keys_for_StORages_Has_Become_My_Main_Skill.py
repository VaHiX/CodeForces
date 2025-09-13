# Contest 2072, Problem C: Creating Keys for StORages Has Become My Main Skill
# URL: https://codeforces.com/contest/2072/problem/C

for _ in range(int(input())):
    n, k = map(int, input().split())
    ans = [i & k for i in range(n)]
    x = 0
    for i in ans:
        x |= i
    if x < k:
        ans[-1] |= k
    print(*ans)
