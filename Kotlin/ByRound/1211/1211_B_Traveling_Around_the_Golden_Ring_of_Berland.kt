// Contest 1211, Problem B: Traveling Around the Golden Ring of Berland
// URL: https://codeforces.com/contest/1211/problem/B

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
