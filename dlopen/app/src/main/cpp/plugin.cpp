#include <boost/dll.hpp>

extern "C" int count()
{
    static int i = 0;

    return ++i;
}

namespace my {
int count()
{
    static int i = 0;

    return ++i;
}
} // namespace my

extern "C" int (*alias_count)() = my::count;

//
// In case of missing alias in output binary next flag forces its instantiation:
//
// set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBOOST_DLL_FORCE_ALIAS_INSTANTIATION")
//
BOOST_DLL_ALIAS(my::count, boost_alias_count)
