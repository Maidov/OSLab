
#include <iostream>
#include <cmath>
#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>
#include <chrono>
#include <time.h>
#include "point.h"
#include "func.h"
#include "points.h"



int main(int argc, char* argv[]) {
    size_t maxThreads = 1; // Значение по умолчанию

    if (argc > 1) {
        maxThreads = std::stoul(argv[1]);
    }


    std::cout << maxThreads;
    if (maxThreads == 0){
        std::cout << "---> 100 Points / Threads from 1 to 10 <---\n";
        for (int i = 1; i < 11; i++)
        {
            auto start = std::chrono::steady_clock::now();
            std::vector<Point> result = findLargestTriangleMultiThread(P100, i);
            auto end = std::chrono::steady_clock::now();
            std::cout << "Triangle find in: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << " -- threads: " << i << "\n";
            std::cout << "Треугольник наибольшей площади:" << std::endl;
            for (const auto& point : result) {
                std::cout << "(" << point.x << ", " << point.y << ", " << point.z << ")";
            }
            std::cout << "\n\n";
        }

        std::cout << "---> 200 Points / Threads from 1 to 10 <---\n";
        for (int i = 1; i < 11; i++)
        {
            auto start = std::chrono::steady_clock::now();
            std::vector<Point> result = findLargestTriangleMultiThread(P200, i);
            auto end = std::chrono::steady_clock::now();
            std::cout << "Triangle find in: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << " -- threads: " << i << "\n";
            std::cout << "Треугольник наибольшей площади:" << std::endl;
            for (const auto& point : result) {
                std::cout << "(" << point.x << ", " << point.y << ", " << point.z << ") ";
            }
            std::cout << "\n\n";
        }

        std::cout << "---> 300 Points / Threads from 1 to 10 <---\n";
        for (int i = 1; i < 11; i++)
        {
            auto start = std::chrono::steady_clock::now();
            std::vector<Point> result = findLargestTriangleMultiThread(P300, i);
            auto end = std::chrono::steady_clock::now();
            std::cout << "Triangle find in: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << " -- threads: " << i << "\n";
            std::cout << "Треугольник наибольшей площади:" << std::endl;
            for (const auto& point : result) {
                std::cout << "(" << point.x << ", " << point.y << ", " << point.z << ") ";
            }
            std::cout << "\n\n";
        }

        std::cout << "---> 400 Points / Threads from 1 to 10 <---\n";
        for (int i = 1; i < 11; i++)
        {
            auto start = std::chrono::steady_clock::now();
            std::vector<Point> result = findLargestTriangleMultiThread(P400, i);
            auto end = std::chrono::steady_clock::now();
            std::cout << "Triangle find in: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << " -- threads: " << i << "\n\n";
            std::cout << "Треугольник наибольшей площади:" << std::endl;
            for (const auto& point : result) {
                std::cout << "(" << point.x << ", " << point.y << ", " << point.z << ") ";
            }
            std::cout << "\n\n";
        }
    } else {
        auto start = std::chrono::steady_clock::now();
            std::vector<Point> result = findLargestTriangleMultiThread(P400, maxThreads);
            auto end = std::chrono::steady_clock::now();
            std::cout << "Triangle find in: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << " -- threads: " << maxThreads << "\n\n";
            std::cout << "Треугольник наибольшей площади:" << std::endl;
            for (const auto& point : result) {
                std::cout << "(" << point.x << ", " << point.y << ", " << point.z << ") ";
            }
            std::cout << "\n\n";
    }
    

    return 0;
}