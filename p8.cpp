#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>
#include <set>
#include <gtest/gtest.h>
#define ll long long
#define ld long double

using namespace std;

template <typename T>
int sgn(T val) {
    if (val < static_cast<T>(0)) return -1;
    if (val > static_cast<T>(0)) return 1;
    return 0;
}

template <typename T>
class Vector {
private:
    bool is_int;

public:
    T x_, y_, z_;

    // Constructor original
    Vector(T x, T y, T z) : x_(x), y_(y), z_(z) {
        if (is_same<int, T>::value) {
            is_int = true;
        } else is_int = false;
    }

    Vector(ll x, ll y, ll z) {
        if (is_same<int, T>::value) {
            is_int = true;
            x_ = (x > INT_MAX) ? INT_MAX : ((x < INT_MIN) ? INT_MIN : static_cast<T>(x));
            y_ = (y > INT_MAX) ? INT_MAX : ((y < INT_MIN) ? INT_MIN : static_cast<T>(y));
            z_ = (z > INT_MAX) ? INT_MAX : ((z < INT_MIN) ? INT_MIN : static_cast<T>(z));
        } else {
            is_int = false;
            x_ = static_cast<T>(x);
            y_ = static_cast<T>(y);
            z_ = static_cast<T>(z);
        }
    }

    Vector(ld x, ld y, ld z) {
        if (is_same<int, T>::value) {
            is_int = true;
            x_ = (x > INT_MAX) ? INT_MAX : ((x < INT_MIN) ? INT_MIN : static_cast<T>(x));
            y_ = (y > INT_MAX) ? INT_MAX : ((y < INT_MIN) ? INT_MIN : static_cast<T>(y));
            z_ = (z > INT_MAX) ? INT_MAX : ((z < INT_MIN) ? INT_MIN : static_cast<T>(z));
        } else {
            is_int = false;
            x_ = static_cast<T>(x);
            y_ = static_cast<T>(y);
            z_ = static_cast<T>(z);
        }
    }

    [[nodiscard]] T dot_product(const Vector<T>& other) const {
        if (is_int) {
            ll a = (ll)other.x_ * (ll)x_;
            ll b = (ll)other.y_ * (ll)y_;
            ll c = (ll)other.z_ * (ll)z_;
            return a + b + c;
        }

        ld a = (ld)other.x_ * (ld)x_;
        ld b = (ld)other.y_ * (ld)y_;
        ld c = (ld)other.z_ * (ld)z_;
        return a + b + c;
    }

    Vector<T> cross_product(const Vector<T>& other) const {
        if (is_int) {
            ll x = (ll)y_ * (ll)other.z_ - (ll)z_ * (ll)other.y_;
            ll y = (ll)z_ * (ll)other.x_ - (ll)x_ * (ll)other.z_; 
            ll z = (ll)x_ * (ll)other.y_ - (ll)y_ * (ll)other.x_;
            return Vector<T>((ll)x, (ll)y, (ll)z);
        }
        
        ld x = (ld)y_ * (ld)other.z_ - (ld)z_ * (ld)other.y_;
        ld y = (ld)z_ * (ld)other.x_ - (ld)x_ * (ld)other.z_; 
        ld z = (ld)x_ * (ld)other.y_ - (ld)y_ * (ld)other.x_;
        return Vector<T>((ld)x, (ld)y, (ld)z);
    }

    Vector<T> operator+(const Vector<T>& other) const {
        if (is_int) {
            ll x = (ll)x_ + (ll)other.x_;
            ll y = (ll)y_ + (ll)other.y_;
            ll z = (ll)z_ + (ll)other.z_;
            return Vector<T>((ll)x, (ll)y, (ll)z);
        } else {
            ld x = (ld)x_ + (ld)other.x_;
            ld y = (ld)y_ + (ld)other.y_;
            ld z = (ld)z_ + (ld)other.z_;
            return Vector<T>((ld)x, (ld)y, (ld)z);
        }
    }

    Vector<T> operator-(const Vector<T>& other) const {
        if (is_int) {
            ll x = (ll)x_ - (ll)other.x_;
            ll y = (ll)y_ - (ll)other.y_;
            ll z = (ll)z_ - (ll)other.z_;
            return Vector<T>((ll)x, (ll)y, (ll)z);
        } else {
            ld x = (ld)x_ - (ld)other.x_;
            ld y = (ld)y_ - (ld)other.y_;
            ld z = (ld)z_ - (ld)other.z_;
            return Vector<T>((ld)x, (ld)y, (ld)z);
        }
    }

    bool operator==(const Vector<T>& other) const {
        return x_ == other.x_ && y_ == other.y_ && z_ == other.z_;
    }

    T norm() {
        return sqrt(dot_product(*this));
    }

    void print() {
        cout << "X :" << x_ << endl;
        cout << "Y :" << y_ << endl;
        cout << "Z :" << z_ << endl;
    }
};

bool my_xor(bool a, bool b) {
    return a != b;
}
template <typename T>
	vector<int> closest_points(vector<vector<T>> const& points){

    }