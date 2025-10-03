# Contest 2003, Problem B: Turtle and Piggy Are Playing a Game 2
# URL: https://codeforces.com/contest/2003/problem/B

for _ in range(int(input())):
    n = int(input())
    lst = sorted(map(int, input().split()))
    print(lst[n//2])