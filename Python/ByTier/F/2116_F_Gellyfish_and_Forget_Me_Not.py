# Problem: CF 2116 F - Gellyfish and Forget-Me-Not
# https://codeforces.com/contest/2116/problem/F

"""
F. Gellyfish and Forget-Me-Not

This problem involves a two-player game where players take turns XOR-ing values from arrays 'a' and 'b', 
with the goal for one player to minimize and the other to maximize the final XOR value x.

The solution uses a greedy approach with a basis vector (similar to Gaussian elimination over GF(2)) 
to track linearly independent XOR combinations. At each turn, the active player (based on c[i]) chooses 
either a[i] or b[i] if it increases the rank of the basis or allows for optimal strategy.

Time Complexity: O(n * log(max_value)) where n is number of elements and max_value ~ 2^60
Space Complexity: O(log(max_value)) for storing the basis vector

Algorithms/Techniques:
- Greedy algorithm with basis representation (linear algebra over GF(2))
- XOR manipulation and bit manipulation techniques
"""

import sys


def main():
    data = sys.stdin.read().splitlines()
    t = int(data[0].strip())
    index = 1
    results = []
    for _ in range(t):
        n = int(data[index].strip())
        index += 1
        a_list = list(map(int, data[index].split()))
        index += 1
        b_list = list(map(int, data[index].split()))
        index += 1
        c_str = data[index].strip()
        index += 1
        
        # Get XOR of all 'a' values as base
        total_a = 0
        for a_val in a_list:
            total_a ^= a_val
            
        # Compute differences between a and b at each position
        d_list = [a_list[i] ^ b_list[i] for i in range(n)]
        
        # Basis array to maintain linearly independent XOR combinations
        basis_arr = [0] * 60
        ans = total_a  # Start with total XOR of 'a' values
        
        # Process from right to left (most significant to least significant round)
        for i in range(n - 1, -1, -1):
            temp = d_list[i]
            if temp == 0:
                continue
                
            # Reduce temp to find highest bit
            for bit_index in range(59, -1, -1):
                if (temp >> bit_index) & 1:
                    if basis_arr[bit_index] != 0:
                        temp ^= basis_arr[bit_index]
                        
            # If temp is not zero, add it to basis
            if temp != 0:
                high_bit_index = temp.bit_length() - 1
                basis_arr[high_bit_index] = temp
                high_bit_val = 1 << high_bit_index
                
                # If c[i] == '0', then Gellyfish (minimizer) plays; else Flower (maximizer)
                if c_str[i] == "0":
                    # For Gellyfish: if current bit is set in ans, we XOR with temp to decrease
                    if ans & high_bit_val:
                        ans ^= temp
                else:
                    # For Flower: if the bit is not set, we XOR with temp to increase
                    if not (ans & high_bit_val):
                        ans ^= temp
                        
        results.append(str(ans))
    sys.stdout.write("\n".join(results))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/codeForces/