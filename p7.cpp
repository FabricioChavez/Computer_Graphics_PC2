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
bool intersection(T x1 , T y1 , T x2 , T y2 , T x3 , T y3  , T x4 , T y4 ) { // P1

    if ((x1 == x3 and y1 == y3) or (x1 == x4 and y1 == y4) or (x2 == x3 and y2 == y3) or (x2 == x4 and y2 == y4))
    return true;

    T lowerx1 = min(x1,x2);
    T lowerx2 = min(x3,x4);
    T upperx1 = max(x1,x2);
    T upperx2 = max(x3,x4);

    bool x_condition = max(lowerx1 , lowerx2)>min(upperx1 , upperx2);
    

    T lowery1 = min(y1,y2);
    T lowery2 = min(y3,y4);
    T uppery1 = max(y1,y2);
    T uppery2 = max(y3,y4);


    bool y_condition = max(lowery1 , lowery2)>min(uppery1 , uppery2);   

    if(x_condition or y_condition) return false;

    T zero = static_cast<T>(0);

    Vector<T>v12 = Vector(x2-x1,y2-y1,zero);  // b menos a 
    Vector<T>v13 = Vector(x3-x1,y3-y1,zero); // c menos a 
    Vector<T>v14 = Vector(x4-x1,y4-y1,zero); // d menos a
    

    bool der_v12_v13 = v12.cross_product(v13).z_ >= zero;
    bool der_v12_v14 = v12.cross_product(v14).z_ >= zero;
    bool different_dir = my_xor(der_v12_v13 , der_v12_v14);

    int sgn1 = sgn<T>(v12.cross_product(v13).z_);
    int sgn2 =sgn<T>(v13.cross_product(v14).z_);

    if(sgn1 ==0 and sgn2 == 0) return true;


    Vector<T>v31 = Vector(x1-x3,y1-y3,zero);
    Vector<T>v32 = Vector(x2-x3,y2-y3,zero);
    Vector<T>v34 = Vector(x4-x3,y4-y3,zero);

    bool der_v34_v31 = v34.cross_product(v31).z_ >= zero;
    bool der_v34_v32 = v34.cross_product(v32).z_ >= zero;
    bool different_dir_v34 = my_xor(der_v34_v31 , der_v34_v32);

    return different_dir or different_dir_v34;

}

template <typename T>
class Segment {
public:
    Vector<T> init_;
    Vector<T> fin_;
    int id_;  
    static T current_x;  

    Segment() : init_(Vector<T>(0, 0, 0)), fin_(Vector<T>(0, 0, 0)), id_(-1) {}

    Segment(const Vector<T>& init, const Vector<T>& fin, int id = -1) 
        : init_(init), fin_(fin), id_(id) {}

    Segment(T x1, T y1, T x2, T y2, int id = -1) 
        : init_(x1, y1, static_cast<T>(0)), 
          fin_(x2, y2, static_cast<T>(0)), 
          id_(id) {}

    T get_y_at(T x) const {
        if (init_.x_ == fin_.x_) return init_.y_;
        T t = (x - init_.x_) / (fin_.x_ - init_.x_);
        return init_.y_ + t * (fin_.y_ - init_.y_);
    }

    bool operator<(const Segment& other) const {   
        T y1 = this->get_y_at(current_x);
        T y2 = other.get_y_at(current_x);
        if (y1 != y2) return y1 < y2;
        return id_ < other.id_; 
    }

    bool intersects_with(const Segment<T>& other) const {
        return intersection(init_.x_, init_.y_, fin_.x_, fin_.y_,
                            other.init_.x_, other.init_.y_, other.fin_.x_, other.fin_.y_);
    }

    void print() const {
        cout << "Segment " << id_ << ": (" << init_.x_ << "," << init_.y_ << ") -> (" 
             << fin_.x_ << "," << fin_.y_ << ")" << endl;
    }
};

template <typename T>
struct Event {
    T x, y;
    bool is_left;  
    int segment_id;
    
    Event(T x, T y, bool is_left, int seg_id) : x(x), y(y), is_left(is_left), segment_id(seg_id) {}
    
   
    bool operator<(const Event& other) const {
        if (x != other.x) return x < other.x;
        if (is_left != other.is_left) return is_left > other.is_left; 
        return y < other.y;
    }
};

template <typename T>
vector<Segment<T>> create_segments_from_coords(const vector<vector<T>>& coords) {
    vector<Segment<T>> segments;
    for (int i = 0; i < coords.size(); i++) {
        if (coords[i].size() >= 4) {
            segments.emplace_back(coords[i][0], coords[i][1], coords[i][2], coords[i][3], i);
        }
    }
    return segments;
}


template <typename T>
T Segment<T>::current_x = 0;

template <typename T>
bool exist_intersections(const vector<vector<T>>& seg) {
    if (seg.size() < 2) return false;
    
    vector<Segment<T>> segments = create_segments_from_coords(seg);

    vector<Event<T>> events;
    for (int i = 0; i < segments.size(); i++) {
        const auto& s = segments[i];
        T x1 = s.init_.x_, x2 = s.fin_.x_;
        T y1 = s.init_.y_, y2 = s.fin_.y_;
        
        if (x1 > x2 or (x1 == x2 and y1 > y2)) {
            swap(x1, x2);
            swap(y1, y2);
        }
        
        events.emplace_back(x1, y1, true, i);   
        events.emplace_back(x2, y2, false, i);  
    }
    
    sort(events.begin(), events.end());
    
   
    set<Segment<T>> active_segments;
    Segment<T>::current_x = events.empty() ? 0 : events[0].x;
    
    for (const auto& event : events) {
        Segment<T>::current_x = event.x;
        auto& current_seg = segments[event.segment_id];
        
        if (event.is_left) {
            auto ret = active_segments.insert(current_seg);
            auto it = ret.first;
            
          
            if (it != active_segments.begin()) {
                auto below = prev(it);
                if (current_seg.intersects_with(*below)) return true;
            }
            
           
            if (next(it) != active_segments.end()) {
                auto above = next(it);
                if (current_seg.intersects_with(*above)) return true;
            }
        } else {
            auto it = active_segments.find(current_seg);
            if (it == active_segments.end()) continue;
            
          
            if (it != active_segments.begin() && next(it) != active_segments.end()) {
                auto below = prev(it);
                auto above = next(it);
                if (below->intersects_with(*above)) return true;
            }
            active_segments.erase(it);
        }
    }
    
    return false;
}



TEST(SegmentIntersectionTest, BasicIntersection) {
  vector<vector<int>> segments = {{0, 0, 10, 10}, {0, 10, 10, 0}};
  EXPECT_TRUE(exist_intersections(segments));
}

TEST(SegmentIntersectionTest, NoIntersection) {
  vector<vector<int>> segments = {{0, 0, 5, 5}, {6, 6, 10, 10}};
  EXPECT_FALSE(exist_intersections(segments));
}

TEST(SegmentIntersectionTest, SharedEndpoint) {
  vector<vector<int>> segments = {{0, 0, 5, 5}, {5, 5, 10, 0}};
  EXPECT_TRUE(exist_intersections(segments));
}

TEST(SegmentIntersectionTest, CollinearOverlap) {
  vector<vector<int>> segments = {{0, 0, 10, 10}, {5, 5, 15, 15}};
  EXPECT_TRUE(exist_intersections(segments));
}

TEST(SegmentIntersectionTest, CollinearNoOverlap) {
  vector<vector<int>> segments = {{0, 0, 5, 5}, {6, 6, 10, 10}};
  EXPECT_FALSE(exist_intersections(segments));
}

TEST(SegmentIntersectionTest, PointSegment) {
  vector<vector<int>> segments = {{5, 5, 5, 5}, {0, 0, 10, 10}};
  EXPECT_TRUE(exist_intersections(segments));
}

TEST(SegmentIntersectionTest, ParallelSegments) {
  vector<vector<int>> segments = {{0, 0, 10, 10}, {0, 5, 10, 15}};
  EXPECT_FALSE(exist_intersections(segments));
}

TEST(SegmentIntersectionTest, AlmostIntersect) {
  vector<vector<double>> segments = {{0.0, 0.0, 10.0, 10.0},
                                     {0.0, 10.0, 9.999, 0.001}};
  EXPECT_TRUE(exist_intersections(segments));
}

TEST(SegmentIntersectionTest, VerticalHorizontal) {
  vector<vector<int>> segments = {{5, 0, 5, 10}, {0, 5, 10, 5}};
  EXPECT_TRUE(exist_intersections(segments));
}

TEST(SegmentIntersectionTest, ManySegmentsSingleIntersection) {
  vector<vector<int>> segments = {{0, 0, 5, 5},   {10, 10, 15, 15},
                                  {20, 0, 25, 5}, {30, 30, 35, 35},
                                  {0, 30, 30, 0}, {0, 0, 30, 30}};
  EXPECT_TRUE(exist_intersections(segments));
}

TEST(SegmentIntersectionTest, ManySegmentsNoIntersection) {
  vector<vector<int>> segments = {{0, 0, 5, 5},     {10, 10, 15, 15},
                                  {20, 20, 25, 25}, {30, 30, 35, 35},
                                  {40, 40, 45, 45}, {50, 50, 55, 55}};
  EXPECT_FALSE(exist_intersections(segments));
}

TEST(SegmentIntersectionTest, BoundaryIntersection) {
  vector<vector<int>> segments = {{0, 0, 10, 10}, {10, 0, 0, 10}};
  EXPECT_TRUE(exist_intersections(segments));
}

TEST(SegmentIntersectionTest, NegativeCoordinates) {
  vector<vector<int>> segments = {{-10, -10, 10, 10}, {-10, 10, 10, -10}};
  EXPECT_TRUE(exist_intersections(segments));
}

TEST(SegmentIntersectionTest, LargeCoordinates) {
  vector<vector<int>> segments = {
      {INT_MAX - 100, INT_MAX - 100, INT_MAX, INT_MAX},
      {INT_MAX - 100, INT_MAX, INT_MAX, INT_MAX - 100}};
  EXPECT_TRUE(exist_intersections(segments));
}

TEST(SegmentIntersectionTest, EmptyInput) {
  vector<vector<int>> segments;
  EXPECT_FALSE(exist_intersections(segments));
}

TEST(SegmentIntersectionTest, SingleSegment) {
  vector<vector<int>> segments = {{0, 0, 10, 10}};
  EXPECT_FALSE(exist_intersections(segments));
}

TEST(SegmentIntersectionTest, TriangleIntersection) {
  vector<vector<int>> segments = {{0, 0, 10, 0}, {10, 0, 5, 10}, {5, 10, 0, 0}};
  EXPECT_TRUE(exist_intersections(segments));
}

TEST(SegmentIntersectionTest, ComplexIntersections) {
  vector<vector<int>> segments = {
      {0, 0, 20, 20}, {0, 20, 20, 0}, {10, 0, 10, 20}, {0, 10, 20, 10}};
  EXPECT_TRUE(exist_intersections(segments));
}

TEST(SegmentIntersectionTest, SameEndpoint) {
  vector<vector<int>> segments = {{0, 0, 10, 10}, {10, 10, 20, 0}};
  EXPECT_TRUE(exist_intersections(segments));
}

TEST(SegmentIntersectionTest, SameStartpoint) {
  vector<vector<int>> segments = {{0, 0, 10, 10}, {0, 0, 10, 0}};
  EXPECT_TRUE(exist_intersections(segments));
}

TEST(SegmentIntersectionTest, HorizontalNoIntersect) {
  vector<vector<int>> segments = {{0, 0, 10, 0}, {0, 5, 10, 5}};
  EXPECT_FALSE(exist_intersections(segments));
}

TEST(SegmentIntersectionTest, VerticalNoIntersect) {
  vector<vector<int>> segments = {{0, 0, 0, 10}, {5, 0, 5, 10}};
  EXPECT_FALSE(exist_intersections(segments));
}

TEST(SegmentIntersectionTest, RandomSegments) {
  vector<vector<int>> segments = {
      {1, 3, 5, 9}, {2, 8, 7, 2}, {3, 4, 9, 4}, {5, 1, 10, 6}, {8, 5, 12, 1}};
  EXPECT_TRUE(exist_intersections(segments));
}

TEST(SegmentIntersectionTest, CrossingXAxis) {
  vector<vector<int>> segments = {{-5, -5, 5, 5}, {-5, 5, 5, -5}};
  EXPECT_TRUE(exist_intersections(segments));
}

TEST(SegmentIntersectionTest, TangentSegments) {
  vector<vector<int>> segments = {{0, 0, 10, 10}, {10, 10, 20, 0}};
  EXPECT_TRUE(exist_intersections(segments));
}

TEST(SegmentIntersectionTest, PerpendicularSegments) {
  vector<vector<int>> segments = {{0, 5, 10, 5}, {5, 0, 5, 10}};
  EXPECT_TRUE(exist_intersections(segments));
}

int main() {
    
    
  
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}