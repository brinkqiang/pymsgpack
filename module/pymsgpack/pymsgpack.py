# -*- coding: utf-8 -*-
from pymsgpack import *

a = CPlayerInfoData()
a.test()
b = a.to_msgpack()

c = CPlayerInfoData()
c.from_msgpack(b)
d = c.to_msgpack()
assert(b == d)
