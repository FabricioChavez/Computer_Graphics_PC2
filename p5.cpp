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


    bool operator==(const Vector<T>&other) const{
        return x_ == other.x_ and y_ == other.y_ and z_ == other.z_ ;
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



template<typename T>
bool line_segment_insertection( Vector<T> P, // punto de paso de recta
     Vector<T> Dir , // vector director
     Vector<T> PA , Vector<T> PB){ // segmento 
     T zero = static_cast<T>(0);


    Vector<T> dirP_to_PA = PA-P;
    Vector<T> dirP_to_PB = PB-P;

    int sgnA = dirP_to_PA.cross_product(Dir);
    int sgnB = dirP_to_PB.cross_product(Dir);

    if(my_xor(sgnA , sgnB)) return true ;
    else if(sgnA>= zero and sgnB > zero) return true;
    else if(sgnB>=0 and sgnA > zero ) return true;
}


template <typename T>
bool insise_polygon(vector<vector<T>> const& vertices, T px, T py){
    T zero = static_cast<T> (0);
    T one = static_cast<T> (0);
    Vector<T> p_test(px , py  , zero);
    Vector<T> dir( one, zero,zero);
    int  n  = vertices.size();
    int cnt = 0;
    for (int i=1;i< n; i++){
        Vector<T> Pa(vertices[i-1][0] , vertices[i-1][1] , zero );
        Vector<T> Pb(vertices[i][0], vertices[i][1],zero);

        if(p_test == Pa  or p_test == Pb) return true;

        if(line_segment_insertection( p_test , dir ,Pa  , Pb , )) cnt++;

    }


    return cnt%2!=0;
    


}



int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}