##############################################
# The MIT License (MIT)
# Copyright (c) 2014 Kevin Walchko
# see LICENSE for full details
##############################################
#
# Kevin J. Walchko 13 Oct 2014
#
# see http://zeromq.org for more info
# http://zguide.zeromq.org/py:all

import zmq
import time
from pygecko.transport.zmq_base import Base
from pygecko.transport.zmq_base import ZMQError


class Pub(Base):
    """
    Simple publisher
    """
    def __init__(self):
        """
        Publishes messages on a topic.
        """
        Base.__init__(self, zmq.PUB)

    def __del__(self):
        self.socket.close()

    def publish(self, msg):
        """
        in: topic, message
        out: none
        """
        self.socket.send(msg)


class Sub(Base):
    """
    Simple subscriber that read messages on a topic (which are defined by port
    number)
    """

    def __init__(self):
        """
        Simple subscriber. Topics that it listens for are based on port number
        and not a topic string it listens for
        """
        Base.__init__(self, zmq.SUB)

        try:
            self.socket = self.ctx.socket(zmq.SUB)
            self.socket.setsockopt(zmq.SUBSCRIBE, b'')
            self.topics = b''

        except Exception as e:
            error = '[-] Sub Error, {0!s}'.format((str(e)))
            raise ZMQError(error)

    def __del__(self):
        self.socket.setsockopt(zmq.UNSUBSCRIBE, b'')
        self.socket.close()

    def recv_nb(self):
        """
        Calls recv(flags) with flags=zmq.NOBLOCK to implement non-blocking
        (or zmq.DONTWAIT)
        """
        return self.recv(flags=zmq.NOBLOCK)

    def recv(self, flags=0):
        """
        Implements a recv_poll(). By default, this does not block.
        """
        msg = None
        try:
            # topic, jmsg = self.socket.recv_multipart(flags=flags)
            msg = self.socket.recv(flags=flags)
        except zmq.Again:
            # no message has arrived yet or not connected to server
            # print(e)
            time.sleep(0.01)
        except Exception:
            # something else is wrong
            # print(e)
            raise
        return msg
        # return self.recv_poll()



############################################################################
# class Pub(Base):
#     """
#     Simple publisher
#     """
#     def __init__(self):
#         """
#         Publishes messages on a topic.
#         """
#         Base.__init__(self, zmq.PUB)
#
#     def __del__(self):
#         self.socket.close()
#
#     def publish(self, msg):
#         """
#         in: topic, message
#         out: none
#         """
#         self.socket.send(msg)
#
#
# class Sub(Base):
#     """
#     Simple subscriber that read messages on a topic(s)
#     """
#
#     # def __init__(self, topics=None):
#     def __init__(self):
#         """
#         topics: an array of topics, ex ['hello', 'cool messages'] or None to subscribe to all messages
#         unpack: a function to deserialize messages if necessary
#         """
#         Base.__init__(self, zmq.SUB)
#
#         try:
#             self.socket = self.ctx.socket(zmq.SUB)
#
#             # manage subscriptions
#             # can also use: self.socket.subscribe(topic) or unsubscribe()
#             # if topics is None:
#             #     # print("[>] Receiving messages on ALL topics...")
#             self.socket.setsockopt(zmq.SUBSCRIBE, b'')
#             self.topics = b''
#             # else:
#             #     if type(topics) is list:
#             #         pass
#             #     else:
#             #         raise Exception('topics must be a list')
#             #
#             #     self.topics = topics
#             #     for t in topics:
#             #         print("[>] Subscribed to messages on topics: {} ...".format(t))
#             #         self.socket.setsockopt(zmq.SUBSCRIBE, t.encode('utf-8'))
#
#         except Exception as e:
#             error = '[-] Sub Error, {0!s}'.format((str(e)))
#             raise ZMQError(error)
#
#     def __del__(self):
#         # if self.topics is None:
#         self.socket.setsockopt(zmq.UNSUBSCRIBE, b'')
#         # else:
#         #     for t in self.topics:
#         #         self.socket.setsockopt(zmq.UNSUBSCRIBE, t.encode('utf-8'))
#         self.socket.close()
#
#     def recv_nb(self):
#         """
#         Calls recv(flags) with flags=zmq.NOBLOCK to implement non-blocking
#         (or zmq.DONTWAIT)
#         """
#         return self.recv(flags=zmq.NOBLOCK)
#
#     def recv(self, flags=0):
#         """
#         Implements a recv_multipart(flags). By default, this blocks.
#         """
#         msg = None
#         try:
#             # topic, jmsg = self.socket.recv_multipart(flags=flags)
#             msg = self.socket.recv(flags=flags)
#         except zmq.Again:
#             # no message has arrived yet or not connected to server
#             # print(e)
#             time.sleep(0.01)
#         except Exception:
#             # something else is wrong
#             # print(e)
#             raise
#         return msg
#

# def pub(self, topic, msg):
#     """
#     in: topic, message
#     out: none
#     """
#     if topic not in self.topics:
#         raise Exception("Pub.pub: {} is an invalide topic".format(topic))
#     # jmsg = serialize(msg)
#
#     # if self.pack:
#     #     jmsg = msgpack.packb(msg, default=self.pack, use_bin_type=True, strict_types=True)
#     # else:
#     #     jmsg = msgpack.packb(msg, use_bin_type=True, strict_types=True)
#
#     jmsg = self.packer.pack(msg)
#
#     # self.socket.send_multipart([topic.encode('ascii'), jmsg.encode('ascii')])
#     # done = True
#     # while done:
#     #     # done = self.socket.send_multipart([topic.encode('ascii'), jmsg])
#     #     done = self.socket.send_multipart([topic.encode('utf-8'), jmsg])
#     #     # done = self.socket.send(jmsg)
#     # print('pub >>', topic.encode('ascii'))
#     self.socket.send_multipart([topic.encode('utf-8'), jmsg])

    # def raw_recv(self, flags=0):
    #     return self.socket.recv_multipart(flags=flags)


# move to zmq classes
# import zmq
# from pygecko.transport.zmqclass import Base
#
# class Rep(Base):
#     """
#     Reply?
#     """
#     def __init__(self):
#         Base.__init__(self)
#         self.socket = self.ctx.socket(zmq.REP)
#
#     def __del__(self):
#         """
#         wtf! I need this or it hangs
#         """
#         # print("*** rep out sucka!!! ***")
#         # pass
#         self.close()
#
#     def listen_nb(self, callback):
#         """
#         checks to see if a request needs to be serviced
#         callback: a function to handle a request message and return the answer.
#             The function must be able to handle a message it didn't expect.
#             Since there are no topics associated with this, a user might send
#             some crazy message
#
#             callback(message) -> answer
#
#         returns True if serviced, False if not
#         """
#         # print 'listen'
#         ret = False
#         try:
#             jmsg = self.socket.recv_multipart(flags=zmq.NOBLOCK)[0]
#             print("*** {} ***".format(jmsg))
#             msg = self.packer.unpack(jmsg)
#
#             msg = callback(msg)
#
#             jmsg = self.packer.pack(msg)
#             self.socket.send(jmsg)
#             ret = True
#
#         except zmq.Again as e:
#             # no response yet or server not up and running yet
#             # time.sleep(0.001)
#             # print("*** no reply ***")
#             pass
#         except Exception as e:
#             # something else is wrong
#             raise
#
#         return ret
#
#     def listen(self, callback):
#         """
#         The same as listen_nb() but this one blocks until a request is made.
#
#         this blocks ... utility?
#         """
#         while True:
#             # try:
#             jmsg = self.socket.recv_multipart()[0]
#             msg = self.packer.unpack(jmsg)
#
#             msg = callback(msg)
#
#             jmsg = self.packer.pack(msg)
#             self.socket.send(jmsg)
#             # except zmq.Again as e:
#             #     # no response yet or server not up and running yet
#             #     time.sleep(0.01)
#             # except Exception as e:
#             #     # something else is wrong
#             #     raise
#
# class Req(Base):
#     """
#     Request?
#     """
#     def __init__(self):
#         Base.__init__(self)
#         self.socket = self.ctx.socket(zmq.REQ)
#
#     def __del__(self):
#         pass
#
#     def get_nb(self):
#         """
#         automagically sets flags for nonblocking and calls the recv method. If
#         no answer is received, then None is returned
#         """
#         return self.get(flags=zmq.NOBLOCK)
#
#     def get(self, msg, flags=0):
#         """
#         flags=zmq.NOBLOCK to implement non-blocking or zmq.DONTWAIT
#
#         If no flags are set, this blocks until a returned message is received.
#         """
#         jmsg = self.packer.pack(msg)
#         msg = None
#         self.socket.send(jmsg)
#         try:
#             jmsg = self.socket.recv_multipart(flags=flags)[0]
#             msg = self.packer.unpack(jmsg)
#         except zmq.Again as e:
#             # no response yet or server not up and running yet
#             time.sleep(0.001)
#         except Exception as e:
#             # something else is wrong
#             raise
#         return msg










# class SubNB(Sub):
#     def __init__(self, cb_func, topics=None, unpack=None):
#         Sub.__init__(self, topics, unpack,cb_func=cb_func)
#     def recv(self):
#         super.recv(flags=zmq.NOBLOCK)
# class SubNB(Sub):
#     """
#     Simple subscriber that read messages on a topic(s).
#
#     This is non-blocking and calls a call backfunction (cb_func) when a message
#     is finally received. The blind non-blocking consumes around 0.5% (max) more
#     cpu percentage than the blocking version. So for low number of node, not
#     a big deal.
#
#     Below
#       subscribe is blocking
#       subscribe2 in non-blocking
#
#     each subscribe type calls chew_up_cpu() 4 times which consumes around
#     3.4% ... anything more than that is attributed to block/non-block
#
#     GeckoCore is the hub and does a lot of data collection, plus passing
#     messages between inputs/outputs
#
#     +------------------------------
#     | Alive processes: 10
#     +------------------------------
#     | subscribe2[23117]............. cpu:   3.7%    mem:   0.06%
#     | subscribe2[23119]............. cpu:   3.7%    mem:   0.05%
#     | subscribe[23121].............. cpu:   3.5%    mem:   0.05%
#     | publish[23115]................ cpu:   0.9%    mem:   0.05%
#     | GeckoCore[23106].............. cpu:   6.2%    mem:   0.05%
#     | publish[23114]................ cpu:   1.0%    mem:   0.05%
#     | subscribe2[23116]............. cpu:   3.6%    mem:   0.06%
#     | subscribe2[23118]............. cpu:   3.9%    mem:   0.05%
#     | subscribe2[23120]............. cpu:   3.7%    mem:   0.05%
#     | subscribe[23122].............. cpu:   3.5%    mem:   0.05%
#     ------------------------------
#     """
#     unpack = None
#
#     def __init__(self, cb_func, topics=None, unpack=None):
#         """
#         topics: an array of topics, ex ['hello', 'cool messages']
#         unpack: a function to deserialize messages if necessary
#         """
#         Sub.__init__(self, topics, unpack)
#
#         self.cb_func = cb_func
#
#     def recv(self):
#         """
#         flags=zmq.NOBLOCK to implement non-blocking
#         """
#         try:
#             topic, jmsg = self.socket.recv_multipart(flags=zmq.NOBLOCK)
#             # if self.unpack:
#             #     msg = msgpack.unpackb(jmsg, ext_hook=self.unpack, raw=False)
#             # else:
#             #     msg = msgpack.unpackb(jmsg, raw=False)
#             msg = self.packer.unpack(jmsg)
#
#             self.cb_func(topic, msg)
#         except zmq.Again as e:
#             # no message has arrived yet or not connected to server
#             # print(e)
#             pass
#         except Exception as e:
#             # something else is wrong
#             # print(e)
#             raise
#         return

    # def raw_recv(self, flags=0):
    #     return self.socket.recv_multipart(flags=flags)





    # def recv(self):
    #     # check to see if there is read, write, or erros
    #
    #     topic = None
    #     msg = None
    #
    #     zmq.zmq_poll([(self.socket, zmq.POLLIN,)], 10)
    #     socks = self.poller.poll(10)
    #     print('socks', socks)
    #     socks = dict(socks)
    #     topic, jmsg = self.socket.recv_multipart()
    #     print(topic)
    #
    #     print('socks:', socks)
    #
    #     cnt = 0
    #     if socks.get(self.socket) == zmq.POLLIN:
    #         print('pollin:')
    #         try:
    #             for i in range(10):
    #                 topic, jmsg = self.socket.recv_multipart()
    #                 msg = deserialize(jmsg)
    #                 cnt = i
    #         except:
    #             pass
    #
    #         print('recv looped', cnt)
    #     # print(topic, msg)
    #
    #     return topic, msg


# class ServiceProvider(Base):
#     """
#     Provides a service
#     """
#     def __init__(self, bind_to):
#         Base.__init__(self)
#         self.socket = self.ctx.socket(zmq.REP)
#         # tcp = 'tcp://' + bind_to[0] + ':' + str(bind_to[1])
#         # tcp = self.getAddress(bind_to)
#         # self.socket.bind(tcp)
#
#     def __del__(self):
#         self.socket.close()
#         # self._stop()
#
#     def listen(self, callback):
#         # print 'listen'
#         while True:
#             jmsg = self.socket.recv()
#             msg = json.loads(jmsg)
#
#             ans = callback(msg)
#
#             jmsg = json.dumps(ans)
#             self.socket.send(jmsg)
#
#
# class ServiceClient(Base):
#     """
#     Client socket to get a response back from a service provider
#     """
#     def __init__(self, bind_to):
#         Base.__init__(self)
#         self.socket = self.ctx.socket(zmq.REQ)
#         # tcp = 'tcp://' + bind_to[0] + ':' + str(bind_to[1])
#         # tcp = self.getAddress(bind_to)
#         # self.socket.connect(tcp)
#
#     def __del__(self):
#         self.socket.close()
#         # self._stop()
#
#     def get(self, msg):
#         jmsg = json.dumps(msg)
#         self.socket.send(jmsg)
#         jmsg = self.socket.recv()
#         msg = json.loads(jmsg)
#         return msg
# class MsgPack(object):
#     def pack(self, data):
#         return msgpack.packb(data, use_bin_type=True, strict_types=True)
#
#     def unpack(self, data):
#         return msgpack.unpackb(data, raw=False)
#
#
# class MsgPackCustom(object):
#     def __init__(self, packer, unpacker):
#         self.packer = packer
#         self.ext_unpack = unpacker
#
#     def pack(self, data):
#         return data = msgpack.packb(data, use_bin_type=True, strict_types=True,default=self.packer)
#
#     def unpack(self, data):
#         return data = msgpack.unpackb(data, raw=False, ext_hook=self.ext_unpack)
#
#
# class Pickle(object):
#     def pack(self, data):
#         return pickle.dumps(data)
#     def unpack(self, data):
#         return pickle.loads(data)
#
#
# class Json(object):
#     def pack(self, data):
#         """
#         json doesn't know how to handle namedtuples, so store class id for
#         unpack
#         """
#         if type(data) in known_types:
#             d = data._asdict()
#             d['type'] = unpack_types[type(data)]
#         else:
#             d = data
#         return json.dumps(d)
#
#     def unpack(self, data):
#         """
#         if data is an ordered dictionary AND it has class id, then create the
#         message using the class id
#         """
#         d = json.loads(data)
#         if type(data) is OrderedDict:
#             if 'type' in d:
#                 cls = unpack_types[d['type']]
#                 d.pop('type', None)
#                 d = cls(*d.values())
#         return d

#
# class ZMQError(Exception):
#     pass
#
#
# class Base(object):
#     """
#     Base class for other derived pub/sub/service classes
#     """
#     # ctx = zmq.Context()
#     socket = None
#     pack = None
#
#     def __init__(self, kind=None):
#         self.ctx = zmq.Context()
#         self.packer = Pickle()
#         self.socket = None
#         # self.socket = self.ctx.socket(kind)
#
#     def __del__(self):
#         self.close()
#         # self.ctx.term()
#         # self.socket.close()
#         # print('[<] shutting down {}'.format(type(self).__name__))
#
#     def close(self):
#         self.socket.close()
#         self.ctx.term()
#         print('[<] shutting down {}'.format(type(self).__name__))
#
#     def bind(self, addr, hwm=None, queue_size=10):
#         """
#         Binds a socket to an addr. Only one socket can bind.
#         Usually pub binds and sub connects, but not always!
#
#         in:
#           addr as tcp or uds
#           hwm (high water mark) a int that limits buffer length
#           queue_size is the same as hwm
#         out: none
#         """
#         print(type(self).__name__, 'bind to {}'.format(addr))
#         self.socket.bind(addr)
#         if hwm:
#             self.socket.set_hwm(hwm)
#         elif queue_size:
#             self.socket.set_hwm(queue_size)
#
#     def connect(self, addr, hwm=None, queue_size=10):
#         """
#         Connects a socket to an addr. Many different sockets can connect.
#         Usually pub binds and sub connects, but not always!
#
#         in: addr as tcp or uds, hwm (high water mark) a int that limits buffer length
#         out: none
#         """
#         print(type(self).__name__, 'connect to {}'.format(addr))
#         self.socket.connect(addr)
#         if hwm:
#             self.socket.set_hwm(hwm)
#         elif queue_size:
#             self.socket.set_hwm(queue_size)
