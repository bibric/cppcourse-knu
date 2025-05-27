

#include <iostream>
#include <array>
#include <vector>


/* --------------------------------------------------------------------------------------------
 * Smart pointers as class members.
 *
 * Class members that are pointers can quickly become a problem.
 * Firstly, if only raw pointers are used, the intended ownership is unclear.
 * Secondly, it's easy to overlook that a member has to be deleted.
 * Thirdly, pointer members usually require you to implement copy or move constructors
 * and assignment operators (--> rule of 3, rule of 5).
 * Since C++-11, one can solve a few of those problems using smart pointers.
 *
 * The class "Owner" owns some data, but it is broken. If you copy it like in
 * doStuff(), you have two pointers pointing to the same data, but both instances
 * think that they own the data.
 *
 * Tasks
 * 1) It likely crashes. Verify this. You can also try running `valgrind ./problem4`,
 *    it should give you some hints as to what's happening.
 * 2) Fix the Owner class by using a `std::shared_ptr` for its data, which we can
 *    copy as much as we want. Run the fixed program.
 *    Note: Once `std::shared_ptr` is in use, you can also use the default destructor.
 *
 * --------------------------------------------------------------------------------------------
 */
#include <memory>


struct LargeObject {

    std::array<double, 100000> data ;

} ;

class Owner {

  public:

    Owner() : _largeObject( new LargeObject() ) {}
    LargeObject * getLargeObject() const { return _largeObject.get() ; }

  private:

    std::shared_ptr<LargeObject> _largeObject ;

} ;

void doStuff() {

    std::vector<Owner> owners ;

    for ( int i = 0 ; i < 5 ; ++i ) {
        Owner owner ;
        // ... additional owner setup ...
        owners.push_back(owner) ;
    }
}

int main() {

    doStuff() ;

}
