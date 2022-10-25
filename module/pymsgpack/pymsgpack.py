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

# -*- coding: utf-8 -*-
a = CMsgPackLoader()

a.load()

b = creature_attr_def()

b.maximun = "123"
b.minimun = "123"
b.use_centimeter = "123"

b.key = "123"
b.defs = "123"
b.type = "123"
b.desc = "123"
b.desc_bit = "123"

a.creature_attr_def_info.add("123" , b)

d = a.creature_attr_def_info.get("123")
print("get 123",d)
d.defs = "1234"
print("get 123 defs:",d.defs)

e = a.creature_attr_def_info.get("1234")
print("get 1234",e)

c = a.creature_attr_def_info.to_msgpack()

def list_to_hex_string(list_data):
    list_str = ''
    for x in list_data:
        list_str += x.encode('hex')
    return list_str

print(list_to_hex_string(c))
a.save()
a.load()