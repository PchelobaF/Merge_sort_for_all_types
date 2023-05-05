#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <array>
#include <fstream>
#include <sstream>
#include <limits>
#include <numeric>
#include <type_traits>
#include <locale.h>

template<typename T>
void merge_sort(std::vector<T>& arr) {
    if (arr.size() > 1) {
        const size_t mid = arr.size() / 2;
        auto left = std::vector<T>(arr.begin(), arr.begin() + mid);
        auto right = std::vector<T>(arr.begin() + mid, arr.end());

        merge_sort(left);
        merge_sort(right);

        size_t i = 0, j = 0, k = 0;
        auto temp = std::vector<T>(arr.size());

        while (i < left.size() && j < right.size()) {
            if (left[i] <= right[j]) {
                temp[k] = left[i];
                i++;
            }
            else {
                temp[k] = right[j];
                j++;
            }
            k++;
        }

        while (i < left.size()) {
            temp[k] = left[i];
            i++;
            k++;
        }

        while (j < right.size()) {
            temp[k] = right[j];
            j++;
            k++;
        }

        for (size_t idx = 0; idx < arr.size(); ++idx) {
            arr[idx] = temp[idx];
        }
    }
}

template<typename T>
void cycle_sort(T &arr) {
    std::array<size_t, 12> results{ 0 };
    for (size_t i = 0; i < 12; i++) {
        auto start = std::chrono::steady_clock::now();
        merge_sort(arr);
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start);
        results[i] = static_cast<int>(duration.count());
    }
    auto min_result = *std::min_element(results.begin(), results.end());
    auto max_result = *std::max_element(results.begin(), results.end());
    auto sum = std::accumulate(results.begin(), results.end(), 0ull);
    auto res = static_cast<unsigned int>((sum - min_result - max_result) / 10);
    std::cout << "Среднее время выполнения (без учета максимального и минимального): " << res << " микросекунд" << std::endl;
    std::cout << "Время выполнения в 12 циклах: ";
    for (const auto& result : results) {
        std::cout << result << " ";
    }
    std::cout << std::endl;
}

template<typename T>
void new_rand_arr(std::vector<T>& arr, T start, T end) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<T> distrib(start, end);

    for (auto& element : arr) {
        element = distrib(gen);
    }
}

void new_rand_arr_int(std::vector<int>& arr, int start, int end) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(start, end);

    for (auto& element : arr) {
        element = distrib(gen);
    }
}

std::vector<std::string> generate_string_arr(int size) {
    std::ifstream file("E:/HTML Academy/проекты на Python/rust-projects/rust-app/src/text.txt");
    if (!file.is_open()) {
        std::cerr << "Something went wrong reading the file" << std::endl;
        exit(1);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string contents = buffer.str();

    std::transform(contents.begin(), contents.end(), contents.begin(), [](unsigned char c) { return std::tolower(c); });

    std::replace_if(contents.begin(), contents.end(), [](unsigned char c) {
        return std::ispunct(c);
        }, ' ');

    std::stringstream ss(contents);
    std::vector<std::string> new_contents;
    std::string word;
    int count = 0;

    while (ss >> word && count < size) {
        new_contents.push_back(word);
        count++;
    }

    std::cout << "Массив заполнен " << new_contents.size() << " строками" << std::endl;

    return new_contents;
}


size_t set_size_arr() {
    size_t number = 0;
    std::cout << "Введите размер массива данных: ";
    std::cin >> number;
    std::cout << "Массивы заполнены " << number << " элементами\n" << std::endl;
    return number;
}

int main() {
    setlocale(LC_ALL, "Russian");
    int size = set_size_arr();

    std::vector<int> ints(size);
    new_rand_arr_int(ints, 0, INT_MAX);
    cycle_sort(ints);
    std::cout << "\n";

    std::vector<float> floats(size);
    new_rand_arr(floats, 0.0f, std::numeric_limits<float>::max());
    cycle_sort(floats);
    std::cout << "\n";

    std::vector<double> doubles(size);
    new_rand_arr(doubles, 0.0, std::numeric_limits<double>::max());
    cycle_sort(doubles);
    std::cout << "\n";

    std::vector<std::string> string_arr = generate_string_arr(size);
    cycle_sort(string_arr);

    return 0;
}
