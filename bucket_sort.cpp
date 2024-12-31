#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert> 
using namespace std;

void bucketSort(vector<int>& arr) {
    if (arr.empty()) return;

    // найдем минимальный и максимальный элементы
    int minVal = *min_element(arr.begin(), arr.end());
    int maxVal = *max_element(arr.begin(), arr.end());

    // установим количество корзин 
    int bucketCount = sqrt(arr.size());
    int bucketRange = ceil((maxVal - minVal + 1) / static_cast<double>(bucketCount));

    // создадим пустые корзины
    vector<vector<int>> buckets(bucketCount);

    // распределим элементы по корзинам
    for (int num : arr) {
        int index = (num - minVal) / bucketRange;
        if (index >= bucketCount) index = bucketCount - 1; // попадание в последнюю корзину
        buckets[index].push_back(num);
    }

    // отсортируем каждую корзину и объединим результат
    arr.clear();
    for (auto& bucket : buckets) {
        sort(bucket.begin(), bucket.end());
        arr.insert(arr.end(), bucket.begin(), bucket.end());
    }
}

void testBucketSort() {
    // лучший случай: уже отсортированный массив
    vector<int> bestCase = {1, 2, 3, 4, 5};
    bucketSort(bestCase);
    assert(bestCase == vector<int>({1, 2, 3, 4, 5}));

    // средний случай: случайный порядок
    vector<int> averageCase = {3, 1, 4, 5, 2};
    bucketSort(averageCase);
    assert(averageCase == vector<int>({1, 2, 3, 4, 5}));

    // худший случай: обратный порядок
    vector<int> worstCase = {5, 4, 3, 2, 1};
    bucketSort(worstCase);
    assert(worstCase == vector<int>({1, 2, 3, 4, 5}));

    cout << "все тесты для bucket sort пройдены успешно." << endl;
}

// Пример использования
int main() {
    vector<int> data = {29, 25, 3, 49, 9, 37, 21, 43};

    cout << "исходный массив: ";
    for (int num : data) cout << num << " ";
    cout << endl;

    bucketSort(data);

    cout << "отсортированный массив: ";
    for (int num : data) cout << num << " ";
    cout << endl;

    testBucketSort();

    return 0;
}
