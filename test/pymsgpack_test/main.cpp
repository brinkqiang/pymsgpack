#include "gtest.h"
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>
#include <algorithm>
#include "dmformat.h"


class frame_dmpytest : public testing::Test
{
public:
    virtual void SetUp()
    {
        pymsgpack = pybind11::module_::import("pymsgpack");
        obj = pymsgpack.attr("CPlayer")(1, "zhangsan");
    }
    virtual void TearDown()
    {

    }
protected:
    pybind11::scoped_interpreter guard;
    pybind11::module_ pymsgpack;
    pybind11::object obj;

    const int PERF_COUNT = (100 * 10000);
};


TEST_F(frame_dmpytest, dmpytest_pymsgpack)
{
    auto GetName = obj.attr("GetName");
    auto GetLevel = obj.attr("GetLevel");
    auto GetHP = obj.attr("GetHP");

    obj.attr("Init")();
    fmt::print("Name={} Level={} HP={}\n", GetName().cast<std::string>(), GetLevel().cast<int>(), GetHP().cast<int64_t>());
    obj.attr("AddHP")(100);
    fmt::print("Name={} Level={} HP={}\n", GetName().cast<std::string>(), GetLevel().cast<int>(), GetHP().cast<int64_t>());
}

PYBIND11_EMBEDDED_MODULE(dmpymath, m) {
    // `m` is a `py::module_` which is used to bind functions and classes
    m.def("add", [](int a, int b) {
        return a + b;
        });
}

TEST_F(frame_dmpytest, dmpytest_perf)
{
    auto dmpymath = pybind11::module_::import("dmpymath");
    auto add = dmpymath.attr("add");

    uint64_t total = 0;
    for (int i = 0; i < PERF_COUNT; i++)
    {
        int num = add(1, 2).cast<int>();
        total += num;
    }

    fmt::print("count={} total={}\n", PERF_COUNT, total);
}
