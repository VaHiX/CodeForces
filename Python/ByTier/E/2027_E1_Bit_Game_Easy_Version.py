# Contest 2027, Problem E1: Bit Game (Easy Version)
# URL: https://codeforces.com/contest/2027/problem/E1


def nimber(x: int, a: int) -> int:
    aprime = 0
    goodbit = False
    for bit in range(30, -1, -1):
        if x & (1 << bit):
            aprime *= 2
            if goodbit or (a & (1 << bit)):
                aprime += 1
        elif a & (1 << bit):
            goodbit = True
    # g(2^k - 2) = 0, for all k >= 1.
    for k in range(1, 31):
        if aprime == (1 << k) - 2:
            return 0
    # g(2^k - 1) = k, for all k >= 1.
    for k in range(1, 31):
        if aprime == (1 << k) - 1:
            return k
    # g(2^k) = k + (-1)^k, for all k >= 0.
    for k in range(1, 31):
        if aprime == (1 << k):
            return k - 1 if k % 2 else k + 1
    # g(2^k+1) = g(2^k+2) = ... = g(2^{k+1} - 3) = k + 1, for all k >= 2.
    for k in range(2, 31):
        if (1 << k) < aprime <= (2 << k) - 3:
            return k + 1
    # should never get to this point
    assert False
    return -1


def solve():
    import sys

    input = sys.stdin.read
    data = input().split()
    idx = 0
    t = int(data[idx])
    idx += 1
    results = []
    for _ in range(t):
        n = int(data[idx])
        idx += 1
        A = list(map(int, data[idx : idx + n]))
        idx += n
        X = list(map(int, data[idx : idx + n]))
        idx += n
        curr = 0
        for i in range(n):
            curr ^= nimber(X[i], A[i])
        results.append("Alice" if curr else "Bob")
    print("\n".join(results))


if __name__ == "__main__":
    solve()
