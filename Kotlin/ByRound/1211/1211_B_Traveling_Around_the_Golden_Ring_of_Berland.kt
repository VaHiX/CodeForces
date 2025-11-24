// Problem: CF 1211 B - Traveling Around the Golden Ring of Berland
// https://codeforces.com/contest/1211/problem/B

/**
 * Problem: Traveling Around the Golden Ring of Berland
 * 
 * Algorithm/Techniques: Greedy approach with prefix sum analysis
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 * 
 * The solution works by finding the maximum number of selfies required in any city,
 * then calculating the minimum number of visits needed based on how many times
 * we must traverse the ring to satisfy all requirements.
 */
fun main() {
  val n: Int = readLine()!!.toInt()
  var str = readLine()
  val strings = str?.split(' ')!!.toList()
  val numbers = IntArray(strings.size)
  strings.indices.forEach { numbers[it] = strings[it].toInt() }
  var largestElement = numbers[0]
  var position: Int = 0
  for (i in 0..n - 1) {
    if (largestElement <= numbers[i]) {
      largestElement = numbers[i]
      position = i
    }
  }
  largestElement = largestElement - 1
  var ans: Long = (largestElement.toLong() * (numbers.size).toLong()) + position.toLong() + 1L
  println(ans)
}


// https://github.com/VaHiX/CodeForces/