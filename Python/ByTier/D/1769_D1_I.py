# Problem: CF 1769 D1 - Игра в Девятку I
# https://codeforces.com/contest/1769/problem/D1

"""
Игра в Девятку I
Алгоритм: Минимакс с мемоизацией
Описание: Игра моделируется как двухигроковая игра с идеальными стратегиями. 
Каждый игрок пытается выиграть, делая наилучший ход в зависимости от ситуации.
Используется рекурсивная функция с мемоизацией для определения, может ли текущий игрок выиграть.
Временная сложность: O(2^18) в худшем случае, но с мемоизацией уменьшается до приемлемого уровня на практике.
Пространственная сложность: O(2^18) для хранения кэша.
"""

VALUES = "6789TJQKA"
SIUS = "CDSH"
popanegra = ""


def get_card(card: str) -> int:
    # Преобразует строку карты в числовой идентификатор
    return VALUES.index(card[0]) * 10 + SIUS.index(card[1])


def prev_card(card: int) -> int:
    # Возвращает предыдущую карту в последовательности
    return card - 10 if card > 30 else card + 10


def memory(function):
    # Декоратор для мемоизации результатов рекурсивной функции
    def wrapper(cards1: list[int], cards2: list[int]) -> bool:
        nonlocal cache
        args = (tuple(cards1), tuple(cards2))
        if args in cache:
            return cache[args]
        result = function(cards1, cards2)
        cache[args] = result
        return result

    cache = dict()
    return wrapper


@memory
def game(cards1: list[int], cards2: list[int]) -> bool:
    # Рекурсивная функция определяет, выиграет ли игрок, который ходит первым (cards1)
    has_card = False
    for card in cards1:
        # Проверяет, есть ли предыдущая карта в руках у игроков
        prev = prev_card(card)
        if card // 10 == 3 or (prev not in cards1 and prev not in cards2):
            # Выполняет ход, если можно выложить на стол
            has_card = True
            new_cards1 = cards1.copy()
            new_cards1.remove(card)
            if not new_cards1:
                # Если это последний ход, игрок выигрывает
                return True
            # Если противник не может выиграть после хода, текущий игрок выигрывает
            if not game(cards2, new_cards1):
                return True
    if has_card:
        # Если ход был, но игрок не выиграл, то он проиграл
        return False
    # Если нет ходов, игрок не может выиграть
    return not game(cards2, cards1)


# Чтение входных данных и преобразование карт
cards1 = sorted(map(get_card, input().split()))
cards2 = sorted(map(get_card, input().split()))
if game(cards1, cards2):
    print("Alice")
else:
    print("Bob")


# https://github.com/VaHiX/CodeForces/