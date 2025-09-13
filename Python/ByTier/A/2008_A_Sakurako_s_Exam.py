# Contest 2008, Problem A: Sakurako's Exam
# URL: https://codeforces.com/contest/2008/problem/A

for _ in range(int(input())):
    a, b = map(int, input().split())
    print('NO' if a & 1 or not a and b & 1 else 'YES')
