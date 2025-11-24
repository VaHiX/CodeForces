# Problem: CF 1698 G - Long Binary String
# https://codeforces.com/contest/1698/problem/G

"""
Algorithm: 
This problem involves finding the lexicographically largest binary string t of length 10^100 that has exactly two 1-bits after a series of operations on an initially all-zero string. Each operation allows selecting a substring and XORing it with string s.

Key Insights:
1. We can think of the problem in terms of a finite field (GF(2)) and linear algebra.
2. Operations are equivalent to adding vectors (represented as integers in binary form).
3. The final state has exactly two 1s, which corresponds to adding two vectors (or operations) such that their XOR leads to exactly two 1s.
4. To maximize lexicographically, we want the leftmost 1 to occur as late as possible.
5. The solution uses a "meet-in-the-middle" approach for finding a combination of operations that results in exactly two 1s in the binary representation.

Time Complexity:
- O(B * n) where B = 2^(n/2 + 1) and n = length of reduced pattern s.
- The search phase and lookup phase in the dictionary.

Space Complexity:
- O(B) for storing the dictionary of intermediate results, where B = 2^(n/2 + 1).

Techniques:
- Bit manipulation and finite field arithmetic (XOR).
- Meet-in-the-middle technique to reduce time complexity for finding combinations.

"""

def main():
    import sys

    s = sys.stdin.readline().strip()
    n = len(s)

    # Skip leading zeros
    j = 0
    while j < n and s[j] == "0":
        j += 1
    if j == n:
        print(-1)
        return

    # Remove trailing zeros
    s_prime = s[j:]
    while s_prime and s_prime[-1] == "0":
        s_prime = s_prime[:-1]
    n_prime = len(s_prime)
    if n_prime == 0:
        print(-1)
        return

    # Convert s_prime to integer (bit representation)
    V = 0
    for i in range(n_prime):
        V |= int(s_prime[i]) << i
    m = bin(V).count("1")

    # If V is a power of two, it means the result is simply two consecutive bits
    if m == 1:
        print(f"{j +1 } {j +2 }")
        return

    # Helper function for multiplication in finite field
    def mul(a, b, S, H):
        c = 0
        # Multiply two integers in GF(2)
        for i in range(70):
            if (a >> i) & 1:
                c ^= b << i
        # Reduce modulo the polynomial S
        for i in range(69, H - 1, -1):
            if (c >> i) & 1:
                c ^= S << (i - H)
        return c

    # Parameters for meet-in-the-middle
    S = V
    H = n_prime - 1
    T = S & ~1      # Initialize T to S with the lowest bit removed
    O = 1 << 1      # O = 2, used for shifting (x^1)
    B = 1 << (n_prime // 2 + 1)   # Half size of the search space

    # Build dictionary of left-side results (first B operations)
    M = {}
    T = 1
    for b in range(B):
        M[T] = b
        T = mul(T, O, S, H)
    
    # Initialize right side
    T = 1
    for b in range(B):
        T = mul(T, O, S, H)
    P = T
    
    # Search for a combination that produces two 1s (i.e., a power of 2)
    i = 1
    while True:
        if P in M:
            # Found a valid pair
            print(f"{j +1 } {j +i *B -M [P ]+1 }")
            break
        P = mul(P, T, S, H)
        i += 1


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/