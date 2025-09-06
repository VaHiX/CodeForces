# Contest 923, Problem A: Primal Sport
# URL: https://codeforces.com/contest/923/problem/A

def sieve(MAX):
    sieve = [1] * MAX
    for i in range(2, MAX):
        if sieve[i] != 1:
            continue
        for j in range(2 * i, MAX, i):
            sieve[j] = i
    return sieve


def main():
    MAX = int(1e6)
    N = MAX + 1
    primes = sieve(N)

    x2 = int(input())

    max_p = primes[x2]

    result = float('inf')
    for x1 in range(x2 - max_p + 1, x2 + 1):
        if primes[x1] == x1:
            result = min(result, x1)
            continue
        max_p = primes[x1]
        t = x1 - max_p + 1
        result = min(result, t)

    print(result)


main()
