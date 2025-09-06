# Contest 2068, Problem A: Condorcet Elections
# URL: https://codeforces.com/contest/2068/problem/A

n, m = map(int, input().split())
print("YES")
print(2 * m)
for i in range(m):
    a, b = map(int, input().split())
    str1 = str(a) + " " + str(b)
    str2 = ""
    for j in range(1, n + 1):
        if j == a or j == b:
            continue
        str2 = str(j) + " " + str2
        str1 += " " + str(j)
    print(str1)
    print(str2 + str(a) + " " + str(b))
