# Contest 689, Problem A: Mike and Cellphone
# URL: https://codeforces.com/contest/689/problem/A

n = int(input())
number = (input())
number = str(number)


a = [0] * 10
for i in number:
    l = int(i)
    a[l] += 1


horizontal = a[0] != 0 or (a[1] != 0 or a[4] != 0 or a[7] != 0) and (a[3] != 0 or a[6] != 0 or a[9] != 0)
vertical = (a[1] != 0 or a[2] != 0 or a[3] != 0) and (a[7] != 0 or a[0] != 0 or a[9] != 0)


if horizontal and vertical:
    print('YES')
else:
    print('NO')