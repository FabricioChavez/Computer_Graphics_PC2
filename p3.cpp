#include <iostream>
#include <climits>
#include <vector>
#include <cmath>
#include <gtest/gtest.h>
#define ll long long
#define ld long double
using namespace std;

template <typename T>
int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

template <typename T>
class Vector {
private:
    bool is_int;

public:
    T x_, y_, z_;

    Vector(T x, T y, T z) : x_(x), y_(y), z_(z) {
        is_int = std::is_same<T, int>::value;
    }

    T dot_product(const Vector<T>& other) const {
        if (is_int) {
            ll a = (ll)x_ * other.x_;
            ll b = (ll)y_ * other.y_;
            ll c = (ll)z_ * other.z_;
            return static_cast<T>(a + b + c);
        } else {
            return x_ * other.x_ + y_ * other.y_ + z_ * other.z_;
        }
    }

    Vector<T> cross_product(const Vector<T>& other) const {
        if (is_int) {
            ll x = y_ * other.z_ - z_ * other.y_;
            ll y = z_ * other.x_ - x_ * other.z_;
            ll z = x_ * other.y_ - y_ * other.x_;
            return Vector<T>(x, y, z);
        } else {
            T x = y_ * other.z_ - z_ * other.y_;
            T y = z_ * other.x_ - x_ * other.z_;
            T z = x_ * other.y_ - y_ * other.x_;
            return Vector<T>(x, y, z);
        }
    }

    Vector<T> operator+(const Vector<T>& other) const {
        return Vector(x_ + other.x_, y_ + other.y_, z_ + other.z_);
    }

    Vector<T> operator-(const Vector<T>& other) const {
        return Vector(x_ - other.x_, y_ - other.y_, z_ - other.z_);
    }

    T norm() {
        return sqrt(dot_product(*this));
    }

    void print() {
        cout << "X: " << x_ << "\nY: " << y_ << "\nZ: " << z_ << endl;
    }
};

double distance_point_to_line_3D(double p1x, double p1y, double p1z, 
                                 double dx, double dy, double dz,
                                 double px, double py, double pz) {
    Vector<double> P1top(px - p1x, py - p1y, pz - p1z);
    Vector<double> director(dx, dy, dz);
    double area = P1top.cross_product(director).norm();
    double base = director.norm();
    if (base == 0) return INFINITY; // Handle zero direction vector
    return area / base;
}

// Tests corregidos
TEST(DistancePointToLine3DTest, PointOnLine) {
    double distance = distance_point_to_line_3D(0, 0, 0, 1, 1, 1, 1, 1, 1);
    EXPECT_NEAR(distance, 0.0, 1e-10);
}

TEST(DistancePointToLine3DTest, PointNearLine) {
    double distance = distance_point_to_line_3D(0, 0, 0, 1, 0, 0, 0, 1, 0);
    EXPECT_NEAR(distance, 1.0, 1e-10);
}

TEST(DistancePointToLine3DTest, KnownDistance) {
    double distance = distance_point_to_line_3D(0, 0, 0, 0, 0, 1, 3, 4, 5);
    EXPECT_NEAR(distance, 5.0, 1e-10);
}

TEST(DistancePointToLine3DTest, LineNotThroughOrigin) {
    double distance = distance_point_to_line_3D(1, 2, 3, 1, 1, 1, 2, 3, 4);
    EXPECT_NEAR(distance, 0.0, 1e-10);
}

TEST(DistancePointToLine3DTest, LargeNumbers) {
    double distance = distance_point_to_line_3D(1000, 2000, 3000, 10, 10, 10, 1010, 2010, 3000);
    EXPECT_NEAR(distance, 10*sqrt(2.0/3.0), 1e-3); // ~8.165
}

TEST(DistancePointToLine3DTest, SmallNumbers) {
    double distance = distance_point_to_line_3D(
        0.001, 0.002, 0.003, // P1
        0.1, 0.1, 0.1,       // d
        0.001, 0.002, 0.103  // P
    );
    EXPECT_NEAR(distance, 0.0816, 1e-4); // Tolerancia de 0.0001
}

TEST(DistancePointToLine3DTest, NegativeNumbers) {
    double distance = distance_point_to_line_3D(-1, -2, -3, -1, -1, -1, -2, -3, -4);
    EXPECT_NEAR(distance, 0.0, 1e-10);
}

TEST(DistancePointToLine3DTest, ParallelToAxis) {
    double distance = distance_point_to_line_3D(5, 6, 7, 0, 0, 1, 8, 9, 10);
    EXPECT_NEAR(distance, sqrt(18.0), 1e-10);
}

TEST(DistancePointToLine3DTest, NonUnitDirectionVector) {
    double distance = distance_point_to_line_3D(0, 0, 0, 3, 4, 0, 0, 0, 10);
    EXPECT_NEAR(distance, 10.0, 1e-10);
}

TEST(DistancePointToLine3DTest, ArbitraryCase) {
    double distance = distance_point_to_line_3D(2, 3, 4, 5, 6, 7, 8, 7, 6);
    EXPECT_NEAR(distance, sqrt(1536.0/110.0), 1e-3); // ~3.737
}

TEST(DistancePointToLine3DTest, TinyDirectionVector) {
    double distance = distance_point_to_line_3D(1, 1, 1, 1e-10, 1e-10, 1e-10, 2, 2, 2);
    EXPECT_NEAR(distance, 0.0, 1e-5);
}

TEST(DistancePointToLine3DTest, ZeroDirectionVector) {
    double distance = distance_point_to_line_3D(0, 0, 0, 0, 0, 0, 1, 1, 1);
    EXPECT_TRUE(std::isinf(distance));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}