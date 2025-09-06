# Contest 2070, Problem A: FizzBuzz Remixed
# URL: https://codeforces.com/contest/2070/problem/A

for n in [*open(0)][1:]:
    n = int(n) + 1
    print(n // 15 * 3 + min(3, n % 15))
