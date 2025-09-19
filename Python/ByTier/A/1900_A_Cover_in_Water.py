# Contest 1900, Problem A: Cover in Water
# URL: https://codeforces.com/contest/1900/problem/A

for _ in range(int(input())):
    a = int(input())
    s = input()
    if "..." in s:
        print(2)
    else:
        print(s.count("."))
