# Contest 2095, Problem F: ⅓ оf а Рrоblеm
# URL: https://codeforces.com/contest/2095/problem/F

a, b = map(int, input().split())
print(12 * a + abs(a - b) + (15 * a - 3 * b) * b + 2)
