# Contest 2037, Problem B: Intercepted Inputs
# URL: https://codeforces.com/contest/2037/problem/B

for s in [*open(0)][2::2]:
    n = len(a := s.split()) - 2
    s = {*a}
    i = 1
    while n % i or {str(i), str(n // i)} - s:
        i += 1
    print(i, n // i)
