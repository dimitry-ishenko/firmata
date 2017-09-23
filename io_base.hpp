////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2017 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef FIRMATA_IO_BASE_HPP
#define FIRMATA_IO_BASE_HPP

////////////////////////////////////////////////////////////////////////////////
#include "firmata/callback.hpp"
#include "firmata/types.hpp"

#include <chrono>
#include <utility> // std::move

////////////////////////////////////////////////////////////////////////////////
namespace firmata
{

////////////////////////////////////////////////////////////////////////////////
// Abstract base class for communication with Firmata host
//
class io_base
{
public:
    ////////////////////
    virtual void write(msg_id, const payload& = { }) = 0;

    ////////////////////
    using read_callback = callback<void(msg_id, const payload&)>;

    virtual int on_read(read_callback fn) { return chain_.add(std::move(fn)); }
    virtual void remove_callback(int id) { chain_.remove(id); }

    ////////////////////
    using condition = std::function<bool()>;

    using msec = std::chrono::milliseconds;
    static constexpr msec eons { -1 };

    // block until condition or timeout
    virtual bool wait_until(const condition&, const msec& = eons) = 0;

protected:
    ////////////////////
    callback_chain<read_callback> chain_;
};

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
