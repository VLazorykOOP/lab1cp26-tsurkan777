#include <iostream>
#include <fstream>
#include <cmath>
#include <stdexcept>

using namespace std;

/* ===== ВЛАСНІ ВИНЯТКИ ===== */
class Alg2Exception : public exception {};
class Alg3Exception : public exception {};
class FileException : public exception {};

/* ===== РОБОТА З ФАЙЛАМИ ===== */
double readFromFile(const string& name) {
    ifstream file(name);
    if (!file.is_open()) {
        throw FileException();
    }
    double value;
    file >> value;
    file.close();
    return value;
}

/* ===== T(x) та U(x) ===== */
double T(double x) {
    if (x <= 1)
        return readFromFile("dat_X_1_1.dat");
    if (x < -1)
        return readFromFile("dat_X_00_1.dat");
    return readFromFile("dat_X_1_00.dat");
}

double U(double x) {
    return T(x); // за умовою використовується та сама логіка
}

/* ===== Rrz ===== */
double Rrz(double x, double y, double z) {
    if (z*z + x*y <= 0)
        throw Alg2Exception();
    if (x*x + z*y <= 0)
        throw Alg3Exception();

    return sqrt(z*z + x*y) + sqrt(x*x + z*y);
}

/* ===== Qrz ===== */
double Qrz(double x, double y, double z) {
    return x*y + z;
}

/* ===== Grs ===== */
double Grs(double x, double y, double z) {
    return Rrz(x,y,z) + Qrz(x,y,z) + T(x) + U(y);
}

/* ===== АЛГОРИТМИ ===== */
double algorithm1(double x, double y, double z) {
    return x * Grs(x,y,z) + y * Grs(x,z,y);
}

double algorithm2(double x, double y, double z) {
    return x*x + y*y + z*z;
}

double algorithm3(double x, double y, double z) {
    return x*y*z;
}

double algorithm4(double x, double y, double z) {
    return 1.3498*x + 2.2362*y*z - 2.348*x*y;
}

/* гол функ*/
double fun(double x, double y, double z) {
    try {
        return algorithm1(x,y,z);
    }
    catch (Alg2Exception&) {
        return algorithm2(x,y,z);
    }
    catch (Alg3Exception&) {
        return algorithm3(x,y,z);
    }
    catch (FileException&) {
        return algorithm4(x,y,z);
    }
}

/* перевірка */
int main() {
    double x, y, z;
    cout << "Enter x y z: ";
    cin >> x >> y >> z;

    try {
        double result = fun(x,y,z);
        cout << "Result = " << result << endl;
    }
    catch (...) {
        cout << "Critical error!" << endl;
    }
    return 0;
}
