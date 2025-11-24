// Problem: CF 2112 B - Shrinking Array
// https://codeforces.com/contest/2112/problem/B

/*
B. Shrinking Array

Purpose:
This code solves the problem of finding the minimum number of operations to make an array "beautiful".
An array is beautiful if it has at least two elements and there exists a position i such that 
|b_i - b_{i+1}| <= 1.

The algorithm works as follows:
- If the array already satisfies the condition, return 0.
- Otherwise, check whether there's a mix of increasing and decreasing adjacent elements.
- If both increase and decrease exist, one operation suffices to make it beautiful.
- If neither increase nor decrease is present (i.e., the array is monotonic), it's impossible to make it beautiful.

Algorithms/Techniques:
- Simulation with condition checking
- Greedy approach for determining if transformation is possible

Time Complexity: O(n) where n is the size of the array (single pass through elements)
Space Complexity: O(n) due to input array storage and temporary variables

Input Format:
- First line: number of test cases t
- For each test case:
  - First line: array size n
  - Second line: n integers representing the array

Output Format:
- For each test case, output minimum operations required or -1 if impossible
*/

fun main() {
    val t = readln().toInt() // Read number of test cases
    repeat(t) {
        val n = readln().toInt() // Read size of array
        val a = readln().split(" ").map { it.toInt() } // Read and parse the array elements
        var increase = false // Flag to track if there's an increasing adjacent pair
        var decrease = false // Flag to track if there's a decreasing adjacent pair
        
        for (i in 1 until n) {
            if (Math.abs(a[i] - a[i - 1]) <= 1) { // If the difference is at most 1
                println(0) // Array is already beautiful
                return@repeat // Exit current test case
            }
            if (a[i] > a[i - 1]) { // If current element is greater than previous
                increase = true
            } else if (a[i] < a[i - 1]) { // If current element is less than previous
                decrease = true
            }
        }
        
        if (increase && decrease) { // If both increasing and decreasing pairs exist
            println(1) // One operation is enough to make it beautiful
        } else {
            println(-1) // Impossible to make array beautiful
        }
    }
}


// https://github.com/VaHiX/CodeForces/