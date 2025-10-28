// Problem: CF 2087 E - Color the Arrows
// https://codeforces.com/contest/2087/problem/E

/**
 * Problem: E. Color the Arrows
 * 
 * Algorithm: Dynamic Programming with Directional Processing
 * 
 * Time Complexity: O(n) - Each element is processed a constant number of times
 * Space Complexity: O(n) - For storing the input arrays and intermediate results
 * 
 * Approach:
 * - For each arrow, we process from left to right and right to left
 * - For each direction, we compute prefix sums of rewards, but only consider 
 *   positive rewards to maximize the score
 * - For each arrow, we check if it points left or right, and if it's a left-pointing
 *   arrow, we can extend from the right, otherwise from the left
 * - This allows us to handle the constraint that we can only select an arrow 
 *   that points in the direction of our previous selection
 * 
 * The solution uses two passes:
 * 1. Left to right: process all right-pointing arrows
 * 2. Right to left: process all left-pointing arrows
 * 
 * We merge the results from both passes to find the maximum score.
 */

fun mainE() {
  repeat(readln().toInt()) {
    val n = readln().toInt()
    val orig_s = readln().map { it == '>' } // true if arrow points right, false if left
    val orig_c = readln().split(" ").map { it.toInt() }
    var ans: Long = 0 // Initialize the answer to zero
    
    // Process both directions:
    // First, process from left to right (considering right-pointing arrows)
    listOf(orig_s.zip(orig_c), orig_s.map { !it }.zip(orig_c).reversed()).forEach {
      var cur: Long = 0 // Current running sum
      it.forEach {
        if (!it.first) { // If arrow points left
          // Update answer with current sum plus the reward of this arrow
          ans = maxOf(ans, cur + it.second)
        }
        // Add the reward (but only if positive, to maximize the prefix sum)
        cur += maxOf(it.second, 0)
      }
    }
    println(ans)
  }
}

fun main() {
  mainE()
}


// https://github.com/VaHiX/CodeForces/