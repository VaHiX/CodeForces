# Contest 255, Problem A: Greg's Workout
# URL: https://codeforces.com/contest/255/problem/A

int(input())
a = [int(k) for k in input().split()]
b = {sum(a[0::3]): "chest", sum(a[1::3]): "biceps", sum(a[2::3]): "back"}
print(b[max(b)])
