# Contest 2064, Problem A: Brogramming Contest
# URL: https://codeforces.com/contest/2064/problem/A

for _ in range(int(input())):
    n = int(input())
    s = input()
    s = "0" + s
    print(s.count("01") + s.count("10"))
