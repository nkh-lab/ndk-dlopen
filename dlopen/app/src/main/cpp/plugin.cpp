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

BOOST_DLL_ALIAS(my::count, boost_alias_count)
