// Problem: CF 2149 A - Be Positive
// https://codeforces.com/contest/2149/problem/A

/*
 * Problem: A. Be Positive
 * Task: Make the product of all elements in the array strictly positive with minimum operations.
 * Algorithm/Techniques: 
 *   - Count zeros and negative ones (-1) in the array.
 *   - If there are zeros, they need to be converted to 1 (cost = count of zeros).
 *   - If there's an odd number of -1s, we must flip one of them to make product positive,
 *     which costs 2 operations (convert -1 to 1).
 * 
 * Time Complexity: O(n) per test case, where n is the length of the array.
 * Space Complexity: O(n) for storing input data and result.
 */

fun main() {
    val input = generateSequence { readLine() }.toList()
    val t = input[0].toInt()  // Number of test cases
    var line = 1
    val result = StringBuilder()
    repeat(t) {
        val n = input[line++].toInt()  // Length of the array
        val arr = input[line++].split(" ").map { it.toInt() }  // Read the array elements
        val zeros = arr.count { it == 0 }  // Count number of zeros
        val neg = arr.count { it == -1 }  // Count number of -1s
        
        // If odd number of -1s, we need to perform 2 operations on one -1 to make product positive
        val ans = zeros + if (neg % 2 == 1) 2 else 0
        result.append(ans).append("\n")
    }
    print(result.toString())
}


// https://github.com/VaHiX/CodeForces/