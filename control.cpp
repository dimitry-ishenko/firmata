////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2013-2017 Dimitry Ishenko
//
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL v3.
// For full terms see COPYING or visit https://www.gnu.org/licenses/gpl.html

////////////////////////////////////////////////////////////////////////////////
#include "firmata/control.hpp"

////////////////////////////////////////////////////////////////////////////////
namespace firmata
{

////////////////////////////////////////////////////////////////////////////////
control::control(io::base* io) : io_(io)
{
    ////////////////////
    // get version and firmware
    io_->send(fw_query);
    payload data = get(fw_reply);

    version_ = std::make_tuple(data[0], data[1]);
    firmware_ = to_string(data.begin() + 2, data.end());

    ////////////////////
    //

    ////////////////////
    query_state();
}

////////////////////////////////////////////////////////////////////////////////
void control::reset()
{
    io_->send(firmata::reset);
    query_state();
}

////////////////////////////////////////////////////////////////////////////////
payload control::get(type reply_id)
{
    type id;
    payload data;

    do { std::tie(id, data) = io_->recv(); }
    while(id != reply_id);

    return data;
}

////////////////////////////////////////////////////////////////////////////////
void control::query_state()
{
}

////////////////////////////////////////////////////////////////////////////////
}
