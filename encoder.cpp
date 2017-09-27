////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2017 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "encoder.hpp"

#include <functional>
#include <stdexcept>
#include <utility>

////////////////////////////////////////////////////////////////////////////////
namespace firmata
{

////////////////////////////////////////////////////////////////////////////////
encoder::encoder(pin& pin1, pin& pin2) : pin1_(pin1), pin2_(pin2)
{
    if((pin1.mode() == digital_in || pin1.mode() == pullup_in)
    && (pin2.mode() == digital_in || pin2.mode() == pullup_in))
    {
        using namespace std::placeholders;
        id_ = pin1_.on_state_changed(std::bind(&encoder::pin_state_changed, this, _1));
    }
    else throw std::invalid_argument("Invalid pin mode");
}

////////////////////////////////////////////////////////////////////////////////
encoder::~encoder() { pin1_.remove_callback(id_); }

////////////////////////////////////////////////////////////////////////////////
cbid encoder::on_rotate(int_callback fn) { return rotate_.add(std::move(fn)); }
cbid encoder::on_rotate_cw(void_callback fn) { return rotate_cw_.add(std::move(fn)); }
cbid encoder::on_rotate_ccw(void_callback fn) { return rotate_ccw_.add(std::move(fn)); }

void encoder::remove_callback(cbid id)
{
    rotate_.remove(id) || rotate_cw_.remove(id) || rotate_ccw_.remove(id);
}

////////////////////////////////////////////////////////////////////////////////
void encoder::pin_state_changed(int state)
{
    if(state)
    {
        auto step = pin2_.state() ? cw : ccw;
        if(step == step_)
        {
            switch(step)
            {
            case  no: break;
            case  cw: rotate_( 1); rotate_cw_(); break;
            case ccw: rotate_(-1); rotate_ccw_(); break;
            }
        }
        step_ = no;
    }
    else step_ = pin2_.state() ? ccw : cw;
}

////////////////////////////////////////////////////////////////////////////////
}
