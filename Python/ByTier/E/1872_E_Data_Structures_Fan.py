# Problem: CF 1872 E - Data Structures Fan
# https://codeforces.com/contest/1872/problem/E

"""
Algorithm: Efficient XOR query processing using prefix XOR and flipping tracking
Time Complexity: O(n + q) per test case, where n is array length and q is number of queries
Space Complexity: O(n) for prefix array and auxiliary variables

Approach:
1. Precompute prefix XOR of array elements for fast range XOR queries
2. Maintain running XOR of elements where s[i] == 0 (total0)
3. For type 1 queries (flip bits):
   - Calculate XOR of affected range using prefix XOR
   - Toggle the total0 value by XORing with this range XOR
4. For type 2 queries (XOR computation):
   - If g == 0, return total0 (XOR of elements where s[i] == 0)
   - If g == 1, return totalXor ^ total0 (XOR of elements where s[i] == 1)
"""

import sys


def main():
    data = sys.stdin.read().splitlines()
    t = int(data[0])
    index = 1
    output_lines = []
    for _ in range(t):
        n = int(data[index])
        index += 1
        a = list(map(int, data[index].split()))
        index += 1
        s = data[index].strip()
        index += 1
        q = int(data[index])
        index += 1
        # Precompute prefix XOR for range queries
        totalXor = 0
        for num in a:
            totalXor ^= num
        prefix = [0] * (n + 1)
        for i in range(1, n + 1):
            prefix[i] = prefix[i - 1] ^ a[i - 1]
        # Compute initial XOR of elements where s[i] == 0
        total0 = 0
        for i in range(n):
            if s[i] == "0":
                total0 ^= a[i]
        answers = []
        for _ in range(q):
            parts = data[index].split()
            index += 1
            if parts[0] == "1":
                # Type 1 query: flip s[l-1:r] (0-indexed)
                l = int(parts[1])
                r = int(parts[2])
                # Calculate XOR of range [l-1, r) using prefix XOR
                segXor = prefix[r] ^ prefix[l - 1]
                # Toggle total0: if the range had 0s, their xor will be flipped
                total0 ^= segXor
            else:
                # Type 2 query: return XOR of elements where s[i] == g
                g = int(parts[1])
                if g == 0:
                    # XOR of elements where s[i] == 0
                    answers.append(str(total0))
                else:
                    # XOR of elements where s[i] == 1 = totalXor XOR total0
                    answers.append(str(totalXor ^ total0))
        output_lines.append(" ".join(answers))
    for line in output_lines:
        print(line)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/