# Contest 2044, Problem B: Normal Problem
# URL: https://codeforces.com/contest/2044/problem/B

for _ in range(int(input())):
    a = input().strip()
    b = a[::-1].translate(str.maketrans("pqw", "qpw"))
    print(b)
