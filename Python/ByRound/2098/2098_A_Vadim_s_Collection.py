# Contest 2098, Problem A: Vadim's Collection
# URL: https://codeforces.com/contest/2098/problem/A

for _ in range(int(input())):
    s = input()
    l = [int(i) for i in s]
    for i in range(10):
        for j in range(i + 1, 10):
            if l[j] >= 10 - i - 1 and l[j] < l[i]:
                l[j], l[i] = l[i], l[j]
    print("".join([str(i) for i in l]))
