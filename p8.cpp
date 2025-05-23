#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
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
pair<vector<vector<T>>, vector<vector<T>>> divide_x(const vector<vector<T>>& X, const vector<vector<T>>& P, int l, int div, int r) {
    vector<vector<T>> x_left, x_right;
    set<vector<T>> left_set, right_set;
    
    for (int i = l; i <= div; i++) {
        left_set.insert(P[i]);
    }
    for (int i = div + 1; i <= r; i++) {
        right_set.insert(P[i]);
    }
    
    for (const auto& point : X) {
        if (left_set.count(point)) {
            x_left.push_back(point);
        } else if (right_set.count(point)) {
            x_right.push_back(point);
        }
    }
    
    return make_pair(x_left, x_right);
}

template <typename T>
pair<vector<vector<T>>, vector<vector<T>>> divide_y(const vector<vector<T>>& Y, const vector<vector<T>>& P, int l, int div, int r) {
    vector<vector<T>> y_left, y_right;
    set<vector<T>> left_set, right_set;
    
    for (int i = l; i <= div; i++) {
        left_set.insert(P[i]);
    }
    for (int i = div + 1; i <= r; i++) {
        right_set.insert(P[i]);
    }
    
    for (const auto& point : Y) {
        if (left_set.count(point)) {
            y_left.push_back(point);
        } else if (right_set.count(point)) {
            y_right.push_back(point);
        }
    }
    
    return make_pair(y_left, y_right);
}

template<typename T>
pair<int, int> closest_points_dc(vector<vector<T>>& P, vector<vector<T>>& X, vector<vector<T>>& Y, int l, int r) {
    T zero = static_cast<T>(0);
    
    if (r - l + 1 <= 3) { 
        Vector<T> p1(P[l][0], P[l][1], zero);
        Vector<T> p2(P[r][0], P[r][1], zero);
        Vector<T> d = p2 - p1;
        int id1 = l;
        int id2 = r;
        T current_dis = d.norm();
        
        for (int i = l; i <= r; i++) {   
            p1 = Vector<T>(P[i][0], P[i][1], zero);
            for (int j = i + 1; j <= r; j++) {   
                p2 = Vector<T>(P[j][0], P[j][1], zero);
                d = p2 - p1;
                T candidate_min = d.norm();
                if (candidate_min < current_dis) {
                    current_dis = candidate_min;
                    id1 = i;
                    id2 = j;
                }
            }
        }
        return make_pair(id1, id2);
    }

    int div = l + (r - l) / 2;
    
    auto x_split = divide_x(X, P, l, div, r);
    auto y_split = divide_y(Y, P, l, div, r);
    
    vector<vector<T>> x_left = x_split.first;
    vector<vector<T>> y_left = y_split.first;
    vector<vector<T>> x_right = x_split.second;
    vector<vector<T>> y_right = y_split.second;

    auto left_ans = closest_points_dc(P, x_left, y_left, l, div);
    auto right_ans = closest_points_dc(P, x_right, y_right, div + 1, r);

    Vector<T> l_p1(P[left_ans.first][0], P[left_ans.first][1], zero);
    Vector<T> l_p2(P[left_ans.second][0], P[left_ans.second][1], zero);
    Vector<T> r_p1(P[right_ans.first][0], P[right_ans.first][1], zero);
    Vector<T> r_p2(P[right_ans.second][0], P[right_ans.second][1], zero);

    Vector<T> delta_l = l_p2 - l_p1;
    Vector<T> delta_r = r_p2 - r_p1;
    T dl = delta_l.norm();
    T dr = delta_r.norm();

    T delta = min(dl, dr);
    pair<int, int> best_pair = (dl < dr) ? left_ans : right_ans;

    T midline = P[div][0];
    vector<vector<T>> strip;
    
    for (const auto& point : Y) {
        if (abs(point[0] - midline) < delta) {
            strip.push_back(point);
        }
    }

    for (int i = 0; i < strip.size(); i++) {
        Vector<T> p1(strip[i][0], strip[i][1], zero);
        for (int j = i + 1; j < strip.size() and j <= i + 7; j++) {
            Vector<T> p2(strip[j][0], strip[j][1], zero);
            Vector<T> dist_vec = p2 - p1;
            T dist = dist_vec.norm();
            
            if (dist < delta) {
                delta = dist;
                int idx1 = -1, idx2 = -1;
                for (int k = 0; k < P.size(); k++) {
                    if (P[k][0] == strip[i][0] and P[k][1] == strip[i][1]) {
                        idx1 = k;
                    }
                    if (P[k][0] == strip[j][0] and P[k][1] == strip[j][1]) {
                        idx2 = k;
                    }
                }
                if (idx1 != -1 and idx2 != -1) {
                    best_pair = make_pair(idx1, idx2);
                }
            }
        }
    }

    return best_pair;
}

template <typename T>
vector<int> closest_points(vector<vector<T>> const& points) {
    vector<vector<T>> P = points;
    vector<vector<T>> X = points;
    vector<vector<T>> Y = points;

    sort(P.begin(), P.end(), [](vector<T> a, vector<T> b) {
        return a[0] < b[0];
    });

    sort(X.begin(), X.end(), [](vector<T> a, vector<T> b) {
        return a[0] < b[0];
    });

    sort(Y.begin(), Y.end(), [](vector<T> a, vector<T> b) {
        return a[1] < b[1];
    });

    auto ans = closest_points_dc(P, X, Y, 0, points.size() - 1);

    int original_idx1 = -1, original_idx2 = -1;
    for (int i = 0; i < points.size(); i++) {
        if (points[i][0] == P[ans.first][0] and points[i][1] == P[ans.first][1]) {
            original_idx1 = i;
        }
        if (points[i][0] == P[ans.second][0] and points[i][1] == P[ans.second][1]) {
            original_idx2 = i;
        }
    }

    vector<int> result{original_idx1, original_idx2};
    sort(result.begin(), result.end());

    return result;
}

TEST(ClosestPointsTest, ImageDataPoints) {
    vector<vector<double>> points = {
        {-8, 2},      // A = 0
        {-7, 4},      // B = 1  
        {-4.47, 1.13}, // C = 2
        {-5.85, 1.87}, // D = 3
        {-6.07, 2.61}, // E = 4
        {-6.57, 0.89}, // F = 5
        {-6.07, -0.69}, // G = 6
        {-5.91, -1.85}, // H = 7
        {-2.63, -1.71}, // I = 8
        {-1.91, -0.71}, // J = 9
        {-3.63, 1.45},  // K = 10
        {-3.71, 3.47},  // L = 11
        {-1.71, 4.35},  // M = 12
        {-1.35, 3.29},  // N = 13
        {-2.89, 2.25},  // O = 14
        {-7.35, 1.45},  // P = 15
        {-4.42, 1.13}   // Q = 16
    };
    
    vector<int> result = closest_points(points);
    cout<<result[0]<<" "<<result[1]<<endl;
    
    // P is at index 15, Q is at index 16
    vector<int> expected = {2, 16};
    EXPECT_EQ(result, expected);
}

TEST(ClosestPointsTest, BasicIntegerTest) {
  std::vector<std::vector<int>> points = {
      {0, 0}, {3, 0}, {0, 4}, {1, 1}, {5, 5}};
  std::vector<int> expected = {0, 3};
  EXPECT_EQ(closest_points(points), expected);
}

TEST(ClosestPointsTest, BasicDoubleTest) {
  std::vector<std::vector<double>> points = {
      {0.5, 0.5}, {1.5, 1.5}, {4.0, 4.0}, {10.0, 10.0}, {0.51, 0.51}};
  std::vector<int> expected = {0, 4};
  EXPECT_EQ(closest_points(points), expected);
}

TEST(ClosestPointsTest, CoincidentPointsTest) {
  std::vector<std::vector<double>> points = {
      {1.0, 1.0}, {2.0, 2.0}, {1.0, 1.0}, {5.0, 5.0}};
  std::vector<int> expected = {0, 2};
  EXPECT_EQ(closest_points(points), expected);
}

TEST(ClosestPointsTest, VeryClosePointsTest) {
  std::vector<std::vector<double>> points = {
      {0.0, 0.0}, {1.0, 1.0}, {1.0 + 1e-10, 1.0 + 1e-10}, {5.0, 5.0}};
  std::vector<int> expected = {1, 2};
  EXPECT_EQ(closest_points(points), expected);
}

TEST(ClosestPointsTest, OnlyTwoPointsTest) {
  std::vector<std::vector<int>> points = {{3, 4}, {1, 2}};
  std::vector<int> expected = {0, 1};
  EXPECT_EQ(closest_points(points), expected);
}

TEST(ClosestPointsTest, PointsOnLineTest) {
  std::vector<std::vector<int>> points = {
      {0, 0}, {1, 1}, {2, 2}, {3, 3}, {5, 5}};
  std::vector<int> expected = {0, 1};
  EXPECT_EQ(closest_points(points), expected);
}

TEST(ClosestPointsTest, PointsOnLineWithDifferentSpacingTest) {
  std::vector<std::vector<int>> points = {
      {0, 0}, {1, 1}, {2, 2}, {3, 3}, {10, 10}};
  std::vector<int> expected = {0, 1};
  EXPECT_EQ(closest_points(points), expected);
}

TEST(ClosestPointsTest, ExtremeValuesTest) {
  std::vector<std::vector<double>> points = {
      {std::numeric_limits<double>::max(), std::numeric_limits<double>::max()},
      {std::numeric_limits<double>::max() - 1.0,
       std::numeric_limits<double>::max() - 1.0},
      {0.0, 0.0},
      {-std::numeric_limits<double>::max(),
       -std::numeric_limits<double>::max()}};
  std::vector<int> expected = {0, 1};
  EXPECT_EQ(closest_points(points), expected);
}

TEST(ClosestPointsTest, NegativeCoordinatesTest) {
  std::vector<std::vector<int>> points = {
      {-10, -10}, {-8, -8}, {-5, -5}, {0, 0}, {5, 5}};
  std::vector<int> expected = {0, 1};
  EXPECT_EQ(closest_points(points), expected);
}

TEST(ClosestPointsTest, ReversedIndicesTest) {
  std::vector<std::vector<int>> points = {{100, 100}, {0, 0}, {1, 1}};
  std::vector<int> expected = {1, 2};
  EXPECT_EQ(closest_points(points), expected);
}

TEST(ClosestPointsTest, PointsInRandomOrderTest) {
  std::vector<std::vector<double>> points = {
      {5.67, 3.45}, {9.12, 4.23}, {1.56, 7.89}, {5.69, 3.43}, {10.11, 12.13}};
  std::vector<int> expected = {0, 3};
  EXPECT_EQ(closest_points(points), expected);
}

TEST(ClosestPointsTest, MaxIntValueTest) {
  std::vector<std::vector<int>> points = {{INT_MAX, INT_MAX},
                                          {INT_MAX - 1, INT_MAX - 1},
                                          {0, 0},
                                          {INT_MIN, INT_MIN}};
  std::vector<int> expected = {0, 1};
  EXPECT_EQ(closest_points(points), expected);
}

TEST(ClosestPointsTest, LargeNumberOfPointsTest) {
  std::vector<std::vector<int>> points;
  for (int i = 0; i < 1000; i++) {
    points.push_back({i * 10, i * 10});
  }
  points.push_back({5, 5});
  points.push_back({6, 6});

  std::vector<int> expected = {1000, 1001};
  EXPECT_EQ(closest_points(points), expected);
}


int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}