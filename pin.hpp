////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2013-2017 Dimitry Ishenko
//
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL v3.
// For full terms see COPYING or visit https://www.gnu.org/licenses/gpl.html

////////////////////////////////////////////////////////////////////////////////
#ifndef FIRMATA_PIN_HPP
#define FIRMATA_PIN_HPP

////////////////////////////////////////////////////////////////////////////////
#include "firmata/types.hpp"
#include <map>

////////////////////////////////////////////////////////////////////////////////
namespace firmata
{

////////////////////////////////////////////////////////////////////////////////
using modes = std::map<mode, res>;

////////////////////////////////////////////////////////////////////////////////
class pin
{
public:
    ////////////////////
    pin(const pin&) = delete;
    pin(pin&& other) noexcept { swap(other); }

    pin& operator=(const pin&) = delete;
    pin& operator=(pin&& other) noexcept { swap(other); return *this; }

    void swap(pin& other) noexcept
    {
        using std::swap;
        swap(digital_, other.digital_);
        swap(analog_,  other.analog_ );
        swap(modes_,   other.modes_  );
    }

    ////////////////////
    firmata::pos pos(type n) const noexcept;

    auto const& modes() const noexcept { return modes_; }
    bool supports(mode n) const noexcept { return modes_.count(n); }

private:
    ////////////////////
    firmata::pos digital_ = invalid, analog_ = invalid;
    firmata::modes modes_;

    ////////////////////
    pin() noexcept = default;
    friend class control;
};

////////////////////////////////////////////////////////////////////////////////
inline void swap(pin& lhs, pin& rhs) noexcept { lhs.swap(rhs); }

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif