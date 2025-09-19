# Contest 953, Problem A: 2-3-numbers
# URL: https://codeforces.com/contest/953/problem/A

stroka = input().split()
l = int(stroka[0])
r = int(stroka[1])
counter = 0
for x in range(35):
    for y in range(22):
        if l <= 2**x * 3**y <= r:
            counter += 1
print(counter)
