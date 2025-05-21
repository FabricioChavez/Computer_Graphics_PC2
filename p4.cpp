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






template <typename T> 
bool inside_triangle(vector<vector<T>> const& vertices, T px, T py) {
    T zero = static_cast<T>(0);
    Vector<T> p0(vertices[0][0], vertices[0][1], zero);
    Vector<T> p1(vertices[1][0], vertices[1][1], zero);
    Vector<T> p2(vertices[2][0], vertices[2][1], zero);
    Vector<T> p(px, py, zero);
    
   
    Vector<T> a0 = p0 - p; 
    Vector<T> a1 = p1 - p; 
    Vector<T> a2 = p2 - p; 
    
   
    T cp1 = a0.cross_product(a1);
    T cp2 = a1.cross_product(a2);
    T  cp3 = a2.cross_product(a0);
    
    int sgn1 = sgn(cp1.z_); 
    int sgn2 = sgn(cp2.z_);
    int sgn3 = sgn(cp3.z_);
    
 
    if (sgn1 == 0 && sgn2 == 0 && sgn3 == 0) return false;
    
  
    bool inside = (sgn1 >= 0 && sgn2 >= 0 && sgn3 >= 0) || 
                  (sgn1 <= 0 && sgn2 <= 0 && sgn3 <= 0);
                  
    return inside;
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}