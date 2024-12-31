#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

void combSort(vector<int>& arr) {
    int n = arr.size();
    int gap = n; // начальный разрыв
    const double shrink = 1.3; // коэффициент уменьшения разрыва
    bool sorted = false;

    while (!sorted) {
        // уменьшаем разрыв
        gap = static_cast<int>(gap / shrink);
        if (gap <= 1) {
            gap = 1;
            sorted = true;
        }

        // пузырьковая сортировка
        for (int i = 0; i < n - gap; ++i) {
            if (arr[i] > arr[i + gap]) {
                swap(arr[i], arr[i + gap]);
                sorted = false;
            }
        }
    }
}

void testCombSort() {
    vector<int> bestCase = {1, 2, 3, 4, 5};
    combSort(bestCase);
    assert(bestCase == vector<int>({1, 2, 3, 4, 5}));

    vector<int> averageCase = {3, 1, 4, 5, 2};
    combSort(averageCase);
    assert(averageCase == vector<int>({1, 2, 3, 4, 5}));

    vector<int> worstCase = {5, 4, 3, 2, 1};
    combSort(worstCase);
    assert(worstCase == vector<int>({1, 2, 3, 4, 5}));

    cout << "все тесты пройдены успешно" << endl;
}

int main() {
    vector<int> arr = {34, 7, 23, 32, 5, 62};

    cout << "исходный массив: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    combSort(arr);

    cout << "отсортированный массив: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    testCombSort();

    return 0;
}
