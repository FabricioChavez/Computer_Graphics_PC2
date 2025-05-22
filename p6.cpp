#include <iostream>
#include <climits>
#include <vector>
#include <unordered_set>
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
    
   
    set<int> extreme_indices = {north, south, east, west, ne, nw, se, sw};
    
   
    vector<vector<T>> octagon;
    for (int idx : extreme_indices) {
        octagon.push_back(vertices[idx]);
    }

    
    for (int i = 0; i < n; i++)
    {
        if(inside_polygon(octagon , vertices[i][0],vertices[i][1]));
            with_points_removed.push_back(vertices[i]);
    }
    
return with_points_removed;
}


template<typename T>
pair<Vector<T>, int> min_y(vector<vector<T>> v){

    T y_min =  v[0][1];
    int idx = -1;

    for (int i = 0; i <  v.size(); i++)
    {
        if(y_min > v[i][1])
        {
            y_min = v[i][1]
            idx = i;
        }
    }    
    
    T zero = static_cast<T>(0);
    
    return make_pair(Vector<T>(v[idx][0], vp[idx][1] ,zero),idx);
}





// ejecuta jarvis, con o sin elinminación de puntos interiors (especificado vía un parametro)
template <typename T>
vector<vector<T>> jarvis(vector<vector<T>> const& vertices, 
    bool withInteriorPointsRemoval){

    vector<vector<T>> to_work_with = (withInteriorPointsRemoval)?interior_points_removal(vertices):vertices;
    
    T zero = static_cast<T> (0);
 
    vector<Vector<T>> ans;

    Vector<T> pivot_y ;

    auto pivot_idx = min_y(to_work_with);
    pivot_y = pivot_y.first;
    int idx = pivot.second;    

    unordered_set<int> used_idx;
    used_idx.insert(idx);     
    ans.push_back(pivot_y);
    


    to_work_with.push_back(to_work_with[0]);

    Vector<T> current_most_counter_clock =  Vector<T>(to_work_with[0][0], to_work_with[0][1], zero ) - pivot_y ;
    
    int n = to_work_with.size();
    for (int i = 0; i < n; i++)
    {    int idx_temp = -1;
        if(i>0)
           {
             current_most_counter_clock = Vector<T>(to_work_with[i][0], to_work_with[i][1] , zero) - Vector<T>(*(ans.back())[0], *(ans.back())[1] , zero) ;
           }
       
        for (int j = 0; j < n; j++)
        {   Vector<T> candidate_min = Vector<T>(to_work_with[j][0], to_work_with[j][1] , zero)-Vector<T>(*(ans.back())[0], *(ans.back())[1] , zero);
            if(used_idx.find(j)==used_idx.end(); and sgn<T>(current_most_counter_clock.cross_product(candidate_min))<0){
                current_most_counter_clock = candidate_min;
            }
        }

        ans.push_back(current_most_counter_clock);
        
    }
    
return ans;

}

// ejecuta graham, con o sin elinminación de puntos interiors (especificado vía un parametro)
template <typename T>
vector<vector<T>> graham(vector<vector<T>> const& vertices, 
    bool withInteriorPointsRemoval){
    vector<vector<T>> to_work_with = (withInteriorPointsRemoval)?interior_points_removal(vertices):vertices;
    T zero = static_cast<T> (0);
    Vector<T> pivot ;
    
    auto pivot_idx= min_y(to_work_with);

    pivot = pivot.first;

    sort(to_work_with.begin() , to_work_with.end() , [&pivot](vector<T> a , vector<T> b){
        Vector<T> A(a[0],a[1],zero);
        Vector<T> B(b[0],b[1],zero);

        Vector<T> PA = A - pivot;
        Vector<T> PB = B - pivot;
        int s = sgn<T>(PA.cross_product(PB).z_);

        if(s==0){
            return PA.norm() < PB.norm();
        }


        return s== 1;
    });
    T zero = static_cast<T> (0);
    int n = to_work_with.size();
    Vector<T> p0 (to_work_with[0][0],to_work_with[0][1],zero);
    Vector<T> p1 (to_work_with[1][0],to_work_with[1][1],zero);
    Vector<T> p2 (to_work_with[2][0],to_work_with[2][1],zero);
    stack<Vector<T>> cstack;
    cstack.push(p0);
    cstack.push(p1);
    cstack.push(p2);
    for (int i = 3; i < n; i++)
    {
        Vector<T> current_front(to_work_with[i][0] , to_work_with[i][1], zero);
        Vector<T> dummy = cstack.top();
        Vector<T> current_vec = current_front - dummy;
        cstack.pop();
        Vector<T> previous_vec = dummy - cstack.top();
        cstack.push(dummy); 
        while(sgn<T>(current_front.cross_product(previous_vec))<0){
            cstack.pop();
            dummy = cstack.top();
            current_vec = current_front - dummy;
            cstack.pop();
            previous_vec = dummy - cstack.top();
            cstack.push(dummy); 
            }

        cstack.push(current_front);    
    }
    

    vector<vector<T>> ans;

    while(!cstack.empty()){
        
        Vector<T> point = cstack.top();
        vector<T> fpoint={point.x_ , point.y_};

        ans.push_back(fpoint);
    }

    reverse(ans.begin() , ans.end());
    return ans;
}   




int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}    