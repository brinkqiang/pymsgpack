# -*- coding: utf-8 -*-
import pymsgpack

obj = pymsgpack.CPlayer(1, "zhangsan")

obj.Init()
print("Name=", obj.GetName(), "Level=", obj.GetLevel(), "HP=", obj.GetHP())
obj.AddHP(100)
print("Name=", obj.GetName(), "Level=", obj.GetLevel(), "HP=", obj.GetHP())