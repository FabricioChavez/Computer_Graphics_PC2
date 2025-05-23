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
template <typename T>
class Vector {
private:
    bool is_int;

public:
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

            cout << "MY X EN RESTA " << x << endl;

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


    cout<<"EL SIGNO DE A & B "<< sgnC<<"--->"<<above_line.cross_product(below_line).z_<<endl;
    


    cout<<"EL SIGNO DE LAS INTERSECTIONS "<<sgnA<<endl;
    cout<<"EL SIGNO DE LAS INTERSECTIONS "<<sgnB<<endl;
    cout<<"CAN CROSS? "<<boolalpha<<can_cross<<endl;


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
        cout<<"LOS PUNTOS"<<char('A'+(i-1))<<" and "<<char('A'+(i))<<endl;
        cout<<"SEGMENT"<<endl;
        cout<<"PA "<<endl;
        Pa.print();
        cout<<"PB"<<endl;
        Pb.print();
        cout<<"IS THERE CUT RIGHT? "<<endl;
        cout<<boolalpha<<line_segment_insertection<T>( p_test , dir ,Pa  , Pb , true)<<endl;
        cout<<"IS THERE CUT LEFT? "<<endl;
        cout<<boolalpha<<line_segment_insertection<T>( p_test , dir ,Pa  , Pb , false)<<endl;

        if(p_test == Pa  or p_test == Pb) return true;
      cout<<"-------------------------DONT MIND---------------------------------------"<<endl;
        if(line_segment_insertection<T>( p_test , dir ,Pa  , Pb , true)) cnt_right++;
        if(line_segment_insertection<T>(p_test  , dir_n , Pa , Pb, false)) cnt_left++;
      cout<<"--------------------------------------------------------------------------"<<endl;
    }


   cout<<"FOR POINT :"<<endl;
   p_test.print();
    cout<<"cnt_right    :"<<cnt_right<<endl;
   cout<<"cnt_left     :"<<cnt_left<<endl;

    if(cnt_left%2 == 1 and cnt_right%2==1 ) return true;
    else if ((cnt_left+cnt_right)%2==1) return true;

    return false;

}

TEST(PolygonTest_double , PointOutsideT ){
    vector<vector<double>>vertices{{-8,2},{-4,4},{0,2},{2,4},{4,2},{4,-2},{0,-2},{-6,-2}};
    EXPECT_FALSE(inside_polygon<double>(vertices , -2.04 , -3.6));
}
TEST(PolygonTest_double , PointOutsideU ){
    vector<vector<double>>vertices{{-8,2},{-4,4},{0,2},{2,4},{4,2},{4,-2},{0,-2},{-6,-2}};
    EXPECT_FALSE(inside_polygon<double>(vertices , 7.16 , 4.51));
}
TEST(PolygonTest_double , PointOutsideV ){
    vector<vector<double>>vertices{{-8,2},{-4,4},{0,2},{2,4},{4,2},{4,-2},{0,-2},{-6,-2}};
    EXPECT_FALSE(inside_polygon<double>(vertices , -11.53 , 1.59));
}
TEST(PolygonTest_double , PointOutsideW ){
    vector<vector<double>>vertices{{-8,2},{-4,4},{0,2},{2,4},{4,2},{4,-2},{0,-2},{-6,-2}};
    EXPECT_FALSE(inside_polygon<double>(vertices , 7.69 , 1.72));
}

TEST(PolygonTest_double , PointOutsideI ){
    vector<vector<double>>vertices{{-8,2},{-4,4},{0,2},{2,4},{4,2},{4,-2},{0,-2},{-6,-2}};
    EXPECT_FALSE(inside_polygon<double>(vertices , -8.78 , -1.96));
}
TEST(PolygonTest_double , PointOutsideM ){
    vector<vector<double>>vertices{{-8,2},{-4,4},{0,2},{2,4},{4,2},{4,-2},{0,-2},{-6,-2}};
    EXPECT_FALSE(inside_polygon<double>(vertices , -0.71 , 3.46));
}

TEST(PolygonTest_double , PointInsideK){
    vector<vector<double>>vertices{{-8,2},{-4,4},{0,2},{2,4},{4,2},{4,-2},{0,-2},{-6,-2}};
    EXPECT_TRUE(inside_polygon<double>(vertices , -4.07 , 3.19));
 }
TEST(PolygonTest_double , PointInsideL){
    vector<vector<double>>vertices{{-8,2},{-4,4},{0,2},{2,4},{4,2},{4,-2},{0,-2},{-6,-2}};
    EXPECT_TRUE(inside_polygon<double>(vertices , 2 , 3.04));
}
TEST(PolygonTest_double , PointInsideO){
    vector<vector<double>>vertices{{-8,2},{-4,4},{0,2},{2,4},{4,2},{4,-2},{0,-2},{-6,-2}};
    EXPECT_TRUE(inside_polygon<double>(vertices , 2.76 , 3.24));
}
TEST(PolygonTest_double , PointInsideN){
    vector<vector<double>>vertices{{-8,2},{-4,4},{0,2},{2,4},{4,2},{4,-2},{0,-2},{-6,-2}};
    EXPECT_TRUE(inside_polygon<double>(vertices , -5.6 , 3.2));
}
TEST(PolygonTest_double , PointInsideR){
    vector<vector<double>>vertices{{-8,2},{-4,4},{0,2},{2,4},{4,2},{4,-2},{0,-2},{-6,-2}};
    EXPECT_TRUE(inside_polygon<double>(vertices , -2 , 3));
}
TEST(PolygonTest_double , PointInsideJ){
    vector<vector<double>>vertices{{-8,2},{-4,4},{0,2},{2,4},{4,2},{4,-2},{0,-2},{-6,-2}};
    EXPECT_TRUE(inside_polygon<double>(vertices , -1.71 , -2));
}

TEST(PolygonTest_double , PointInsideQ){
    vector<vector<double>>vertices{{-8,2},{-4,4},{0,2},{2,4},{4,2},{4,-2},{0,-2},{-6,-2}};
    EXPECT_TRUE(inside_polygon<double>(vertices , 0 , 0));
}

// Tests para valores extremos double
TEST(PolygonTest_double, ExtremePointOutside1) {
    vector<vector<double>> vertices{{-8,2},{-4,4},{0,2},{2,4},{4,2},{4,-2},{0,-2},{-6,-2}};
    EXPECT_FALSE(inside_polygon<double>(vertices, DBL_MAX, DBL_MAX));
}

//Tests con valores extremos más adecuados
TEST(PolygonTest_double, ExtremeNegativeCoordinates) {
    vector<vector<double>> vertices{{-8,2},{-4,4},{0,2},{2,4},{4,2},{4,-2},{0,-2},{-6,-2}};
    // Valor negativo extremadamente grande (definitivamente fuera del polígono)
    EXPECT_FALSE(inside_polygon<double>(vertices, -1e100, -1e100));
}

TEST(PolygonTest_double, ExtremePositiveCoordinates) {
    vector<vector<double>> vertices{{-8,2},{-4,4},{0,2},{2,4},{4,2},{4,-2},{0,-2},{-6,-2}};
    // Valor positivo extremadamente grande (definitivamente fuera del polígono)
    EXPECT_FALSE(inside_polygon<double>(vertices, 1e100, 1e100));
}

TEST(PolygonTest_double, NearZeroPointInside) {
    vector<vector<double>> vertices{{-8,2},{-4,4},{0,2},{2,4},{4,2},{4,-2},{0,-2},{-6,-2}};
    // Punto muy cercano a cero pero dentro del polígono
    EXPECT_TRUE(inside_polygon<double>(vertices, 1e-200, 0));
}

TEST(PolygonTest_double, SmallEpsilonOutsideEdge) {
    vector<vector<double>> vertices{{-8,2},{-4,4},{0,2},{2,4},{4,2},{4,-2},{0,-2},{-6,-2}};
    // Punto que está justo fuera del borde del polígono por un epsilon muy pequeño
    EXPECT_FALSE(inside_polygon<double>(vertices, 4 + 1e-10, 0));
}
TEST(PolygonTest_double, ExtremePointOnEdge) {
    vector<vector<double>> vertices{{-8,2},{-4,4},{0,2},{2,4},{4,2},{4,-2},{0,-2},{-6,-2}};
    // Punto exactamente en un borde (coordenada x del vértice más extremo)
    EXPECT_TRUE(inside_polygon<double>(vertices, -8, 2));
}

TEST(PolygonTest_double, NearlyZeroDistance) {
    vector<vector<double>> vertices{{-8,2},{-4,4},{0,2},{2,4},{4,2},{4,-2},{0,-2},{-6,-2}};
    // Punto muy cercano al borde (prueba para precisión de punto flotante)
    EXPECT_FALSE(inside_polygon<double>(vertices, -8, 2.0 + 1e-10));
}


TEST(PolygonTest_int, ExtremePointOnVertex) {
    vector<vector<int>> vertices{{-8,2},{-4,4},{0,2},{2,4},{4,2},{4,-2},{0,-2},{-6,-2}};
    // Punto exactamente en un vértice
    EXPECT_TRUE(inside_polygon<int>(vertices, -8, 2));
}

// Tests para valores extremos int
TEST(PolygonTest_int, ExtremePointOutside1) {
    vector<vector<int>> vertices{{-8,2},{-4,4},{0,2},{2,4},{4,2},{4,-2},{0,-2},{-6,-2}};
    EXPECT_FALSE(inside_polygon<int>(vertices, INT_MAX, INT_MAX));
}

TEST(PolygonTest_int, ExtremePointOutside2) {
    vector<vector<int>> vertices{{-8,2},{-4,4},{0,2},{2,4},{4,2},{4,-2},{0,-2},{-6,-2}};
    EXPECT_FALSE(inside_polygon<int>(vertices, INT_MIN, INT_MIN));
}



TEST(PolygonTest_int, PointOnEdge) {
    vector<vector<int>> vertices{{-8,2},{-4,4},{0,2},{2,4},{4,2},{4,-2},{0,-2},{-6,-2}};
    // Punto exactamente en un borde
    EXPECT_TRUE(inside_polygon<int>(vertices, -7, 2)); // Punto en el borde horizontal superior
}

// Pruebas de casos especiales
TEST(PolygonTest_double, VerticallyStraightEdge) {
    vector<vector<double>> vertices{{-8,2},{-4,4},{0,2},{2,4},{4,2},{4,-2},{0,-2},{-6,-2}};
    // Punto exactamente a la izquierda de un borde vertical
    EXPECT_TRUE(inside_polygon<double>(vertices, 3.999, 0));
    // Punto exactamente a la derecha de un borde vertical
    EXPECT_TRUE(inside_polygon<double>(vertices, 4, 0));
    EXPECT_FALSE(inside_polygon<double>(vertices, 4.0001, 0));
}

TEST(PolygonTest_double, HorizontallyAlignedPoints) {
    vector<vector<double>> vertices{{-8,2},{-4,4},{0,2},{2,4},{4,2},{4,-2},{0,-2},{-6,-2}};
    // Puntos alineados horizontalmente con un borde horizontal
    EXPECT_TRUE(inside_polygon<double>(vertices, -5, -2));
    EXPECT_FALSE(inside_polygon<double>(vertices, -7, -2));
}

TEST(PolygonTest_int, LargeCoordinates) {
    // Usar un polígono con coordenadas más grandes
    vector<vector<int>> vertices{
        {-1000000, 1000000},
        {1000000, 1000000},
        {1000000, -1000000},
        {-1000000, -1000000}
    };
    // Punto dentro del gran cuadrado
    EXPECT_TRUE(inside_polygon<int>(vertices, 0, 0));
    // Punto fuera del gran cuadrado
    EXPECT_FALSE(inside_polygon<int>(vertices, 1000001, 0));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}