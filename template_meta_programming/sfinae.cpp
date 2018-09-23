// at least g++ 4.4, use boost and c++0x
// can replace `boost::` to `std::` when using full c++11 support
#include <boost/type_traits.hpp>
#include <boost/utility/declval.hpp>
#include <iostream>

using namespace std;

#define create_member_checker(member)                                                         \
    template <typename T>                                                                     \
    struct has_member_##member {                                                              \
    private:                                                                                  \
        template <typename U>                                                                 \
        static auto Check(int) -> decltype(boost::declval<U>().member(), boost::true_type()); \
        template <typename U>                                                                 \
        static boost::false_type Check(...);                                                  \
                                                                                              \
    public:                                                                                   \
        enum { value = boost::is_same<decltype(Check<T>(0)), boost::true_type>::value };      \
    };

create_member_checker(foo);
create_member_checker(test);

struct myStruct {
    void foo() { cout << "foo" << endl; }
};

struct another {
    void test() { cout << "test" << endl; }
};

int main()
{
    if (has_member_foo<myStruct>::value)
        cout << "myStruct has foo funciton" << endl;
    else
        cout << "myStruct does't have foo funciton" << endl;

    if (has_member_foo<another>::value)
        cout << "another has foo function" << endl;
    else
        cout << "another does't have foo function" << endl;

    if (has_member_test<myStruct>::value)
        cout << "myStruct has test funciton" << endl;
    else
        cout << "myStruct does't have test funciton" << endl;

    if (has_member_test<another>::value)
        cout << "another has foo function" << endl;
    else
        cout << "another does't have foo function" << endl;
    return 0;
}
