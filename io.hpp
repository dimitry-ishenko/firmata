////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2013-2017 Dimitry Ishenko
//
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL v3.
// For full terms see COPYING or visit https://www.gnu.org/licenses/gpl.html

////////////////////////////////////////////////////////////////////////////////
#ifndef FIRMATA_IO_HPP
#define FIRMATA_IO_HPP

////////////////////////////////////////////////////////////////////////////////
#include <cstdint>
#include <tuple>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
namespace firmata
{

////////////////////////////////////////////////////////////////////////////////
using  byte = std::uint8_t;
using  word = std::uint16_t;
using dword = std::uint32_t;

enum type : dword;

constexpr byte start_sysex = 0xf0;
constexpr byte end_sysex = 0xf7;
constexpr byte ext_id = 0x00;

////////////////////////////////////////////////////////////////////////////////
constexpr type sysex(byte id) noexcept
{ return static_cast<type>(dword(start_sysex) + (dword(id) << 8)); }

constexpr bool is_sysex(type id) noexcept
{ return byte(id & 0xff) == start_sysex; }

constexpr type ext_sysex(word id) noexcept
{ return static_cast<type>(dword(start_sysex) + (dword(ext_id) << 8) + (dword(id) << 16)); }

constexpr bool is_ext_sysex(type id) noexcept
{ return is_sysex(id) && byte((id >> 8) & 0xff) == ext_id; }

////////////////////////////////////////////////////////////////////////////////
enum type : dword
{
};

using payload = std::vector<byte>;

////////////////////////////////////////////////////////////////////////////////
namespace io
{

////////////////////////////////////////////////////////////////////////////////
class base
{
public:
    ////////////////////
    virtual void send(type, const payload&) = 0;
    virtual std::tuple<type, payload> recv() = 0;
};

////////////////////////////////////////////////////////////////////////////////
}
}

////////////////////////////////////////////////////////////////////////////////
#endif