# Problem: CF 2168 C - Intercepting Butterflies
# https://codeforces.com/contest/2168/problem/C

"""
Code Purpose:
This code solves the "Intercepting Butterflies" problem where Alice and Bob must communicate
a secret integer x (1 ≤ x ≤ 2^15) such that Bob can recover x even if a butterfly modifies
the transmitted set S by adding or removing one element.

Algorithm:
The solution uses error-correcting codes based on XOR operations and parity checks:
1. Alice encodes the 15-bit value x into a 20-bit codeword using:
   - First 15 bits: the binary representation of x (x-1 due to 0 indexing)
   - Next 4 bits: XOR of positions where the first 15 bits are 1 (to detect single bit errors)
   - Final bit: parity check (even or odd number of 1s in the previous 4 bits)
2. Bob receives a set S' which may have been modified due to butterfly interference
3. Bob decodes by:
   - Reconstructing the received bits
   - Detecting errors using XOR of positions
   - Correcting single bit errors using parity checks
   - Recovering the original x

Time Complexity: O(1) per test case - constant time operations
Space Complexity: O(1) - only uses fixed-size arrays of 20 elements each
"""

import os
import sys


def main():
    if inp() == "first":
        run_first()
    else:
        run_second()


def run_first():
    for _ in range(read_int()):
        x = read_int()
        x -= 1  # Convert to 0-indexed

        # Convert x to 15-bit binary string
        S = f"{x :015b}"
        p = 0
        # Compute XOR of positions where bits are 1 in S
        for i in range(15):
            if S[i] == "1":
                p ^= i + 1

        # Convert p to 4-bit binary
        P = f"{p :04b}"

        q = 0
        # Count number of 1s in P
        for i in range(4):
            if P[i] == "1":
                q += 1

        # Even parity check (number of 1s in P is even)
        Q = str(q % 2)

        # Concatenate all parts to form 20-bit codeword
        T = "".join([S, P, Q])
        assert len(T) == 20

        # Create set S from positions of 1s in T
        ans = []
        for i in range(20):
            if T[i] == "1":
                ans.append(i + 1)

        print(len(ans))
        print(*ans)


def run_second():
    for _ in range(read_int()):
        read_int()
        A = read_ints()

        # Reconstruct bits from received set
        T = [0] * 20
        for a in A:
            T[a - 1] = 1

        print(solve(T[:15], T[15:19], T[19]))


def solve(S, P, q):
    # Compute XOR of positions where S bits are 1
    sp = 0
    for i in range(15):
        if S[i]:
            sp ^= i + 1

    # Convert P to integer
    pp = 0
    for i in range(4):
        pp <<= 1
        pp += P[i]

    # If S and P don't match, there's an error
    if sp != pp:
        # Find error position
        x = sp ^ pp
        # If error position is valid (between 1 and 15)
        if x.bit_count() >= 2:
            # Correct bit in S at position x
            S[x - 1] ^= 1
        else:
            # Use parity check to correct error
            pc = sum(P)
            if pc % 2 == q:
                S[x - 1] ^= 1

    # Convert back to original number
    ans = 0
    for i in range(15):
        ans <<= 1
        ans += S[i]

    ans += 1  # Convert back to 1-indexed
    return ans


DEBUG = "DEBUG" in os.environ


def inp():
    return sys.stdin.readline().rstrip()


def read_int():
    return int(inp())


def read_ints():
    return [int(e) for e in inp().split()]


def list2d(d1, d2, init=None):
    return [[init] * d2 for _ in range(d1)]


def list3d(d1, d2, d3, init=None):
    return [[[init] * d3 for _ in range(d2)] for _ in range(d1)]


def list4d(d1, d2, d3, d4, init=None):
    return [[[[init] * d4 for _ in range(d3)] for _ in range(d2)] for _ in range(d1)]


def debug(fmt, *args):
    if DEBUG:
        if args:
            print(fmt.format(*args), file=sys.stderr)
        else:
            print(fmt, file=sys.stderr)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/