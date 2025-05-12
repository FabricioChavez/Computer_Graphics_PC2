#include <iostream>
#include <climits>
#include <vector>
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
template <typename  T>
class Vector{
    private:

    bool is_int;

    public:


    Vector(T x, T y, T z):x_(x),y_(y),z_(z) {

        if (is_same<int , T>::value) {
            is_int = true;
        }else is_int = false;

    }

    [[nodiscard]] T dot_product(const Vector<T>&other) const {


        if (is_int) {
            ll a = (ll)other.x_* (ll)x_;
            ll b = (ll)other.y_*(ll)y_;
            ll c = (ll)other.z_*(ll)z_;
            return a + b + c;
        }


            ld a = (ld)other.x_*(ld)x_;
            ld b = (ld)other.y_*(ld)y_;
            ld c = (ld)other.z_*(ld)z_;
            return a + b + c;





    }

    Vector<T>cross_product(const Vector<T>&other) const {
       // return Vector(0,0 ,  x_*other.y_ - y_*other.x_);

        if (is_int) {
            ll x = (ll)y_*(ll)other.z_ - (ll)z_*(ll)other.y_;
            ll y = (ll)x_*(ll)other.z_ - (ll)z_*(ll)other.x_;
            ll z = (ll)x_*(ll)other.y_ - (ll)y_*(ll)other.x_;

            return Vector(x, y, z);
        }
        
            ld x = (ld)y_*(ld)other.z_ - (ld)z_*(ld)other.y_;
            ld y = (ld)z_*(ld)other.x_ - (ld)x_*(ld)other.z_; 
            ld z = (ld)x_*(ld)other.y_ - (ld)y_*(ld)other.x_;

        return Vector(x, y, z);
        
    }

    Vector<T>operator+(const Vector<T>&other) const {
        return Vector(x_ + other.x_, y_ + other.y_, z_ + other.z_);
    }

    Vector<T> operator-(const Vector<T>&other) const{
        return Vector(x_ - other.x_, y_ - other.y_, z_ - other.z_);
    }


    



    T norm() {
        return sqrt(dot_product(*this));
    }
      T x_;
      T y_;
      T z_;



      void print(){
          cout<<"X :"<<x_<<endl;
          cout<<"Y :"<<y_<<endl;
          cout<<"Z :"<<z_<<endl;
      }
};

bool my_xor(bool a , bool b){
    return a!=b;
}
//problema 1
template <typename T>
bool intersection(T x1 , T y1 , T x2 , T y2 , T x3 , T y3  , T x4 , T y4 ) { // P1

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
    bool der_v12_v14 = v13.cross_product(v14).z_ >= zero;
    bool different_dir = my_xor(der_v12_v13 , der_v12_v14);



    Vector<T>v31 = Vector(x1-x3,y1-y3,zero);
    Vector<T>v32 = Vector(x2-x3,y2-y3,zero);
    Vector<T>v34 = Vector(x4-x3,y4-y3,zero);

    bool der_v34_v31 = v34.cross_product(v31).z_ >= zero;
    bool der_v34_v32 = v34.cross_product(v32).z_ >= zero;
    bool different_dir_v34 = my_xor(der_v34_v31 , der_v34_v32);

    return different_dir or different_dir_v34;

}


template<typename T>
bool line_segment_insertection(T px , T py , // punto de paso de recta
     T dirx , T diry , // vector director
     T ax , T ay , T bx , T by){ // segmento 
     T zero = static_cast<T>(0);

    Vector<T> P(px , py , zero );
        



}



template <typename T>
bool insise_triangle(vector<vector<T>> const& vertices, T px, T py){

}



int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}