# -*- coding: utf-8 -*-
from pymsgpackex import *

a = CMsgPackLoader()

a.Load()

b = creature_attr_def()

fix = Fix32()
fix.value = 999
b.maximun = fix
fix.value = 1
b.minimun = fix

b.use_centimeter = True

b.key = "tom"
b.defs = "default"
b.type = "fix32"
b.desc = 1.23456789
b.desc_bit = 888

a.creature_attr_def_info.add("tom" , b)

d = a.creature_attr_def_info.get("tom")
print("get tom",d)
d.defs = "default_test"
print("get tom defs:",d.defs)

e = a.creature_attr_def_info.get("jack")
print("get jack",e)

c = a.creature_attr_def_info.to_msgpack()

j = a.creature_attr_def_info.get("reward_exp")

print(j.key)
print(j.maximun)
print(j.defs)

print(len(c))
a.Save()
a.Load()
