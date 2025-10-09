# Problem: CF 2027 E1 - Bit Game (Easy Version)
# https://codeforces.com/contest/2027/problem/E1

"""
E1. Bit Game (Easy Version)

This problem involves a game played on n piles of stones where each pile has a value a_i and current number of stones x_i.
Players take turns removing d stones from pile i if:
1. 1 <= d <= a_i
2. x_i & d == d (i.e., d is a subset of x_i in terms of bit representation)

The game uses the Sprague-Grundy theorem to compute the nimber of each pile.

Algorithm:
- For each pile, calculate its nimber using the helper function 'nimber'.
- The overall game nimber is XOR of all nimbers.
- If total nimber == 0, Bob wins; otherwise Alice wins.

Time Complexity: O(n * log(max(a_i))) per test case due to bit operations
Space Complexity: O(1) extra space excluding input storage

"""
def nimber(x: int, a: int) -> int:
    aprime = 0
    goodbit = False
    # Process bits from high to low (30 down to 0)
    for bit in range(30, -1, -1):
        if x & (1 << bit):
            # If current bit in x is set, double aprime and consider adding 1 if necessary
            aprime *= 2
            if goodbit or (a & (1 << bit)):
                # Add one to aprime if either we've already seen a 'good' bit,
                # or current bit in a is also set
                aprime += 1
        elif a & (1 << bit):
            # If x has zero at this bit but a has one, this creates a 'goodbit'
            goodbit = True
    # Check if aprime equals special patterns for nimber calculation
    for k in range(1, 31):
        if aprime == (1 << k) - 2:
            return 0
    for k in range(1, 31):
        if aprime == (1 << k) - 1:
            return k
    for k in range(1, 31):
        if aprime == (1 << k):
            return k - 1 if k % 2 else k + 1
    for k in range(2, 31):
        if (1 << k) < aprime <= (2 << k) - 3:
            return k + 1
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
        # Compute XOR of all nimbers for each pile
        for i in range(n):
            curr ^= nimber(X[i], A[i])
        # Determine winner based on overall game state (if XOR is zero, Bob wins)
        results.append("Alice" if curr else "Bob")
    print("\n".join(results))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/codeForces/