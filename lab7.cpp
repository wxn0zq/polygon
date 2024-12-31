#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>

using namespace std;

class Solution {
public:
    int maxSum(vector<int>& nums1, vector<int>& nums2) {
        const int MOD = 1e9 + 7;
        long long sum1 = 0, sum2 = 0, result = 0;
        size_t index1 = 0, index2 = 0;

        for (; index1 < nums1.size() || index2 < nums2.size();) {
            if (index1 < nums1.size() && (index2 == nums2.size() || nums1[index1] < nums2[index2])) {
                sum1 += nums1[index1++];
            } else if (index2 < nums2.size() && (index1 == nums1.size() || nums1[index1] > nums2[index2])) {
                sum2 += nums2[index2++];
            } else {
                result += max(sum1, sum2) + nums1[index1];
                sum1 = sum2 = 0;
                ++index1;
                ++index2;
            }
        }

        result += max(sum1, sum2);
        return result % MOD;
    }
};

int main() {
    Solution sol;

    // Генерация случайных данных для тестов
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 1000);

    vector<int> nums1, nums2;
    vector<int> sizes;
    vector<double> times;

    // Измерение времени для разных размеров данных
    for (int n = 1; n <= 1000; n += 50) {  // Протестируем для разных размеров
        nums1.clear();
        nums2.clear();

        // Заполняем векторы случайными числами
        for (int i = 0; i < n; ++i) {
            nums1.push_back(dis(gen));
            nums2.push_back(dis(gen));
        }

        auto start = chrono::high_resolution_clock::now();
        sol.maxSum(nums1, nums2);  // Замер времени выполнения
        auto end = chrono::high_resolution_clock::now();
        
        chrono::duration<double> duration = end - start;
        sizes.push_back(n);
        times.push_back(duration.count());
    }

    // Запись данных в CSV файл
    ofstream file("execution_times.csv");
    file << "Размер входных данных (n + m), Время выполнения (секунды)\n";
    for (size_t i = 0; i < sizes.size(); ++i) {
        file << sizes[i] << ", " << times[i] << "\n";
    }

    file.close();

    cout << "Данные записаны в файл execution_times.csv" << endl;

    return 0;
}
