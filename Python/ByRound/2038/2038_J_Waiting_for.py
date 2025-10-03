# Contest 2038, Problem J: Waiting for...
# URL: https://codeforces.com/contest/2038/problem/J

cnt = 0
for _ in range(int(input())):
    tp, p = input().split()
    p1 = int(p)
    if tp == "P":
        cnt += p1
    else:
        print("YES" if cnt <= p1 - 1 else "NO")
        cnt = 0 if cnt <= p1 else cnt - p1
