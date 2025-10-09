// Contest 1211, Problem E: Double Permutation Inc.
// URL: https://codeforces.com/contest/1211/problem/E

private fun readLn() = readLine()!!

private fun readInt() = readLn().toInt()

private fun readLong() = readLn().toLong()

private fun readDouble() = readLn().toDouble()

private fun readStrings() = readLn().split(" ")

private fun readInts() = readStrings().map { it.toInt() }

private fun readLongs() = readStrings().map { it.toLong() }

private fun readDoubles() = readStrings().map { it.toDouble() }

fun main(args: Array<String>) {
  var n = readInt()
  var a = readInts()
  val MAX = 200010
  var cnt = IntArray(MAX)
  for (x in a) cnt[x]++
  var low = 0
  var high = n
  while (low < high) {
    var mid = (low + high + 1) / 2
    var ok = true
    for (i in 1..mid) {
      if (cnt[i] != 2) {
        ok = false
        break
      }
    }
    if (ok) {
      var x = ArrayList<Int>()
      var y = 0
      var cc = IntArray(mid + 1)
      for (v in a) {
        if (v <= mid) {
          if (cc[v] == 0) {
            x.add(v)
          } else {
            if (x[y] != v) {
              ok = false
              break
            }
            y += 1
          }
          cc[v] += 1
        }
      }
    }
    if (ok) {
      low = mid
    } else {
      high = mid - 1
    }
  }
  var res = CharArray(n)
  var mid = low
  var x = ArrayList<Int>()
  var y = 0
  var cc = IntArray(mid + 1)
  for (it in 0..n - 1) {
    var v = a[it]
    if (v <= mid) {
      if (cc[v] == 0) {
        res[it] = 'R'
      } else {
        res[it] = 'G'
      }
      cc[v] += 1
    } else {
      res[it] = 'B'
    }
  }
  println(res.joinToString(""))
}
