// MessagePack for C++ example
//
// Copyright (C) 2015 KONDO Takatoshi
//
//    Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//    http://www.boost.org/LICENSE_1_0.txt)
//
#include "gtest.h"
#include <msgpack.hpp>
#include <string>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <array>
#include "dmcrc.h"
#include "dmfile.h"
#include <memory>

class Event_snapshot
{
public:
    uint32_t listener_id;
};
class Tasks_node
{
public:
};

class Tasks {
public:
    std::map<int32_t, Tasks_node> map_Tasks;
};


class Frame_props_snapshot{
public:
    
};
class Timer_snapshot {
public:

};

class Basic
{
public:
    uint32_t current_frame_id;
    Event_snapshot event_snapshot;
    Frame_props_snapshot frame_props_snapshot;
    uint32_t gen_id_cursor;
    Timer_snapshot timer_snapshot;
};

class Blackboard
{
public:
    std::string caution_pos;
};

class Custom_level_data_node
{
public:
};

class Custom_level_data
{
public:
    std::map<std::string, Custom_level_data_node> node;
};

class LCreature
{
public:
    uint32_t _ability_point;
    uint32_t _auto_recover_timer;
    uint32_t _seq_count;
    std::string b_i_t_reason;
    Blackboard blackboard;
    uint32_t  creature_subtype;
    std::string cur_tree;
    Custom_level_data custom_level_data;
    uint32_t eid;
    uint32_t entity_no;
    Event_snapshot event_snapshot;
    Frame_props_snapshot frame_props_snapshot;
    MSGPACK_DEFINE(_ability_point, _auto_recover_timer);
};

class Lprojectile_node
{
public:
    uint32_t _ability_point;
    uint32_t _auto_recover_timer;
    uint32_t _exit_battle_timer;
    //google.protobuf.Any _life_cycle_timer = 4;
    //repeated google.protobuf.Any _sensors_dict = 5;
    uint32_t _seq_count;
    std::string b_i_t_reason;
    Blackboard blackboard;
    std::string cur_tree;
    uint32_t eid;
    uint32_t entity_no;
    Event_snapshot event_snapshot;
    Frame_props_snapshot frame_props_snapshot;
    std::string hp;
    std::string mhp;
    std::string mmp;
    std::string mp;
    std::string position;
    Timer_snapshot timer_snapshot;
    uint32_t unit_id;
    std::string yaw;
};

class Lprojectile
{
public:
};

class Entities_snapshot
{
public:
    LCreature LCreature;
    Lprojectile LProjectile;

    MSGPACK_DEFINE(LCreature);
};

class Fix32 {
public:
    uint64_t value;
    MSGPACK_DEFINE(value);
};

class Fix32Vec2 {
public:
    Fix32 x;
    Fix32 y;
    MSGPACK_DEFINE(x, y);
};

class Fix32Vec3 {
public:
    Fix32 x;
    Fix32 y;
    Fix32 z;
    MSGPACK_DEFINE(x, y, z);
};

union UN_VEC3
{
    Fix32 v1;
    Fix32Vec2 v2;
    Fix32Vec3 v3;
    MSGPACK_DEFINE(v1, v2, v3);
};

class snapshot
{
public:
    Basic basic;
    uint32_t current_frame_per_second;
    uint32_t current_time_scale;
    std::vector<uint32_t> entities_index;
    Entities_snapshot entities_snapshot;
    std::string random_state;
    std::array<int, 32> status_count;
    Fix32Vec3 vec3_data;
    UN_VEC3 uv3_data;
    MSGPACK_DEFINE(current_frame_per_second, current_time_scale, entities_index, entities_snapshot, random_state, status_count, vec3_data, uv3_data);
};

TEST(msgpack_write, msgpack_write)
{
    std::shared_ptr<snapshot> snap(new snapshot());
    snap->current_frame_per_second = 1234;
    snap->current_time_scale = 6789;
    snap->entities_index.push_back(1);
    snap->entities_index.push_back(12);
    snap->entities_index.push_back(123);
    snap->random_state = "Ëæ»ú×´Ì¬Êý¾Ý";
    snap->entities_snapshot.LCreature._ability_point = 222;
    snap->entities_snapshot.LCreature._auto_recover_timer = 333;

    snap->vec3_data.x.value = 1;
    snap->vec3_data.y.value = 2;
    snap->vec3_data.z.value = 3;

    snap->uv3_data.v1.value = 1;
    snap->uv3_data.v2.y.value = 2;
    for (auto& it : snap->status_count)
    {
        it = 3;
    }

    msgpack::sbuffer sbuf;
    msgpack::pack(sbuf, snap);
    DMWriteFile("msgpack.bin", std::string(sbuf.data(), sbuf.size()));
}

TEST(msgpack_read, msgpack_read)
{
    auto data = DMLoadFile("msgpack.bin");
    std::shared_ptr<snapshot> snap(new snapshot());

    msgpack::object_handle oh = msgpack::unpack(data.data(), data.size());

    oh.get().convert(snap);
    std::cout << "msgpack.bin: " << oh.get() << std::endl;
}

TEST(pack_perf, pack_perf)
{
    snapshot snap;
    snap.current_frame_per_second = 1234;
    snap.current_time_scale = 6789;
    snap.entities_index.push_back(1);
    snap.entities_index.push_back(12);
    snap.entities_index.push_back(123);
    snap.random_state = "abcd";
    snap.entities_snapshot.LCreature._ability_point = 222;
    snap.entities_snapshot.LCreature._auto_recover_timer = 333;
    for (auto& it : snap.status_count)
    {
        it = 3;
    }

    for (int i = 0; i < 1000000; i++)
    {
        std::stringstream stream;
        msgpack::pack(stream, snap);
    }

    std::stringstream stream;
    msgpack::pack(stream, snap);

    std::string data(stream.str());
    auto crc = CDMCRC::CalculateDigest(data.data(), data.size());

    std::cout << "pack_perf: " << crc << std::endl;
}

TEST(pack_perf_sbuffer, pack_perf_sbuffer)
{
    snapshot snap;
    snap.current_frame_per_second = 1234;
    snap.current_time_scale = 6789;
    snap.entities_index.push_back(1);
    snap.entities_index.push_back(12);
    snap.entities_index.push_back(123);
    snap.random_state = "abcd";
    snap.entities_snapshot.LCreature._ability_point = 222;
    snap.entities_snapshot.LCreature._auto_recover_timer = 333;
    for (auto& it : snap.status_count)
    {
        it = 3;
    }

    for (int i = 0; i < 1000000; i++)
    {
        msgpack::sbuffer sbuf;
        msgpack::pack(sbuf, snap);
    }

    msgpack::sbuffer sbuf;
    msgpack::pack(sbuf, snap);

    auto crc = CDMCRC::CalculateDigest(sbuf.data(), sbuf.size());
    std::cout << "pack_perf_sbuffer: " << crc << std::endl;
}

TEST(unpack_perf, unpack_perf)
{
    snapshot snap;
    snap.current_frame_per_second = 1234;
    snap.current_time_scale = 6789;
    snap.entities_index.push_back(1);
    snap.entities_index.push_back(12);
    snap.entities_index.push_back(123);
    snap.random_state = "abcd";
    snap.entities_snapshot.LCreature._ability_point = 222;
    snap.entities_snapshot.LCreature._auto_recover_timer = 333;
    for (auto& it : snap.status_count)
    {
        it = 3;
    }
    std::stringstream stream;
    msgpack::pack(stream, snap);
    for (int i = 0; i < 1000000; i++)
    {
        std::string buffer(stream.str());
        msgpack::object_handle oh = msgpack::unpack(buffer.data(), buffer.size());
    }

    std::string buffer(stream.str());
    msgpack::object_handle oh = msgpack::unpack(buffer.data(), buffer.size());

    snapshot snap2;
    oh.get().convert(snap2);
    std::cout << "unpack_perf: " << oh.get() << std::endl;
}

