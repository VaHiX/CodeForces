# Problem: CF 2009 G1 - Yunli's Subarray Queries (easy version)
# https://codeforces.com/contest/2009/problem/G1

"""
Algorithm: Sliding window with frequency counting
Purpose: For each query range [l, l+k-1], calculate the minimum operations needed to make a consecutive subarray of length k in the array
Time Complexity: O(n + q)
Space Complexity: O(n)
"""

import sys


def main():
    data = sys.stdin.read().split()
    t = int(data[0])
    index = 1
    output_lines = []
    for _ in range(t):
        n = int(data[index])
        k = int(data[index + 1])
        q = int(data[index + 2])
        index += 3
        a = list(map(int, data[index : index + n]))
        index += n
        # Preprocess: Compute d[i] = a[i] - (i + 1) to identify sequences
        d = [a[i] - (i + 1) for i in range(n)]
        offset = n  # Offset to handle negative indices
        size_f = 2 * n + 10
        f = [0] * size_f  # frequency of each value in d
        size_ff = k + 10
        ff = [0] * size_ff  # frequency of frequencies
        max_freq = 0
        
        # If window size is larger than array, then no valid subarrays
        if n - k + 1 <= 0:
            ans_arr = []
        else:
            # Initialize the first window of size k
            for i in range(0, k):
                x_val = d[i] + offset  # Adjust index to be positive
                if x_val < 0 or x_val >= size_f:
                    old_freq = 0
                else:
                    old_freq = f[x_val]
                # Update frequency of old frequency
                if 1 <= old_freq < size_ff:
                    ff[old_freq] -= 1
                # Update new frequency value
                new_freq = old_freq + 1
                if 0 <= x_val < size_f:
                    f[x_val] = new_freq
                if 1 <= new_freq < size_ff:
                    ff[new_freq] += 1
                if new_freq > max_freq:
                    max_freq = new_freq
                    
            # Initialize result array
            ans_arr = [0] * (n - k + 1)
            ans_arr[0] = k - max_freq  # Minimum operations for first window

            # Slide the window from left to right
            for start in range(1, n - k + 1):
                # Remove the leftmost element from window
                x_remove = d[start - 1] + offset
                if x_remove < 0 or x_remove >= size_f:
                    old_freq_remove = 0
                else:
                    old_freq_remove = f[x_remove]
                if 1 <= old_freq_remove < size_ff:
                    ff[old_freq_remove] -= 1
                new_freq_remove = old_freq_remove - 1
                if 0 <= x_remove < size_f:
                    f[x_remove] = new_freq_remove
                if 1 <= new_freq_remove < size_ff:
                    ff[new_freq_remove] += 1
                # Update max frequency if necessary
                if old_freq_remove == max_freq:
                    if old_freq_remove < size_ff and ff[old_freq_remove] == 0:
                        max_freq = old_freq_remove - 1
                        
                # Add the new element on the right
                i_new = start + k - 1
                x_add = d[i_new] + offset
                if x_add < 0 or x_add >= size_f:
                    old_freq_add = 0
                else:
                    old_freq_add = f[x_add]
                if 1 <= old_freq_add < size_ff:
                    ff[old_freq_add] -= 1
                new_freq_add = old_freq_add + 1
                if 0 <= x_add < size_f:
                    f[x_add] = new_freq_add
                if 1 <= new_freq_add < size_ff:
                    ff[new_freq_add] += 1
                if new_freq_add > max_freq:
                    max_freq = new_freq_add
                    
                ans_arr[start] = k - max_freq  # Store minimum operations for this window
                
        # Process queries
        for i in range(q):
            l = int(data[index])  # Start index (1-based)
            r = int(data[index + 1])  # End index (1-based) - guaranteed to match l+k-1
            index += 2
            if n - k + 1 == 0:
                output_lines.append("0")
            else:
                if l - 1 < len(ans_arr):
                    output_lines.append(str(ans_arr[l - 1]))  # Convert to 0-based indexing
                else:
                    output_lines.append("0")
                    
    sys.stdout.write("\n".join(output_lines))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/