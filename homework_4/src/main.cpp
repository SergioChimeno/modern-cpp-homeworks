#include <iostream>
#include "homework_4.h"

int main(int argc, char const *argv[])
{
    std::cout << "## Homework 4 ##" << std::endl;

    ipb::named_vector<int> v1{"MyVector1",{1,2,3,4}};
    ipb::named_vector<int> v2{"MyVector2",{2,4,6,8}};
    ipb::named_vector<int> v3{"MyVector3",{112,2,3,4,6,7,2,86,765}};

    // Result 1
    int result1 = ipb::accumulate(v1);
    std::cout << "-->accumulate: " << result1 << std::endl;

    // Result 2
    int result2 = ipb::count(v1,1);
    std::cout << "-->count: " << result2 << std::endl;

    // Result 3
    int result3_1 = ipb::all_even(v1);
    int result3_2 = ipb::all_even(v2);
    std::cout << "-->all_even\n";
    std::cout << result3_1 << std::endl;
    std::cout << result3_2 << std::endl;

    // Result 4
    std::cout << "-->clamp\n";
    ipb::clamp(v1,2,3);
    ipb::print(v1);

    // Result 5
    std::cout << "-->fill\n";
    ipb::fill(v1,4);
    ipb::fill(v2,-1);
    ipb::print(v1);
    ipb::print(v2);

    // Result 6
    std::cout << "-->find\n";
    bool result6_1 = ipb::find(v1,4);
    bool result6_2 = ipb::find(v2,0);
    std::cout << result6_1 << std::endl;
    std::cout << result6_2 << std::endl;

    // Result 7
    std::cout << "-->toUpper\n";
    ipb::toUpper(v1);
    ipb::toUpper(v2);
    ipb::print(v1);
    ipb::print(v2);

    // Result 8
    std::cout << "-->sort\n";
    ipb::sort(v3);
    print(v3);

    // Result 9
    std::cout << "-->rotate\n";
    ipb::rotate(v3,2);
    print(v3);

    // Result 10
    std::cout << "-->reverse:\n";
    ipb::reverse(v3);
    print(v3);

    return 0;
}
