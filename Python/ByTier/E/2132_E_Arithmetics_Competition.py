"""
Problem: CF2132E - Arithmetics Competition

This program solves a problem where we need to find the maximum sum of elements
from two arrays A and B, selecting exactly K elements in total, with constraints
on the number of elements that can be selected from each array.

Approach:
1. Sort both arrays in descending order
2. Precompute prefix sums for both arrays
3. For each query, use binary search to find the optimal split between the two arrays
   that maximizes the sum while satisfying the constraints

Time Complexity:
   - Sorting: O(N log N + M log M)
   - Prefix sum: O(N + M)
   - Per query: O(log K) with binary search
   - Overall: O(Q log K + (N + M) log (N + M))

Space Complexity: O(N + M) for storing prefix sums
"""

import sys
from itertools import accumulate

def main():
    # Read all input at once for efficiency
    input = sys.stdin.read
    data = input().split()
    idx = 0
    
    # Number of test cases
    num_test_cases = int(data[idx])
    idx += 1
    
    for _ in range(num_test_cases):
        # Read array sizes and number of queries
        size_a, size_b, num_queries = map(int, data[idx:idx+3])
        idx += 3
        
        # Read and sort arrays in descending order
        array_a = list(map(int, data[idx:idx+size_a]))
        idx += size_a
        array_b = list(map(int, data[idx:idx+size_b]))
        idx += size_b
        
        array_a.sort(reverse=True)
        array_b.sort(reverse=True)
        
        # Compute prefix sums
        prefix_a = [0] + list(accumulate(array_a))
        prefix_b = [0] + list(accumulate(array_b))
        
        # Process each query
        for __ in range(num_queries):
            # Query parameters
            max_from_a, max_from_b, total_elements = map(int, data[idx:idx+3])
            idx += 3
            
            # Binary search to find optimal split
            left = max(0, total_elements - max_from_b)  # Minimum elements from A
            right = min(max_from_a, total_elements)     # Maximum elements from A
            best_sum = 0
            
            # Binary search to find the maximum sum
            while left <= right:
                mid = (left + right) // 2
                current_sum = prefix_a[mid] + prefix_b[total_elements - mid]
                next_sum = 0
                
                # Check if we can get a better sum by moving the split
                if mid < right:
                    next_sum = prefix_a[mid + 1] + prefix_b[total_elements - mid - 1]
                
                if current_sum < next_sum:
                    left = mid + 1
                    best_sum = max(best_sum, next_sum)
                else:
                    right = mid - 1
                    best_sum = max(best_sum, current_sum)
            
            print(best_sum)

if __name__ == "__main__":
    main()
