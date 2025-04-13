#include <iomanip>
#include <iostream>
#include <numeric>

class Fraction {
 public:
    Fraction(int r = 1, int i = 1) : chiselnik(r), znaminic(i) {
        normalize();
    }
    Fraction & operator*=(int i) {
        chiselnik *= i;
        normalize();
        return *this;
    }

    Fraction & operator*=(Fraction const & o) {
        chiselnik *= o.chiselnik;
        znaminic *= o.znaminic;
        normalize();
        return *this;
    }
    // Умножение на int (справа)
    friend Fraction operator*(Fraction f, int i) { return f *= i; }
    friend Fraction operator*(int i, Fraction const & f) { return f * i; }
    friend Fraction operator*(Fraction a, Fraction const & b) { return a *= b; }

    bool operator==(const Fraction& obj) const {
        if((chiselnik==obj.chiselnik)&&(znaminic==obj.znaminic)){
            return (bool)1;
        }
        else{
            return (bool)0;
        }
    }
    friend bool operator!=(Fraction const & a, Fraction const & b) { return !(a==b); }
    bool operator>(const Fraction& obj) const {
        //std::cout<<(*this!=obj)<<" "<<((((float)chiselnik/znaminic)>((float)obj.chiselnik/obj.znaminic)))<<std::endl;
        if(((float)chiselnik/znaminic)>((float)obj.chiselnik/obj.znaminic)){
            return (bool)1;
        }
        else{
            return (bool)0;
        }
    }

    friend bool operator<(Fraction const & a, Fraction const & b) { return (!(a>b))&&(a!=b); }
    friend bool operator<=(Fraction const & a, Fraction const & b) { return (!(a>b))||(a==b); }
    friend bool operator>=(Fraction const & a, Fraction const & b) { return (a>b)||(a==b); }
    friend std::ostream& operator<<(std::ostream& os, const Fraction& obj);

 private:
    int chiselnik, znaminic;

    void normalize() {
        int gcd = std::gcd(chiselnik, znaminic);
        chiselnik /= gcd;
        znaminic /= gcd;
    }
};
std::ostream& operator<<(std::ostream& os, const Fraction& obj) {
    float div = (float)obj.chiselnik/obj.znaminic;
    os <<  obj.chiselnik << "/"
              << obj.znaminic << "="<<std::setprecision(3) << div;
    //delete div;
return os;
}


void printAndCheck(std::string const & what, Fraction const & result, Fraction const & expected) {
  const bool passed = result == expected;
  std::cout << std::left << std::setw(40) << what << ": " << (passed ? "PASS" : "** FAIL **") << "    " << result << "\n";
}
void printAndCheck(std::string const & what, bool result, bool expected) {
  const bool passed = result == expected;
  std::cout << std::left << std::setw(40) << what << ": " << (passed ? "PASS" : "** FAIL **") << "    " << result << "\n";
}

int main() {
  // create a fraction with values 3 (which is 3/1) and 1/3
  const Fraction three{3};
  const Fraction athird{1,3};

  // print the fractions
  std::cout << "Three: " << three << '\n';
  std::cout << "One third: " << athird << '\n';
  //std::cout <<2*athird<<"\n";

  // multiply fraction with an int
  // the printAndCheck function requires operator<< and operator==:
  printAndCheck("One third times two", athird * 2, Fraction{2, 3});
  // ensure symmetry
  printAndCheck("Two times one third", 2 * athird, Fraction{2, 3});

  // multiply two fractions
  printAndCheck("Three times one third", three * athird, Fraction{1, 1});
  // normalize the fraction after multiplication so the above statement
  // prints 1/1 instead of e.g. 3/3
  printAndCheck("Three times one third", 3 * athird, Fraction{1, 1});

  // multiply in place
  Fraction f = athird;
  f *= 2;
  printAndCheck("One third times two", f, Fraction{2, 3});

  f *= athird;
  printAndCheck("Two third times one third", f, Fraction{2, 9});

  // you might have some redundancy between the implementation of operator* and
  // operator*=. Can you refactor your code and implement operator* in terms of
  // operator*=?

  std::cout << std::boolalpha;  // print bools as 'true' or 'false' from now on

  // more equality comparisons
  printAndCheck("One third == one third", (athird == Fraction{1, 3}), true);
  printAndCheck("One third != one forth", (athird != Fraction{1, 4}), true);
  printAndCheck("One third == two sixth", (athird == Fraction{2, 6}), true);
  printAndCheck("One third != three sixth", (athird != Fraction{3, 6}), true);
  // try to implement operator!= in terms of operator==

  // more comparisons
  const Fraction afourth{1, 4};
  printAndCheck("athird < athird", (athird < athird), false);
  printAndCheck("afourth < athird", (afourth < athird), true);
  printAndCheck("athird  <= athird", (athird <= athird), true);
  printAndCheck("athird  <= afourth", (athird <= afourth), false);
  printAndCheck("athird  > athird", (athird > athird), false);
  printAndCheck("afourth > athird", (afourth > athird), false);
  printAndCheck("athird >= athird", (athird >= athird), true);
  printAndCheck("athird >= afourth", (athird >= afourth), true);
  // the operators <=, >= and > can typically be implemented just in terms of
  // operator<. Can you do this as well? ;)

  // take aways on operators:
  // * we can very often implement an arithemtic operator@ in terms of
  // operator@=
  // * it usually suffices to implement operator< and operator== and derive the
  // other relational operators from them. C++20 will do part of this automatically.
}
