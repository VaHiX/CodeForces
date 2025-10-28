// Problem: CF 1431 A - Selling Hamburgers
// https://codeforces.com/contest/1431/problem/A

import java.util.*

/*
 * Problem: Selling Hamburgers
 * 
 * Algorithm: 
 * - Sort the array of customer coins in ascending order.
 * - For each possible price m (which is the value at index i in the sorted array),
 *   calculate the number of customers who can buy a hamburger at that price (n - i).
 *   The profit is then m * (number of customers).
 * - Keep track of the maximum profit encountered.
 * 
 * Time Complexity: O(n log n) due to sorting, where n is the number of customers.
 * Space Complexity: O(n) for storing the array of customer coins.
 */

fun solve() {
  val n = readLine()!!.toInt()
  val a = LongArray(n)
  val input = readLine()!!.split(" ").map { it.toLong() }
  for (i in 0 until n) {
    a[i] = input[i]
  }
  a.sort() // Sort the array to process customers in ascending order of coins
  var res = 0L
  for (i in 0 until n) {
    // For each price a[i], calculate profit = price * count of customers who can afford it
    res = maxOf(a[i] * (n - i), res)
  }
  println(res)
}

fun main() {
  val t = readLine()!!.toInt()
  repeat(t) { solve() }
}


// https://github.com/VaHiX/CodeForces/