# Contest 1453, Problem A: Cancel the Trains
# URL: https://codeforces.com/contest/1453/problem/A

for _ in range(int(input())):
    input()
    a = set(map(int, input().split()))
    print(sum(int(x) in a for x in input().split()))
