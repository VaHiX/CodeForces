# Contest 2130, Problem A: Submission is All You Need
# URL: https://codeforces.com/contest/2130/problem/A

for i in range(int(input())):
    n = int(input())
    lst = list(map(int, input().split()))
    print(sum(lst) + lst.count(0))
