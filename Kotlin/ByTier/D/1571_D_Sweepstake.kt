// Problem: CF 1571 D - Sweepstake
// https://codeforces.com/contest/1571/problem/D

/**
 * Problem: Sweepstake
 * 
 * Purpose: 
 *   Given n programmers and m spectators' guesses about who will take 1st and last place,
 *   determine the worst possible rank for the first spectator (you).
 *   Ranking is based on number of correct guesses:
 *   - c2: spectators who guessed both correctly → rank 1
 *   - c1: spectators who guessed one correctly → rank c2 + 1
 *   - c0: spectators who guessed none correctly → rank c2 + c1 + 1
 * 
 * Approach:
 *   Enumerate all possible true first and last place winners (i, j) where i != j.
 *   For each such pair:
 *     - Count how many spectators guessed both correctly (full).
 *     - Compute how many guessed exactly one (first or second only).
 *     - Calculate the rank of the first spectator based on the best-case scenario for others.
 *   The worst rank is the maximum among all possible true rankings.
 * 
 * Time Complexity: O(n^2 * m) in worst case due to nested loop over all (i,j) pairs
 * Space Complexity: O(n^2 + n) for storing counts, so O(n^2)
 */

import java.util.*
import kotlin.math.max

private fun IN(): Int {
  var num = 0
  var c = System.`in`.read().toChar()
  var f = false
  while (c != '-' && (c < '0' || c > '9')) c = System.`in`.read().toChar()
  if (c == '-') {
    f = true
    c = System.`in`.read().toChar()
  }
  while (c >= '0' && c <= '9') {
    num = num * 10 + (c - '0')
    c = System.`in`.read().toChar()
  }
  return if (f) -num else num
}

const val N = 10002010
val cntsFull = IntArray(N) // count of spectators who guessed (f, l) exactly
val cntsFirst = IntArray(1010) // count of spectators who guessed first place f
val cntsSecond = IntArray(1010) // count of spectators who guessed last place l

fun sol() {
  val n = IN()
  val m = IN()
  
  // Initialize arrays
  for (i in 1..n) {
    cntsFirst[i] = 0
    cntsSecond[i] = 0
  }
  for (i in 1..(n + 1) * (n + 1)) cntsFull[i] = 0

  var f: Int
  var l: Int
  var f1 = 0 // first guess of first spectator (you)
  var l1 = 0 // last guess of first spectator (you)
  
  // Read all spectators' guesses and update counts
  for (i in 1..m) {
    f = IN()
    l = IN()
    if (i == 1) {
      f1 = f
      l1 = l
    }
    cntsFirst[f]++       // increment counter for guessed first place
    cntsSecond[l]++      // increment counter for guessed last place
    cntsFull[f * (n + 1) + l]++ // increment counter for specific pair
  }

  var ans = 1
  // Check all possible true rankings (i, j) where i is first, j is last
  for (i in 1..n) {
    for (j in 1..n) {
      if (i == j) continue // skip if same person
      if (i == f1 && j == l1) continue // skip your own guess

      val full = i * (n + 1) + j // index for full match (i, j)
      
      // Check how many spectators get better rank than you for case (i, j)
      if (i == f1 || j == l1) {
        // If one of your guesses is correct (first or second)
        // then these spectators are at rank (cntsFull[full] + 1)
        ans = max(ans, cntsFull[full] + 1)
      } else {
        // Both your guesses are wrong
        // You are in this category if (c1) = cntsFirst[i] + cntsSecond[j] - cntsFull[full]
        // So you will be at rank (c2 + c1 + 1)
        ans = max(ans, cntsFirst[i] + cntsSecond[j] - cntsFull[full] + 1)
      }
    }
  }
  println(ans)
}

fun main() {
  sol()
}


// https://github.com/VaHiX/CodeForces/