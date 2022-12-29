
#ifndef __MODEL_MSGPACK_H_INCLUDE__
#define __MODEL_MSGPACK_H_INCLUDE__

#include "msgpack_variant.hpp"

typedef std::vector<char> vec_bin;

struct attached_model
{
    // export_begin
    attached_model() {}
    virtual ~attached_model() {}
    std::string ObjName;
    std::string BoneName;
    std::string BasePointName;
    std::vector<double> Offset;
    std::vector<double> Rotation;
    double Scale;
    std::int64_t ModelID;

    // export_end
    MSGPACK_DEFINE_MAP(ObjName, BoneName, BasePointName, Offset, Rotation, Scale, ModelID);
};

struct model
{
    // export_begin
    model() {}
    virtual ~model() {}
    std::int64_t model_id;
    std::string name;
    std::vector<std::string> meshes;
    std::string skeleton;
    std::string graph;
    std::vector<std::string> physics_meshes;
    std::vector<double> pickbound;
    std::string effect_path;
    std::vector<attached_model> attached_model;
    std::string repository;
    bool not_use_physics_meshes = false;
    std::vector<double> box;

    // export_end
    MSGPACK_DEFINE_MAP(model_id, name, meshes, skeleton, graph, physics_meshes, pickbound, effect_path, attached_model, repository, not_use_physics_meshes, box);
};

typedef std::map<std::int64_t, model> map_model;

struct model_data
{
    // export_begin
    map_model data;
    // export_end
    MSGPACK_DEFINE_MAP(data);

    // export_begin
    model_data() {}
    virtual ~model_data() {}

    void add(const std::int64_t key, model& v);

    const model* get(const std::int64_t key);

    vec_bin to_msgpack();

    void from_msgpack(const vec_bin& data);

    bool load();
    bool save();
    // export_end
};


#endif // __MODEL_MSGPACK_H_INCLUDE__