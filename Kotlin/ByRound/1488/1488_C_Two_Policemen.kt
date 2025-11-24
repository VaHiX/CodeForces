// Problem: CF 1488 C - Two Policemen
// https://codeforces.com/contest/1488/problem/C

/**
 * Problem: C. Two Policemen
 * 
 * Purpose: Given a street of length n, two policemen at positions x and y,
 *          find the minimum time (in minutes) for both policemen to cover
 *          all points of the street. Each minute, each policeman can move
 *          left, right, or stay in place.
 * 
 * Approach: 
 *   - Try all possible positions between the two policemen (from x to y-1)
 *   - For each position i, compute the time needed for both policemen to
 *     cover the entire street by placing one at i, and the other at either x or y
 *   - Minimize over all positions to get the answer.
 * 
 * Time Complexity: O(n) per test case in worst case, but since sum of n <= 1e6,
 *                   overall complexity is acceptable.
 * Space Complexity: O(1)
 */
import java.io.BufferedReader
import java.io.InputStreamReader
import java.util.StringTokenizer
import kotlin.math.max
import kotlin.math.min

private class FastScanner {
  private val br = BufferedReader(InputStreamReader(System.`in`))
  private var st: StringTokenizer? = null
  fun nextInt(): Int {
    while (st == null || !st!!.hasMoreElements()) {
      st = StringTokenizer(br.readLine())
    }
    return st!!.nextToken().toInt()
  }
}

fun main() {
  val fs = FastScanner()
  val t = fs.nextInt()
  val out = StringBuilder()
  
  repeat(t) {
    var n = fs.nextInt()
    var x = fs.nextInt()
    var y = fs.nextInt()
    
    // Ensure x <= y to simplify logic
    if (x > y) {
      val tmp = x
      x = y
      y = tmp
    }
    
    // Initialize answer with a large value
    var ans = 1_000_000_000L
    
    // Try all positions between x and y (exclusive)
    for (i in x until y) {
      // Compute gap and boundary for the left side (before position i)
      val leftGap = i - x        // Number of steps needed to reach i from x
      val leftBound = x - 1      // Distance from x to leftmost point
      
      // Compute gap and boundary for the right side (after position i)
      val rightGap = y - i - 1   // Number of steps needed to reach i from y
      val rightBound = n - y     // Distance from y to rightmost point
      
      // Calculate minimum time to cover the left part:
      // - Move towards gap, then move towards boundary
      // - Cost = min(gap, bound) * 2 (since we can use 2 moves per step for coverage)
      // - Plus max(gap, bound) to ensure all is covered
      val left = (min(leftGap, leftBound) * 2L) + max(leftGap, leftBound)
      
      // Same for the right part
      val right = (min(rightGap, rightBound) * 2L) + max(rightGap, rightBound)
      
      // Answer is the maximum of left and right (both parts must be fully covered)
      ans = min(ans, max(left, right))
    }
    
    out.append(ans).append('\n')
  }
  print(out.toString())
}


// https://github.com/VaHiX/CodeForces/