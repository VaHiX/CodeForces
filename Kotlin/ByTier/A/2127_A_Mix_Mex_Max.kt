// Problem: CF 2127 A - Mix Mex Max
// https://codeforces.com/contest/2127/problem/A

/**
 * Problem: A. Mix Mex Max
 * 
 * Task: Determine if an array can be made "good" by replacing -1s with non-negative integers.
 * An array is "good" if for every triplet of consecutive elements:
 * mex([a[i], a[i+1], a[i+2]]) = max([a[i], a[i+1], a[i+2]]) - min([a[i], a[i+1], a[i+2]])
 * 
 * Algorithm:
 * - For each test case, we process the array and check conditions.
 * - If any element is 0, it's impossible to make the array good (since MEX of a set containing 0 will not be 0).
 * - We filter out -1s and check if remaining elements form a valid pattern:
 *   - If result set has size 1, answer is YES.
 *   - Else NO.
 *
 * Time Complexity: O(n) per test case, where n is the length of array.
 * Space Complexity: O(n) for storing arrays and sets.
 */
fun main() {
    val t = readLine()!!.toInt() // Read number of test cases
    repeat(t) {
        val n = readLine()!!.toInt() // Read size of array
        val a = readLine()!!.split(' ').map { it.toInt() } // Read array elements
        
        if (a.any { it == 0 }) {
            println("NO") // If any element is zero, cannot be good due to MEX constraints
        } else {
            val b = a.filter { it != -1 } // Remove all -1s
            
            if (b.isEmpty()) {
                println("YES") // All elements were -1, so we can assign same value everywhere
            } else {
                val c = b.toSet() // Get unique values from non -1 elements
                
                if (c.size == 1) {
                    println("YES") // All non -1 elements are same -> valid pattern
                } else {
                    println("NO") // Non uniform values -> invalid
                }
            }
        }
    }
}


// https://github.com/VaHiX/CodeForces/