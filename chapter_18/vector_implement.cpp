#include <iostream>
#include <initializer_list>
#include <algorithm>
#include <istream>
class vector{ 
    int sz;
    double* elem;
public:
    vector();
    vector(int sz);
    vector(std::initializer_list<double> lst); // constructor with initializer list.
    vector(const vector&);                  // copy constructor.
    vector& operator=(const vector&);       // copy asignment.
    vector(vector&&);                       // move constructor. Move operations do not take const arguments.
    vector& operator=(vector&&);            // move assignement. Move operations do not take const arguments.
    ~vector();
};

vector::vector() {
    std::cout << "Default Constructor\n";
    sz = 0;
    elem = nullptr;
}

vector::vector(int sz):sz(sz), elem(new double[sz]) {
        std::cout << "Non default Constructor\n";
        for (int i = 0; i < sz; ++i){
            elem[i] = 0.0;
        }
}

vector::vector(std::initializer_list<double> lst): sz(lst.size()), elem(new double[sz]) {
    std::cout << "Initializer list constructor\n";
    std::copy(lst.begin(), lst.end(), elem);
}

vector::vector(const vector&arg):sz(arg.sz), elem(new double[sz]) {
    std::cout << "Copy constructor\n";
    std::copy(arg.elem, arg.elem+sz, elem);
}

vector& vector::operator=(const vector&arg) {
    std::cout << "Copy assignment\n";
    double* p = new double[arg.sz];
    std::copy(arg.elem, arg.elem+sz, elem);
    delete[] elem;
    elem = p;
    sz = arg.sz;
    return *this;
}

vector::vector(vector&& arg): sz(arg.sz), elem(arg.elem) {
    std::cout << "Move constructor\n";
    arg.sz = 0;
    arg.elem = nullptr;
}

vector& vector::operator=(vector&& arg) {
    std::cout << "Move assignement\n";
    delete[] elem;
    elem = arg.elem;
    sz = arg.sz;
    arg.elem = nullptr;
    arg.sz = 0;
    return *this;
}

vector::~vector() {
    delete[] elem;
}

/////////////////////////////////////////////////////////////////////
vector MakeSomething(vector input){
    return input;    // Invoke move constructor
}

int main() {
    vector v(5);
    vector v2 = {1, 2, 3};
    vector v3 = v2;

    {
        vector v4{1, 2, 3, 4};
        v = v4;
    }

    vector v5 = MakeSomething(vector()); // input vector() will be move constructor.
    vector v6 = std::move(v5);
}