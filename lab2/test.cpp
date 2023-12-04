#include <gtest/gtest.h>
#include "func.h"
#include "points.h"
#include "point.h"

double dbEqual(double a, double b){
    double eps = 10e-5;
    if (fabs(a - b) < eps) return true;
    return false;
}

TEST(test_01, distance1) {   
    Point a{0, 0, 0};
    Point b{1, 0, 0};
    ASSERT_TRUE(dbEqual(distance(a, b), 1.0));
}

TEST(test_01, distance2) {   
    Point a{0, 0, 0};
    Point b{0, 1, 0};
    ASSERT_TRUE(dbEqual(distance(a, b), 1.0));
}

TEST(test_01, distance3) {   
    Point a{0, 0, 0};
    Point b{0, 0, 1};
    ASSERT_TRUE(dbEqual(distance(a, b), 1.0));
}

TEST(test_01, distance4) {   
    Point a{1, 0, 1};
    Point b{0, 0, 0};
    ASSERT_TRUE(dbEqual(distance(a, b), sqrt(2)));
}

TEST(test_02, calcArea1) {   
    Point a{1, 0, 0};
    Point b{0, 0, 0};
    Point c{0, 1, 0};
    ASSERT_TRUE(dbEqual(calcArea(a, b, c), 0.5));
}

TEST(test_02, calcArea2) {   
    Point a{2, 2, 1};
    Point b{2, 2, 2};
    Point c{1, 2, 2};
    ASSERT_TRUE(dbEqual(calcArea(a, b, c), 0.5));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}