// Problem: CF 2110 F - Faculty
// https://codeforces.com/contest/2110/problem/F

/**
 * Problem: Faculty
 * Purpose: Calculate the "beauty" of prefixes of an array, where beauty is defined as the maximum
 *          value of f(x, y) = (x mod y) + (y mod x) over all pairs in the prefix.
 *
 * Algorithm:
 * - For each element in the input array, maintain a list of previously seen elements.
 * - Keep track of the current maximum element seen so far.
 * - When processing a new element:
 *   - If it's greater than current max, update max and compute answer using previous elements.
 *   - If it's less than current max, compute with max directly.
 *   - Add the new element to the list.
 *
 * Time Complexity: O(n^2) in worst case due to nested loop when updating answer,
 *                  but optimized by only checking pairs when a new maximum is found.
 * Space Complexity: O(n) for storing the list of elements.
 */
import java.io.BufferedReader
import java.io.InputStreamReader
import java.util.StringTokenizer
import kotlin.math.max

fun main() {
    val jin = BufferedReader(InputStreamReader(System.`in`))
    val out = StringBuilder()
    repeat(jin.readLine().toInt()) {
        val n = jin.readLine().toInt()
        val tokenizer = StringTokenizer(jin.readLine())
        val xs = mutableListOf<Int>() // Stores previously seen numbers
        var currMax = 0 // Tracks current maximum in the prefix
        var answer = 0 // Stores the beauty of current prefix
        repeat(n) {
            val x = tokenizer.nextToken().toInt()
            if (x > currMax) { // If new element is greater than current max
                if (2 * currMax > x) {
                    // If 2 * prev_max > x, then x mod prev_max gives x,
                    // so answer is just x since x mod x = 0.
                    answer = x
                } else {
                    // Otherwise compute with all previous elements
                    for (y in xs) {
                        answer = max(answer, y + (x % y))
                    }
                }
                currMax = x // Update current maximum
            } else if (x < currMax) { // If new element is less than current max
                // Compute f(x, currMax) = x + (currMax mod x)
                answer = max(answer, x + (currMax % x))
            }
            xs.add(x) // Add the current element to list of seen elements
            out.append(answer).append(' ')
        }
        out.appendLine()
    }
    print(out)
}


// https://github.com/VaHiX/CodeForces/