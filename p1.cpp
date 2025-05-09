#include <iostream>
#include <gtest/gtest.h>
#define ll long long
#define ld long double
using namespace std;

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
            ld y = (ld)x_*(ld)other.z_ - (ld)z_*(ld)other.x_;
            ld z = (ld)x_*(ld)other.y_ - (ld)y_*(ld)other.x_;

        return Vector(x, y, z);
        
    }

    Vector<T>operator+(const Vector<T>&other) const {
        return Vector(x_ + other.x_, y_ + other.y_, z_ + other.z_);
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


//problema 1
template <typename T>
bool insertects(T x1 , T y1 , T x2 , T y2 , T x3 , T y3  , T x4 , T y4 ) { // P1


    T zero = static_cast<T>(0);



    Vector<T>v12 = Vector(x2-x1,y2-y1,zero);  // b menos a 


    Vector<T>v13 = Vector(x3-x1,y3-y1,zero); // c menos a 
    Vector<T>v14 = Vector(x4-x1,y4-y1,zero); // d menos a
    

    bool der_v12_v13 = v12.cross_product(v13).z_ >= zero;
    cout<<"---------------TEST 1-------------------------"<<endl;
    auto test = v12.cross_product(v13);
    test.print();

    cout<<"test 1----> "<<boolalpha<<der_v12_v13<<endl;

    


    bool der_v12_v14 = v13.cross_product(v14).z_ >= zero;
    auto test2 = v13.cross_product(v14);
    cout<<"---------------TEST 2-------------------------"<<endl;
   test2.print();
   cout<<"test 2----> "<<boolalpha<<der_v12_v13<<endl;


    bool different_dir = der_v12_v13 ^ der_v12_v14;

    cout<<boolalpha<<different_dir<<endl;


    Vector<T>v31 = Vector(x1-x3,y1-y3,zero);
    Vector<T>v32 = Vector(x2-x3,y2-y3,zero);
    Vector<T>v34 = Vector(x4-x3,y4-y3,zero);
    cout<<"---------------TEST 3-------------------------"<<endl;
    bool der_v34_v31 = v34.cross_product(v31).z_ >= zero;
    auto test3 = v34.cross_product(v31);
    test3.print();
    cout<<"test 3----> "<< der_v34_v31<<endl;
    cout<<"---------------TEST 4-------------------------"<<endl;
    bool der_v34_v32 = v34.cross_product(v32).z_ >= zero;
    auto test4 = v34.cross_product(v32);    
    test4.print();
    cout<<"test 4----> "<< der_v34_v32<<endl;

    bool different_dir_v34 = der_v34_v31 ^ der_v34_v32;

    cout<<"-------------------------ANSWER-----------------------------------"<<endl;
    cout<<"is there intersection " << boolalpha<<different_dir_v34<<endl;
    cout<<"---------------------------------------------------------------"<<endl;

    return different_dir or different_dir_v34;

}

 
TEST(insertects , NormalTestCase){
    //EXPECT_EQ(insertects<int>(-3 , 0 , 4 , 3 , -2 , 3 , 4 , 0), true);
    //EXPECT_EQ(insertects<double>(-1 , 0 , 3 , 3 , 1.68 , 2.01 , 4 , 0), true);
    //EXPECT_EQ(insertects<double>(-1 , 0 , 3 , 3 , 1.33 , 1.75 , 0 , 4), true);
    //EXPECT_EQ(insertects<int>(-1 , 0 , 3 , 3 , 2 , 4 , 0 , 2), false);


    //EXPECT_EQ(insertects<double>(-1 , 0 , 3 , 3 , 5 , 4.5 , 4 ,0 ), false);
   
    EXPECT_EQ(insertects<double>(-1 , 0 , 3 , 3 , 5 , 4.5 , 7.28 ,6.21 ), false);
    


}   



int main(int argc , char** argv) {
  ::testing::InitGoogleTest(&argc , argv);
  return RUN_ALL_TESTS();
//insertects(-3 , 0 , 4 , 3 , -2 , 3 , 4 , 0);

  return 0;


}