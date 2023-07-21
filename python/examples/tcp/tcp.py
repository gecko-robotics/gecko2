#!/usr/bin/env python3
# -*- coding: utf-8 -*-
##############################################
# The MIT License (MIT)
# Copyright (c) 2018 Kevin Walchko
# see LICENSE for full details
##############################################

from pygecko.multiprocessing import geckopy
from pygecko.multiprocessing.process import GeckoSimpleProcess
import time
# import json


def chew_up_cpu(interval):
    # chew up some cpu
    # return
    start = time.time()
    while (time.time() - start) < interval: 5*5


def publisher(**kwargs):
    geckopy.init_node()
    rate = geckopy.Rate(2)
    logger = geckopy.getLogger(__name__)

    p = geckopy.pubBinderTCP(
        kwargs.get('key'),
        kwargs.get('topic')
    )
    if p is None:
        logger.error("publisher is None")
        return

    # start = time.time()
    cnt = 0
    while geckopy.ok():
        # msg = json.dumps({'time': time.time() - start})
        msg = b"hello"
        p.publish(msg)  # topic msg

        logger.debug('[{}] published msg'.format(cnt))
        cnt += 1
        rate.sleep()
        # print(geckopy.is_shutdown())
    print('pub bye ...')
    # print(geckopy.is_shutdown())


def subscriber(**kwargs):
    geckopy.init_node(**kwargs)
    rate = geckopy.Rate(2)
    logger = geckopy.getLogger(__name__)

    topic = kwargs.get('topic')
    s = geckopy.subConnectTCP(
        kwargs.get('key'),
        kwargs.get('topic')
    )
    if s is None:
        logger.error("subscriber is None")
        return

    while not geckopy.is_shutdown():
        msg = s.recv_nb()
        if msg:
            logger.info("{}: {}".format(topic, msg.decode("utf-8")))
        chew_up_cpu(.1)
        rate.sleep()

    print('sub bye ...')


if __name__ == '__main__':
    # normally you wouldn't run this here, but is running else where
    # this is just for testing
    # from pygecko.transport import GeckoCore
    # core = GeckoCore()
    # core.start()

    # although I don't do anything with procs, because I reuse the variables
    # p and s below, they will kill the processes when new process are created
    # using those names. Appending them to procs allows me to keep them alive
    # until the program ends
    procs = []

    # for topic in ['ryan', 'mike', 'sammie', 'scott']:
    for topic in ['ryan']:
        # info to pass to processes
        args = {
            "key": "local",
            'topic': topic
        }

        p = GeckoSimpleProcess()
        p.start(func=publisher, name='pub_{}'.format(topic), kwargs=args)
        procs.append(p)

        s = GeckoSimpleProcess()
        s.start(func=subscriber, name='sub_{}'.format(topic), kwargs=args)
        procs.append(s)

        s = GeckoSimpleProcess()
        s.start(func=subscriber, name='sub_{}_2'.format(topic), kwargs=args)
        procs.append(s)

    while True:
        try:
            time.sleep(1)
            for p in procs:
                if not p.is_alive():
                    procs.remove(p)
                    p.join(1)
                    print("dead:", p)
            if len(procs) == 0:
                break

        except KeyboardInterrupt:
            print('main process got ctrl-c')
            break
        except Exception as e:
            print(e)
            print("bye ...")
            break
        finally:
            for p in procs:
                procs.remove(p)
                p.join(1)
