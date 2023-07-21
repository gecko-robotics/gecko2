#!/usr/bin/env python3
# -*- coding: utf-8 -*-
##############################################
# The MIT License (MIT)
# Copyright (c) 2018 Kevin Walchko
# see LICENSE for full details
##############################################

from pygecko.multiprocessing import geckopy
from pygecko.multiprocessing import GeckoSimpleProcess
from pygecko.transport.protocols import MsgPack
import time
# from pygecko import Vector, IMU
from pygecko.messages import vec_t, imu_st




def pub(**kwargs):
    geckopy.init_node(**kwargs)
    rate = geckopy.Rate(2)

    p = geckopy.pubBinderTCP("local", "bob2")
    if (p == None):
        print("ERROR setting up publisher")
        return
    cnt = 0
    v = vec_t(1,2,3)
    m = imu_st(v,v,v)
    while not geckopy.is_shutdown():
        # m = imu_st(v,v,v)
        p.publish(m)
        print("sent")
        rate.sleep()
        cnt += 1


def sub(**kwargs):
    geckopy.init_node(**kwargs)
    rate = geckopy.Rate(2)

    s = geckopy.subConnectTCP("local", "bob2")
    if (s == None):
        print("ERROR setting up subscriber")
        return
    cnt = 0
    while not geckopy.is_shutdown():
        data = s.recv_nb()
        print("sub:", data)
        print('-'*40)
        rate.sleep()


if __name__ == '__main__':
    # sub()
    pub()
