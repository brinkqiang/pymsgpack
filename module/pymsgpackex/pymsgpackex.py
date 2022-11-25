# -*- coding: utf-8 -*-
from pymsgpackex import *

msg = GetMsgPackLoader()

msg.Load()

node = creature_attr_def()

fix = Fix32()
fix.value = 999
node.maximun = fix
fix.value = 1
node.minimun = fix

node.use_centimeter = True

node.key = "tom"
node.defs = "default"
node.type = "fix32"
node.desc = 1.23456789
node.desc_bit = 888

msg.creature_attr_def_info.add("tom" , node)

tom = msg.creature_attr_def_info.get("tom")
print("get tom", tom)
tom.defs = "default_test"
print("get tom defs:", tom.defs)

jack = msg.creature_attr_def_info.get("jack")
print("get jack", jack)

reward_exp = msg.creature_attr_def_info.get("reward_exp")

print(reward_exp.key)
print(reward_exp.maximun)
print(reward_exp.defs)
print(reward_exp.desc)

data = msg.creature_attr_def_info.to_msgpack()

print(len(data))
msg.Save()
msg.Load()
