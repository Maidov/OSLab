#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>
#include <chrono>
#include <time.h>
#include "point.h"
#include "points.h"

std::mutex maxAreaMutex;


Point getRPoint(int Min, int Max) {
    Point result;

    // Инициализация генератора случайных чисел

    // Генерация случайных чисел в заданных границах
    result.x = std::rand() % (Max - Min + 1) + Min;
    result.y = std::rand() % (Max - Min + 1) + Min;
    result.z = std::rand() % (Max - Min + 1) + Min;

    return result;
}

void getRPoints(int n){
    std::srand(std::time(NULL));
    std::cout << "{";
    for (int i = 0; i < n; i++)
    {
        Point p = getRPoint(-100, 100);
        std::cout << "{" << p.x << ", " << p.y << ", " << p.z << "}, \n";
    }
    std::cout << "}";
    
}

double distance(const Point& p1, const Point& p2) {
    return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2) + std::pow(p2.z - p1.z, 2));
}

double calcArea(const Point& p1, const Point& p2, const Point& p3) {
    double a = distance(p1, p2);
    double b = distance(p2, p3);
    double c = distance(p3, p1);
    double s = (a + b + c) / 2;
    return std::sqrt(s * (s - a) * (s - b) * (s - c));
}

void findLargestTriangleThread(const std::vector<Point>& points, size_t start, size_t end, double& maxArea, std::vector<Point>& maxTriangle) {
    for (size_t i = start; i < end; ++i) {
        for (size_t j = 0; j < points.size(); ++j) {
            for (size_t k = 0; k < points.size(); ++k) {
                double currentArea = calcArea(points[i], points[j], points[k]);
                if (currentArea > maxArea) {
                    std::lock_guard<std::mutex> lock(maxAreaMutex);
                    if (currentArea > maxArea) {
                        maxArea = currentArea;
                        maxTriangle = {points[i], points[j], points[k]};
                    }
                }
            }
        }
    }
}

std::vector<Point> findLargestTriangleMultiThread(const std::vector<Point>& points, size_t maxThreads) {
    double maxArea = 0;
    std::vector<Point> maxTriangle;

    size_t chunkSize = points.size() / maxThreads;
    std::vector<std::thread> threads;

    for (size_t i = 0; i < maxThreads; ++i) {
        size_t start = i * chunkSize;
        size_t end = (i == maxThreads - 1) ? points.size() : (i + 1) * chunkSize;
        threads.emplace_back(findLargestTriangleThread, std::ref(points), start, end, std::ref(maxArea), std::ref(maxTriangle));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return maxTriangle;
}

int min(int a, int b){
    if (a < b) return a;
    return b;
}