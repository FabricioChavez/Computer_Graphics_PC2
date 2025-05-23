#include <iostream>
#include <climits>
#include <vector>
#include <unordered_set>
#include <cmath>
#include <gtest/gtest.h>
#include <stack>
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
    

    Vector() {
        if constexpr(is_same<int, T>::value) {
            is_int = true;
        } else is_int = false;
    }



    Vector(T x, T y, T z) : x_(x), y_(y), z_(z) {
        if constexpr(is_same<int, T>::value) {
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
            return T(a + b + c);
        }

        ld a = (ld)other.x_ * (ld)x_;
        ld b = (ld)other.y_ * (ld)y_;
        ld c = (ld)other.z_ * (ld)z_;
        return T(a + b + c);
    }

    

    Vector<T> cross_product(const Vector<T>& other) const {
        if (is_int) {
            ll x = (ll)y_ * (ll)other.z_ - (ll)z_ * (ll)other.y_;
            ll y = (ll)x_ * (ll)other.z_ - (ll)z_ * (ll)other.x_;
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

           // cout << "MY X EN RESTA " << x << endl;

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

    T x_;
    T y_;
    T z_;

    void print() {
        cout << "X :" << x_ << endl;
        cout << "Y :" << y_ << endl;
        cout << "Z :" << z_ << endl;
    }
};
bool my_xor(int a , int     b){
    return a!=b;
}



template<typename T>
bool line_segment_insertection( Vector<T> P, // punto de paso de recta
     Vector<T> Dir , // vector director
     Vector<T> PA , Vector<T> PB , bool is_positive){ // segmento 
    bool can_cross = true ;    
    T zero = static_cast<T>(0);
    auto dirP_to_PA = PA-P;
    auto dirP_to_PB = PB-P;
    auto above_line = (max(PB.y_ , PA.y_)==PB.y_)?dirP_to_PB:dirP_to_PA;
    auto below_line = (min(PB.y_ , PA.y_)==PB.y_)?dirP_to_PB:dirP_to_PA;
    int sgnA = sgn<T>(Dir.cross_product(dirP_to_PA).z_);
    int sgnB = sgn<T>(Dir.cross_product(dirP_to_PB).z_);
    int sgnC = sgn<T>(above_line.cross_product(below_line).z_);
    if(is_positive) can_cross = sgnC == -1;   
    else can_cross = sgnC == 1; 

    if(my_xor(sgnA , sgnB) and sgnA !=zero and sgnB!=zero) return true and can_cross;
    else if(sgnA== zero and sgnB > zero) return true and can_cross;
    else if(sgnB==zero  and sgnA > zero ) return true and can_cross;
    return false;
}


template <typename T>
bool inside_polygon(vector<vector<T>> const& v, T px, T py){
    T zero = static_cast<T> (0);
    T one = static_cast<T> (1);
    T negative_one = static_cast<T> (-1);
    Vector<T> p_test(px , py  , zero);
    Vector<T> dir( one, zero,zero);
    Vector<T> dir_n (negative_one , zero , zero );
    vector<vector<T>> vertices = v;
    vertices.push_back(vertices[0]);
    int  n  = vertices.size();
    int cnt_right = 0;
    int cnt_left = 0;    
    for (int i=1;i< n; i++){
        
        Vector<T> Pa(vertices[i-1][0] , vertices[i-1][1] , zero );
        Vector<T> Pb(vertices[i][0], vertices[i][1],zero);
        if(p_test == Pa  or p_test == Pb) return true; 
        if(line_segment_insertection<T>( p_test , dir ,Pa  , Pb , true)) cnt_right++;
        if(line_segment_insertection<T>(p_test  , dir_n , Pa , Pb, false)) cnt_left++;
     
    }
    if(cnt_left%2 == 1 and cnt_right%2==1 ) return true;
    else if ((cnt_left+cnt_right)%2==1) return true;
    return false;

}

template <typename T> 
vector<vector<T>> interior_points_removal(vector<vector<T>> const& vertices) {
    vector<vector<T>> with_points_removed;
    int n = vertices.size();
    
    int north = 0, south = 0, east = 0, west = 0;
    int ne = 0, nw = 0, se = 0, sw = 0;
    
    for (int i = 1; i < n; i++) {
        if (vertices[i][1] > vertices[north][1])
            north = i;
        if (vertices[i][1] < vertices[south][1])
            south = i;
        if (vertices[i][0] > vertices[east][0])
            east = i;
        if (vertices[i][0] < vertices[west][0])
            west = i;
        if (vertices[i][0] + vertices[i][1] > vertices[ne][0] + vertices[ne][1])
            ne = i;
        if (-vertices[i][0] + vertices[i][1] > -vertices[nw][0] + vertices[nw][1])
            nw = i;
        if (vertices[i][0] - vertices[i][1] > vertices[se][0] - vertices[se][1])
            se = i;
        if (-vertices[i][0] - vertices[i][1] > -vertices[sw][0] - vertices[sw][1])
            sw = i;
    }
    
   
    vector<int> octagon_indices = {south, se, east, ne, north, nw, west, sw};
    
    
    vector<int> unique_indices;
    for (int idx : octagon_indices) {
       
        if (find(unique_indices.begin(), unique_indices.end(), idx) == unique_indices.end()) {
            unique_indices.push_back(idx);
        }
    }
    
    
    vector<vector<T>> filter_octagon;
    for (int idx : unique_indices) {
        filter_octagon.push_back(vertices[idx]);
    }
    
    cout << "LOS DEL OCTAGON FILTRADO" << endl;
    for (auto oct : filter_octagon) {
        cout << oct[0] << " " << oct[1] << endl;
    }
    
    
    for (int i = 0; i < n; i++) {
        if (!inside_polygon(filter_octagon, vertices[i][0], vertices[i][1])) {
            with_points_removed.push_back(vertices[i]);
        }
    }

    for (auto octa_point : filter_octagon){
        with_points_removed.push_back(octa_point);
    }
    

    


    cout<<"PART OF FILTER OCTAGON"<<endl;
    if (!with_points_removed.empty()) {
        cout << with_points_removed[0][0] << " " << with_points_removed[0][1] << endl;
    }
    
    return with_points_removed;
}


template<typename T>
Vector<T> min_y(vector<vector<T>> v){
    T y_min = v[0][1];
    
   
    for (int i = 1; i < v.size(); i++) {
        if(v[i][1] < y_min) {
            y_min = v[i][1];
        }
    }
    
  
    vector<vector<T>> partial_ans;
    for (int i = 0; i < v.size(); i++) {
        if(v[i][1] == y_min) {
            partial_ans.push_back(v[i]);
        }
    }
    
    
    T x_min = partial_ans[0][0];
    int idx = 0;
    
    for (int i = 1; i < partial_ans.size(); i++) {
        if(partial_ans[i][0] < x_min) {
            x_min = partial_ans[i][0];
            idx = i;
        }
    }
    
    T zero = static_cast<T>(0);
    
    return Vector<T>(partial_ans[idx][0], partial_ans[idx][1], zero);
}



// ejecuta jarvis, con o sin elinminación de puntos interiors (especificado vía un parametro)
template <typename T>
vector<vector<T>> jarvis(vector<vector<T>> const& vertices, 
    bool withInteriorPointsRemoval){

    vector<vector<T>> to_work_with = (withInteriorPointsRemoval)?interior_points_removal(vertices):vertices;
    
    T zero = static_cast<T>(0);
    vector<Vector<T>> ans;
    vector<vector<T>> ans_t;

    auto pivot_y = min_y(to_work_with);
    
    int pivot_idx = 0;
    for(int i = 0; i < to_work_with.size(); i++){
        if(to_work_with[i][0] == pivot_y.x_ && to_work_with[i][1] == pivot_y.y_){
            pivot_idx = i;
            break;
        }
    }

    ans.push_back(pivot_y);
    ans_t.push_back(vector<T>{pivot_y.x_, pivot_y.y_});
    
    int n = to_work_with.size();
    int current_idx = pivot_idx;
    bool finished = false;
    
    while (!finished) {
        int idx_temp = -1;
        Vector<T> current_most_counter_clock;
        bool first_candidate = true;
        
        for (int j = 0; j < n; j++) {
            if(j == current_idx) continue;
            
            Vector<T> candidate_min = Vector<T>(to_work_with[j][0], to_work_with[j][1], zero) - Vector<T>(ans.back().x_, ans.back().y_, zero);
            
            if(first_candidate) {
                current_most_counter_clock = candidate_min;
                idx_temp = j;
                first_candidate = false;
                continue;
            }
            
            int sign = sgn<T>(current_most_counter_clock.cross_product(candidate_min).z_);

            if(sign == 0){
                current_most_counter_clock = (candidate_min.norm() > current_most_counter_clock.norm()) ? 
                                           candidate_min : current_most_counter_clock;
                if(candidate_min.norm() > current_most_counter_clock.norm()) idx_temp = j;
            } else if(sign < 0){
                current_most_counter_clock = candidate_min;
                idx_temp = j;
            }
        }
        
        if(idx_temp != -1 && idx_temp != pivot_idx) {
            ans.push_back(Vector<T>(to_work_with[idx_temp][0], to_work_with[idx_temp][1], zero));
            ans_t.push_back(to_work_with[idx_temp]);
            current_idx = idx_temp;
        } else {
            finished = true;
        }
    }
    
    return ans_t;
}

// ejecuta graham, con o sin elinminación de puntos interiors (especificado vía un parametro)
template <typename T>
vector<vector<T>> graham(vector<vector<T>> const& vertices, 
    bool withInteriorPointsRemoval){
    vector<vector<T>> to_work_with = (withInteriorPointsRemoval)?interior_points_removal(vertices):vertices;
    T zero = static_cast<T>(0);
    
    Vector<T> pivot = min_y(to_work_with);
    
    sort(to_work_with.begin(), to_work_with.end(), [&pivot, &zero](vector<T> a, vector<T> b){
        Vector<T> A(a[0], a[1], zero);
        Vector<T> B(b[0], b[1], zero);
        
        Vector<T> PA = A - pivot;
        Vector<T> PB = B - pivot;
        int s = sgn<T>(PA.cross_product(PB).z_);
        
        if(s == 0){
            return PA.norm() < PB.norm();
        }
        
        return s == 1;
    });
    
    int n = to_work_with.size();
    Vector<T> p0(to_work_with[0][0], to_work_with[0][1], zero);
    Vector<T> p1(to_work_with[1][0], to_work_with[1][1], zero);
    Vector<T> p2(to_work_with[2][0], to_work_with[2][1], zero);
    stack<Vector<T>> cstack;
    cstack.push(p0);
    cstack.push(p1);
    cstack.push(p2);
    
    cout << "LLEGA HASTA ACA??" << endl;
    
    for (int i = 3; i < n; i++)
    {
        Vector<T> current_front(to_work_with[i][0], to_work_with[i][1], zero);
        
        while(cstack.size() >= 2) {
            Vector<T> top = cstack.top();
            cstack.pop();
            Vector<T> next_to_top = cstack.top();
            
            Vector<T> vec1 = top - next_to_top;
            Vector<T> vec2 = current_front - top;
            
            if(sgn<T>(vec1.cross_product(vec2).z_) <= 0) {
                continue;
            } else {
                cstack.push(top);
                break;
            }
        }
        
        cstack.push(current_front);
    }
    
    vector<vector<T>> ans;
    
    while(!cstack.empty()){
        Vector<T> point = cstack.top();
        vector<T> fpoint = {point.x_, point.y_};
        ans.push_back(fpoint);
        cstack.pop();
    }
    
    reverse(ans.begin(), ans.end());
    return ans;
} 


TEST(GrahamDouble, polygonGrahamA) {
    // Datos de entrada basados en tu imagen
    std::vector<std::vector<double>> points = {
        {-10.07, 1.87},  // A
        {-6.51, 5.17},   // B
        {-6.01, 2.31},   // C
        {-3.09, 3.35},   // D
        {-1.41, 4.55},   // E
        {-1.79, 1.97},   // F
        {-6.47, 0.13},   // G
        {-5.63, -2.11},  // H
        {1.49, -2.65},   // I   
        {-1.61, -3.63},  // J
        {6.63, -4.09},   // K
        {6.61, -2.07},   // L
        {7.35, 2.57},    // M
        {3.45, 3.65},    // N
        {1.33, 2.47},    // O
        {1.47, 4.79},    // P
        {-3.07, 6.73},   // Q
        {4.21, 6.25},    // R
        {-7, -4},        // S
        {1.25, -6.15}    // T
    };
    
    // Convex hull esperado basado en la imagen (en orden counterclockwise)
    std::vector<std::vector<double>> expected_hull = {
        {1.25, -6.15},   // T (punto más bajo)
        {6.63, -4.09},   // K
        {7.35, 2.57},    // M
        {4.21, 6.25},    // R
        {-3.07, 6.73},   // Q
        {-6.51, 5.17},   // B
        {-10.07, 1.87},  // A
        {-7, -4}         // S
    };
    cout<<"HAGAMOS TEST GRAHAM A"<<endl;
    // Ejecutar Jarvis March
    auto result = graham<double>(points, true);

    for (auto v:result)
    {
        cout<<v[0]<<" "<<v[1]<<endl;
    }   
    
    
    // OPCIÓN 1: Comparación exacta con EXPECT_EQ
    EXPECT_EQ(expected_hull.size(), result.size()) << "Hull size mismatch";
    
    for (size_t i = 0; i < expected_hull.size() && i < result.size(); i++) {
        EXPECT_EQ(expected_hull[i].size(), result[i].size()) << "Point " << i << " dimension mismatch";
        for (size_t j = 0; j < expected_hull[i].size() && j < result[i].size(); j++) {
            EXPECT_NEAR(expected_hull[i][j], result[i][j], 1e-6) 
                << "Point " << i << " coordinate " << j << " mismatch";
        }
    }
}



TEST(GrahamDouble, polygonGrahamB) {
    // Datos de entrada basados en tu imagen
    std::vector<std::vector<double>> points = {
        {-10.07, 1.87},  // A
        {-6.51, 5.17},   // B
        {-6.01, 2.31},   // C
        {-3.09, 3.35},   // D
        {-1.41, 4.55},   // E
        {-1.79, 1.97},   // F
        {-6.47, 0.13},   // G
        {-5.63, -2.11},  // H
        {1.49, -2.65},   // I
        {-1.61, -3.63},  // J
        {6.63, -4.09},   // K
        {6.61, -2.07},   // L
        {7.35, 2.57},    // M
        {3.45, 3.65},    // N
        {1.33, 2.47},    // O
        {1.47, 4.79},    // P
        {-3.07, 6.73},   // Q
        {4.21, 6.25},    // R
        {-7, -4},        // S
        {1.25, -6.15},    // T
        {-4 , -6}        // U
    };
    
    // Convex hull esperado basado en la imagen (en orden counterclockwise)
    std::vector<std::vector<double>> expected_hull = {
        {1.25, -6.15},   // T (punto más bajo)
        {6.63, -4.09},   // K
        {7.35, 2.57},    // M
        {4.21, 6.25},    // R
        {-3.07, 6.73},   // Q
        {-6.51, 5.17},   // B
        {-10.07, 1.87},  // A
        {-7, -4},         // S
         {-4 , -6}        // U
    };
    

    // Ejecutar Jarvis March
    auto result = graham<double>(points, true);

    for (auto v:result)
    {
        cout<<v[0]<<" "<<v[1]<<endl;
    }   
    
    
    // OPCIÓN 1: Comparación exacta con EXPECT_EQ
    EXPECT_EQ(expected_hull.size(), result.size()) << "Hull size mismatch";
    
    for (size_t i = 0; i < expected_hull.size() && i < result.size(); i++) {
        EXPECT_EQ(expected_hull[i].size(), result[i].size()) << "Point " << i << " dimension mismatch";
        for (size_t j = 0; j < expected_hull[i].size() && j < result[i].size(); j++) {
            EXPECT_NEAR(expected_hull[i][j], result[i][j], 1e-6) 
                << "Point " << i << " coordinate " << j << " mismatch";
        }
    }
}

TEST(GrahamDouble, PolygonGrahamC) {
    std::vector<std::vector<double>> points = {
        {-8, 6},    // A
        {-4, 6},    // B
        {0, 6},     // C
        {2, 6},     // D
        {4, 6},     // E
        {6, 6},     // F
        {8, 6},     // G
        {8, 4},     // H
        {8, 2},     // I
        {8, 0},     // J
        {8, -2},    // K
        {8, -4},    // L
        {4, -4},    // M
        {0, -4},    // N
        {-2, -4},   // O
        {-4, -4},   // P
        {-6, -4},   // Q
        {-8, -4},   // R
        {-8, -2},   // S
        {-8, 0},    // T
        {-8, 2}     // U
    };
    
    std::vector<std::vector<double>> expected_hull = {
        {-8, -4},   // R (punto más bajo-izquierdo)
        {8, -4},    // L (más a la derecha en y=-4)
        {8, 6},     // G (esquina superior derecha)
        {-8, 6}     // A (esquina superior izquierda)
    };
    
  
     
    auto result = graham<double>(points, true);

    for (auto v:result)
    {
        cout<<v[0]<<" "<<v[1]<<endl;
    }  
    
    EXPECT_EQ(expected_hull.size(), result.size()) << "Hull size mismatch";
    
    for (size_t i = 0; i < expected_hull.size() && i < result.size(); i++) {
        EXPECT_EQ(expected_hull[i].size(), result[i].size()) << "Point " << i << " dimension mismatch";
        for (size_t j = 0; j < expected_hull[i].size() && j < result[i].size(); j++) {
            EXPECT_NEAR(expected_hull[i][j], result[i][j], 1e-6) 
                << "Point " << i << " coordinate " << j << " mismatch";
        }
    }
}



TEST(GrahamDouble, CircleAllPointsInHull) {
    std::vector<std::vector<double>> points = {
        {-2.47, 1.7},   // B
        {-2.94, 0.59},  // C
        {-2.94, -0.61}, // D
        {-2.46, -1.72}, // E
        {-1.78, -2.42}, // F
        {-0.94, -2.85}, // G
        {0, -3},        // H (punto más bajo - empezará aquí)
        {0.95, -2.84},  // I
        {2.11, -2.13},  // J
        {-0.38, -2.98}, // K
        {2.88, -0.85},  // L
        {2.98, 0.32},   // M
        {2.98, -0.37},  // N
        {2.15, 2.09},   // O
        {1.16, 2.77},   // P
        {0.22, 2.99},   // Q
        {0, 3},         // R
        {-1.15, 2.77},  // S
        {-1.53, 2.58}   // T
    };
    
    // Convex hull esperado - todos los puntos en orden counterclockwise empezando desde H
    std::vector<std::vector<double>> expected_hull = {
        {0, -3},        // H (punto de inicio - más bajo)
        {0.95, -2.84},  // I
        {2.11, -2.13},  // J
        {2.88, -0.85},  // L
        {2.98, -0.37},  // N
        {2.98, 0.32},   // M
        {2.15, 2.09},   // O
        {1.16, 2.77},   // P
        {0.22, 2.99},   // Q
        {0, 3},         // R
        {-1.15, 2.77},  // S
        {-1.53, 2.58},  // T
        {-2.47, 1.7},   // B
        {-2.94, 0.59},  // C
        {-2.94, -0.61}, // D
        {-2.46, -1.72}, // E
        {-1.78, -2.42}, // F
        {-0.94, -2.85}, // G
        {-0.38, -2.98}  // K
    };
    
    auto result = graham<double>(points, true);
    
    for (auto v : result) {
        cout << v[0] << " " << v[1] << endl;
    }
    
    EXPECT_EQ(expected_hull.size(), result.size()) << "Hull size mismatch";
    
    for (size_t i = 0; i < expected_hull.size() && i < result.size(); i++) {
        EXPECT_EQ(expected_hull[i].size(), result[i].size()) << "Point " << i << " dimension mismatch";
        for (size_t j = 0; j < expected_hull[i].size() && j < result[i].size(); j++) {
            EXPECT_NEAR(expected_hull[i][j], result[i][j], 1e-6) 
                << "Point " << i << " coordinate " << j << " mismatch";
        }
    }
}


TEST(GrahamDouble, ParabolaAllPointsInHull) {
    std::vector<std::vector<double>> points = {
        {-5.76, 8.3},   // D
        {-5.44, 7.4},   // E
        {-5.06, 6.39},  // F
        {-4.38, 4.79},  // G
        {-3.73, 3.47},  // H
        {-2.86, 2.05},  // I
        {-1.39, 0.48},  // J
        {0, 0},         // K (vértice de la parábola - punto más bajo)
        {1.42, 0.51},   // L
        {2.49, 1.55},   // M
        {3.43, 2.93},   // N
        {4.24, 4.49},   // O
        {5.03, 6.33},   // P
        {5.64, 7.95}    // Q
    };
    
    // Convex hull esperado - todos los puntos en orden counterclockwise
    // Empezando desde K (punto más bajo) y siguiendo la parábola
    std::vector<std::vector<double>> expected_hull = {
        {0, 0},         // K (punto de inicio - vértice más bajo)
        {1.42, 0.51},   // L
        {2.49, 1.55},   // M
        {3.43, 2.93},   // N
        {4.24, 4.49},   // O
        {5.03, 6.33},   // P
        {5.64, 7.95},   // Q
        {-5.76, 8.3},   // D
        {-5.44, 7.4},   // E
        {-5.06, 6.39},  // F
        {-4.38, 4.79},  // G
        {-3.73, 3.47},  // H
        {-2.86, 2.05},  // I
        {-1.39, 0.48}   // J
    };
    
    auto result = graham<double>(points, true);
    
    for (auto v : result) {
        cout << v[0] << " " << v[1] << endl;
    }
    
    EXPECT_EQ(expected_hull.size(), result.size()) << "Hull size mismatch";
    
    for (size_t i = 0; i < expected_hull.size() && i < result.size(); i++) {
        EXPECT_EQ(expected_hull[i].size(), result[i].size()) << "Point " << i << " dimension mismatch";
        for (size_t j = 0; j < expected_hull[i].size() && j < result[i].size(); j++) {
            EXPECT_NEAR(expected_hull[i][j], result[i][j], 1e-6) 
                << "Point " << i << " coordinate " << j << " mismatch";
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(JarvisDouble, polygonA) {
    // Datos de entrada basados en tu imagen
    std::vector<std::vector<double>> points = {
        {-10.07, 1.87},  // A
        {-6.51, 5.17},   // B
        {-6.01, 2.31},   // C
        {-3.09, 3.35},   // D
        {-1.41, 4.55},   // E
        {-1.79, 1.97},   // F
        {-6.47, 0.13},   // G
        {-5.63, -2.11},  // H
        {1.49, -2.65},   // I
        {-1.61, -3.63},  // J
        {6.63, -4.09},   // K
        {6.61, -2.07},   // L
        {7.35, 2.57},    // M
        {3.45, 3.65},    // N
        {1.33, 2.47},    // O
        {1.47, 4.79},    // P
        {-3.07, 6.73},   // Q
        {4.21, 6.25},    // R
        {-7, -4},        // S
        {1.25, -6.15}    // T
    };
    
    // Convex hull esperado basado en la imagen (en orden counterclockwise)
    std::vector<std::vector<double>> expected_hull = {
        {1.25, -6.15},   // T (punto más bajo)
        {6.63, -4.09},   // K
        {7.35, 2.57},    // M
        {4.21, 6.25},    // R
        {-3.07, 6.73},   // Q
        {-6.51, 5.17},   // B
        {-10.07, 1.87},  // A
        {-7, -4}         // S
    };
    
    // Ejecutar Jarvis March
    auto result = jarvis<double>(points, true);

    for (auto v:result)
    {
        cout<<v[0]<<" "<<v[1]<<endl;
    }   
    
    
    // OPCIÓN 1: Comparación exacta con EXPECT_EQ
    EXPECT_EQ(expected_hull.size(), result.size()) << "Hull size mismatch";
    
    for (size_t i = 0; i < expected_hull.size() && i < result.size(); i++) {
        EXPECT_EQ(expected_hull[i].size(), result[i].size()) << "Point " << i << " dimension mismatch";
        for (size_t j = 0; j < expected_hull[i].size() && j < result[i].size(); j++) {
            EXPECT_NEAR(expected_hull[i][j], result[i][j], 1e-6) 
                << "Point " << i << " coordinate " << j << " mismatch";
        }
    }
}


TEST(JarvisDouble, polygonB) {
    // Datos de entrada basados en tu imagen
    std::vector<std::vector<double>> points = {
        {-10.07, 1.87},  // A
        {-6.51, 5.17},   // B
        {-6.01, 2.31},   // C
        {-3.09, 3.35},   // D
        {-1.41, 4.55},   // E
        {-1.79, 1.97},   // F
        {-6.47, 0.13},   // G
        {-5.63, -2.11},  // H
        {1.49, -2.65},   // I
        {-1.61, -3.63},  // J
        {6.63, -4.09},   // K
        {6.61, -2.07},   // L
        {7.35, 2.57},    // M
        {3.45, 3.65},    // N
        {1.33, 2.47},    // O
        {1.47, 4.79},    // P
        {-3.07, 6.73},   // Q
        {4.21, 6.25},    // R
        {-7, -4},        // S
        {1.25, -6.15},    // T
        {-4 , -6}        // U
    };
    
    // Convex hull esperado basado en la imagen (en orden counterclockwise)
    std::vector<std::vector<double>> expected_hull = {
        {1.25, -6.15},   // T (punto más bajo)
        {6.63, -4.09},   // K
        {7.35, 2.57},    // M
        {4.21, 6.25},    // R
        {-3.07, 6.73},   // Q
        {-6.51, 5.17},   // B
        {-10.07, 1.87},  // A
        {-7, -4},         // S
         {-4 , -6}        // U
    };
    
    // Ejecutar Jarvis March
    auto result = jarvis<double>(points, true);

    for (auto v:result)
    {
        cout<<v[0]<<" "<<v[1]<<endl;
    }   
    
    
    // OPCIÓN 1: Comparación exacta con EXPECT_EQ
    EXPECT_EQ(expected_hull.size(), result.size()) << "Hull size mismatch";
    
    for (size_t i = 0; i < expected_hull.size() && i < result.size(); i++) {
        EXPECT_EQ(expected_hull[i].size(), result[i].size()) << "Point " << i << " dimension mismatch";
        for (size_t j = 0; j < expected_hull[i].size() && j < result[i].size(); j++) {
            EXPECT_NEAR(expected_hull[i][j], result[i][j], 1e-6) 
                << "Point " << i << " coordinate " << j << " mismatch";
        }
    }
}
TEST(JarvisDouble, PolygonC) {
    std::vector<std::vector<double>> points = {
        {-8, 6},    // A
        {-4, 6},    // B
        {0, 6},     // C
        {2, 6},     // D
        {4, 6},     // E
        {6, 6},     // F
        {8, 6},     // G
        {8, 4},     // H
        {8, 2},     // I
        {8, 0},     // J
        {8, -2},    // K
        {8, -4},    // L
        {4, -4},    // M
        {0, -4},    // N
        {-2, -4},   // O
        {-4, -4},   // P
        {-6, -4},   // Q
        {-8, -4},   // R
        {-8, -2},   // S
        {-8, 0},    // T
        {-8, 2}     // U
    };
    
    std::vector<std::vector<double>> expected_hull = {
        {-8, -4},   // R (punto más bajo-izquierdo)
        {8, -4},    // L (más a la derecha en y=-4)
        {8, 6},     // G (esquina superior derecha)
        {-8, 6}     // A (esquina superior izquierda)
    };
    
  
     // Ejecutar Jarvis March
    auto result = jarvis<double>(points, true);

    for (auto v:result)
    {
        cout<<v[0]<<" "<<v[1]<<endl;
    }  
    
    EXPECT_EQ(expected_hull.size(), result.size()) << "Hull size mismatch";
    
    for (size_t i = 0; i < expected_hull.size() && i < result.size(); i++) {
        EXPECT_EQ(expected_hull[i].size(), result[i].size()) << "Point " << i << " dimension mismatch";
        for (size_t j = 0; j < expected_hull[i].size() && j < result[i].size(); j++) {
            EXPECT_NEAR(expected_hull[i][j], result[i][j], 1e-6) 
                << "Point " << i << " coordinate " << j << " mismatch";
        }
    }
}


TEST(JarvisDouble, CircleAllPointsInHull) {
    std::vector<std::vector<double>> points = {
        {-2.47, 1.7},   // B
        {-2.94, 0.59},  // C
        {-2.94, -0.61}, // D
        {-2.46, -1.72}, // E
        {-1.78, -2.42}, // F
        {-0.94, -2.85}, // G
        {0, -3},        // H (punto más bajo - empezará aquí)
        {0.95, -2.84},  // I
        {2.11, -2.13},  // J
        {-0.38, -2.98}, // K
        {2.88, -0.85},  // L
        {2.98, 0.32},   // M
        {2.98, -0.37},  // N
        {2.15, 2.09},   // O
        {1.16, 2.77},   // P
        {0.22, 2.99},   // Q
        {0, 3},         // R
        {-1.15, 2.77},  // S
        {-1.53, 2.58}   // T
    };
    
    // Convex hull esperado - todos los puntos en orden counterclockwise empezando desde H
    std::vector<std::vector<double>> expected_hull = {
        {0, -3},        // H (punto de inicio - más bajo)
        {0.95, -2.84},  // I
        {2.11, -2.13},  // J
        {2.88, -0.85},  // L
        {2.98, -0.37},  // N
        {2.98, 0.32},   // M
        {2.15, 2.09},   // O
        {1.16, 2.77},   // P
        {0.22, 2.99},   // Q
        {0, 3},         // R
        {-1.15, 2.77},  // S
        {-1.53, 2.58},  // T
        {-2.47, 1.7},   // B
        {-2.94, 0.59},  // C
        {-2.94, -0.61}, // D
        {-2.46, -1.72}, // E
        {-1.78, -2.42}, // F
        {-0.94, -2.85}, // G
        {-0.38, -2.98}  // K
    };
    
    auto result = jarvis<double>(points, true);
    
    for (auto v : result) {
        cout << v[0] << " " << v[1] << endl;
    }
    
    EXPECT_EQ(expected_hull.size(), result.size()) << "Hull size mismatch";
    
    for (size_t i = 0; i < expected_hull.size() && i < result.size(); i++) {
        EXPECT_EQ(expected_hull[i].size(), result[i].size()) << "Point " << i << " dimension mismatch";
        for (size_t j = 0; j < expected_hull[i].size() && j < result[i].size(); j++) {
            EXPECT_NEAR(expected_hull[i][j], result[i][j], 1e-6) 
                << "Point " << i << " coordinate " << j << " mismatch";
        }
    }
}


TEST(JarvisDouble, ParabolaAllPointsInHull) {
    std::vector<std::vector<double>> points = {
        {-5.76, 8.3},   // D
        {-5.44, 7.4},   // E
        {-5.06, 6.39},  // F
        {-4.38, 4.79},  // G
        {-3.73, 3.47},  // H
        {-2.86, 2.05},  // I
        {-1.39, 0.48},  // J
        {0, 0},         // K (vértice de la parábola - punto más bajo)
        {1.42, 0.51},   // L
        {2.49, 1.55},   // M
        {3.43, 2.93},   // N
        {4.24, 4.49},   // O
        {5.03, 6.33},   // P
        {5.64, 7.95}    // Q
    };
    
    // Convex hull esperado - todos los puntos en orden counterclockwise
    // Empezando desde K (punto más bajo) y siguiendo la parábola
    std::vector<std::vector<double>> expected_hull = {
        {0, 0},         // K (punto de inicio - vértice más bajo)
        {1.42, 0.51},   // L
        {2.49, 1.55},   // M
        {3.43, 2.93},   // N
        {4.24, 4.49},   // O
        {5.03, 6.33},   // P
        {5.64, 7.95},   // Q
        {-5.76, 8.3},   // D
        {-5.44, 7.4},   // E
        {-5.06, 6.39},  // F
        {-4.38, 4.79},  // G
        {-3.73, 3.47},  // H
        {-2.86, 2.05},  // I
        {-1.39, 0.48}   // J
    };
    
    auto result = jarvis<double>(points, true);
    
    for (auto v : result) {
        cout << v[0] << " " << v[1] << endl;
    }
    
    EXPECT_EQ(expected_hull.size(), result.size()) << "Hull size mismatch";
    
    for (size_t i = 0; i < expected_hull.size() && i < result.size(); i++) {
        EXPECT_EQ(expected_hull[i].size(), result[i].size()) << "Point " << i << " dimension mismatch";
        for (size_t j = 0; j < expected_hull[i].size() && j < result[i].size(); j++) {
            EXPECT_NEAR(expected_hull[i][j], result[i][j], 1e-6) 
                << "Point " << i << " coordinate " << j << " mismatch";
        }
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}    