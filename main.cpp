#include <iostream>
#include <vector>
#include <thread>
#include <cstdlib>
#include <chrono>
#include <functional>

void sumArr(std::vector<int> &array, int start, int end, int &result)
{
    for (int i = start; i < end; i++)
    {
        result += array[i];
    }
}

int main()
{
    int sum{};
    int countParts{};
    int arrSize{};
    std::vector<int> result{};
    std::vector<std::thread> threads{};

    std::cout << "Enter the array size: ";
    std::cin >> arrSize;

    if (arrSize <= 0)
    {
        std::cout << "The array size cannot be equal or less than zero" << std::endl;
        return 1;
    }

    std::cout << "Enter the number of parts (array must be divided into equal parts): ";
    std::cin >> countParts;

    if (countParts <= 0)
    {
        std::cout << "The number of threads cannot be equal or less than zero" << std::endl;
        return 1;
    }
    else if (arrSize % countParts != 0)
    {
        std::cout << "The array must be divided into equal parts" << std::endl;
        return 1;
    }
    else
    {
        std::vector<int> array(arrSize);

        for (int i = 0; i < arrSize; i++)
        {
            array[i] = std::rand() % 10 + 1;
            //std::cout << array[i] << " ";
        }

        std::cout << std::endl;

        auto timerStart = std::chrono::steady_clock::now();

        for (int i = 0; i < countParts; i++)
        {
            sum = 0;
            int start = i * (array.size() / countParts);
            int end = (i + 1) * (array.size() / countParts);

            threads.push_back(std::thread(sumArr, std::ref(array), start, end, std::ref(sum)));
            threads[i].join();
            result.push_back(sum);
        }

        sum = 0;
        for (int i = 0; i < result.size(); i++)
        {
            std::cout << i + 1 << " thread sum = " << result[i] << std::endl;
            sum += result[i];
        }

        auto timerStop = std::chrono::steady_clock::now();
        std::chrono::duration<double> timerDuration = timerStop - timerStart;

        std::cout << "All threads sum = " << sum << std::endl << "Time spent: " << timerDuration.count() << " seconds" << std::endl;
    }
    return 0;
}