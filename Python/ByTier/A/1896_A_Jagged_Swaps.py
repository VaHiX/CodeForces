# Contest 1896, Problem A: Jagged Swaps
# URL: https://codeforces.com/contest/1896/problem/A

lst = [w.rstrip() for w in open(0).readlines()]
res = [["NO", "YES"][line[0:2] == "1 "] for line in lst[2::2]]
print("\n".join(res))
