// shell sort
#include <iostream>
#include <vector>
#include <cassert> 
using namespace std;


void shell_sort(vector<int>& arr){
    int n = arr.size();
    // сначала берем большой промежуток, потом уменьшаем
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // делаем сортировку вставками для тек промежутка
        for (int i = gap; i < n; ++i) {
            int temp = arr[i];
            int j;

            // сдвигаем элементы которые находятся на расстоянии gap, чтобы отсортировать их
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

void testShellSort() {
    vector<int> bestCase = {1, 2, 3, 4, 5};
    shell_sort(bestCase);
    assert(bestCase == vector<int>({1, 2, 3, 4, 5}));

    vector<int> averageCase = {3, 1, 4, 5, 2};
    shell_sort(averageCase);
    assert(averageCase == vector<int>({1, 2, 3, 4, 5}));

    vector<int> worstCase = {5, 4, 3, 2, 1};
    shell_sort(worstCase);
    assert(worstCase == vector<int>({1, 2, 3, 4, 5}));

    cout << "Все тесты для shell sort пройдены успешно." << endl;
}


int main(){
    // vector<int> arr = {1, 2, 3, 4, 5, 6, 7};
    // vector<int> arr = {1, 2, 3, 4, 5, 6, 7};
    vector<int> arr = {64, 34, 25, 12, 22, 11, 90};

    cout << "исходный массив:\n";
    for (int x : arr) {
        cout << x << " ";
    }
    cout << "\n";

    shell_sort(arr);

    cout << "отсортированный массив:\n";
    for (int x : arr) {
        cout << x << " ";
    }
    cout << "\n";

    testShellSort();

    return 0;
}
