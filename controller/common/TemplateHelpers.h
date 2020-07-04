/*******************************************************************************************
*    Copyright 2020 Felix Petriconi
*    Distributed under the Boost Software License, Version 1.0.
*    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
********************************************************************************************/

#ifndef TEMPLATEHELPERS_H
#define TEMPLATEHELPERS_H

#include <iterator>
#include <type_traits>

namespace DIYV
{
    template <typename T, template<typename> class crtpType>
    struct crtp
    {
        T& underlying() { return static_cast<T&>(*this); }
        T const& underlying() const { return static_cast<T const&>(*this); }
    private:
        crtp(){}
        friend crtpType<T>;
    };

    template <typename R>
    typename R::iterator_type make_iterator(R reverse_iterator)
    {
      static_assert(std::is_same<R, typename std::reverse_iterator<typename R::iterator_type>>::value,
        "Passed argument is not a reverse_iterator!");
      return --reverse_iterator.base();
    }
}

#endif // TEMPLATEHELPERS_H
