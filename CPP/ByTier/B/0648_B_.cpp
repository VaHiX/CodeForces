// Problem: CF 648 B - Собери стол
// https://codeforces.com/contest/648/problem/B

/*
 * Собери стол
 * 
 * Алгоритм:
 * 1. Отсортировать все части по возрастанию длины.
 * 2. Сопоставить первую часть с последней, вторую с предпоследней и т.д.
 *    Это обеспечивает равномерное распределение длин частей для формирования ножек одинаковой длины.
 * 
 * Сложность:
 * - Время: O(n log n) из-за сортировки
 * - Память: O(n) для хранения массива частей
 */

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(2 * n);
  for (long p = 0; p < 2 * n; p++) {
    scanf("%ld", &a[p]);
  }
  sort(a.begin(), a.end());  // Сортируем части по возрастанию длины
  for (long p = 0; p < n; p++) {
    printf("%ld %ld\n", a[p], a[2 * n - 1 - p]);  // Пары: первая с последней, вторая с предпоследней и т.д.
  }
  puts("");
}


// https://github.com/VaHiX/CodeForces/