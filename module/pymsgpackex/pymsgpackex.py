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

print(type(reward_exp.key))
print(type(reward_exp.maximun))
print(type(reward_exp.defs))
print(type(reward_exp.desc))

data = msg.creature_attr_def_info.to_msgpack()

print(len(data))
msg.Save()
msg.Load()

model = model()
model.model_id = 99
model.name = "abc"
model.meshes.append("123")
model.skeleton = "sk"
model.graph = "gr"
model.physics_meshes.append("123")
model.pickbound.append(91.0)
model.effect_path = "eff"

att = attached_model()
att.ObjName = "zhangsan"
att.BoneName = "xyz"
att.BasePointName = "point"
att.Offset.append(1.1)
att.Rotation.append(1.2)
att.Scale = 1.3
att.ModelID = 99

model.attached_model.append(att)
model.repository = "repos";
model.not_use_physics_meshes = False
model.box.append(1.5)

msg.model_info.add(99 , model)

model2 = msg.model_info.get(99)
print("get model2 name: ", model2.name)
