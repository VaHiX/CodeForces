"""
Problem: CF2131C - Make it Equal

This program determines if two arrays can be made equal by performing operations
where each element can be increased or decreased by k any number of times.

Approach:
1. For each test case, read n (array length) and k (modulo value)
2. For each element in both arrays, calculate the minimum number of operations needed
   to make it congruent to 0 modulo k (either by adding or subtracting multiples of k)
3. Sort both arrays of remainders
4. If the sorted arrays are identical, print "YES", otherwise print "NO"

Time Complexity: O(n log n) per test case (due to sorting)
Space Complexity: O(n) for storing the arrays
"""

def read_ints():
    """Read a line of integers from input."""
    return list(map(int, input().split()))

def can_make_equal(n, k, a, b):
    """
    Check if two arrays can be made equal by adding/subtracting multiples of k.
    
    Args:
        n: Number of elements in each array
        k: The modulo value for operations
        a: First array of integers
        b: Second array of integers
        
    Returns:
        bool: True if arrays can be made equal, False otherwise
    """
    # Calculate remainders for first array
    remainders_a = [min(x % k, k - x % k) for x in a]
    # Calculate remainders for second array
    remainders_b = [min(x % k, k - x % k) for x in b]
    
    # Compare sorted remainders
    return sorted(remainders_a) == sorted(remainders_b)

def main():
    # Read number of test cases
    test_cases = int(input())
    
    for _ in range(test_cases):
        # Read input for each test case
        n, k = map(int, input().split())
        a = list(map(int, input().split()))
        b = list(map(int, input().split()))
        
        # Check if arrays can be made equal and print result
        if can_make_equal(n, k, a, b):
            print("YES")
        else:
            print("NO")

if __name__ == "__main__":
    main()
