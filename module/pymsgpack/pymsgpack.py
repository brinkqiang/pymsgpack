# -*- coding: utf-8 -*-
from pymsgpack import *

#a = CPlayerInfoData()
#a.test()
#b = a.to_msgpack()
#
#c = CPlayerInfoData()
#c.from_msgpack(b)
#d = c.to_msgpack()
#assert(b == d)

a = CMsgPackLoader()

a.load()

b = creature_attr_def()

b.maximun = "123"
b.minimun = "123"
b.use_centimeter = "123"

b.key = "123"
b.deft = "123"
b.type = "123"
b.desc = "123"
b.desc_bit = "123"

a.creature_attr_def_info.add("123" , b)

a.save()
a.load()