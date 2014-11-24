#!/usr/bin/python
# -*- coding: utf8 -*-

# Copyright (c) 2013-2014, Muhammad Shahzad Shafi <shahzad at voip-demos dot com>
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted per Mozilla Public License v2.0.
#

import itv

data = "ﻒﺘﺤﺗ ﻢﻛﺎﺘﺑ ﺍﻼﻘﺗﺭﺎﻋ ﻒﻳ ﺕﻮﻨﺳ ﺎﻠﻳﻮﻣ ﺍﻸﺣﺩ ﺄﻣﺎﻣ ﺎﻠﻧﺎﺨﺒﻴﻧ ﻒﻳ ﺃﻮﻟ ﺎﻨﺘﺧﺎﺑﺎﺗ ﺮﺋﺎﺴﻳﺓ ﺖﻋﺩﺪﻳﺓ ﻢﻧﺫ ﺙﻭﺭﺓ 2011";

ret = itv.ascii_encode("", ':', data, 1)
if ret != None:
    print "Current Key: %s\n\nNext Key: %s\n\nResult: %s\n" % (ret[0], ret[1], ret[2])

ret = itv.ascii_decode(ret[0], ':', ret[2], 1)
if ret != None:
    print "Current Key: %s\n\nNext Key: %s\n\nResult: %s\n" % (ret[0], ret[1], ret[2])

