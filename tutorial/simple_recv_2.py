#!/usr/bin/env python
#
# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements.  See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership.  The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License.  You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied.  See the License for the
# specific language governing permissions and limitations
# under the License.
#

from proton_utils import ConnectionHandler, ReceiverHandler, Runtime

class Recv(ConnectionHandler, ReceiverHandler):
    def __init__(self, host, address):
        self.host = host
        self.address = address
        self.connect()

    def connect(self):
        self.conn = Runtime.DEFAULT.connect(self.host, handler=self)
        self.link = self.conn.receiver(self.address, handler=self)

    def received(self, receiver, handle, msg):
        print msg.body

    def closed(self, endpoint, error):
        if error: print "Closed due to %s" % error
        self.conn.close()

    def disconnected(self, conn):
        print "Disconnected, reconnecting..."
        self.connect()

    def run(self):
        Runtime.DEFAULT.run()

HOST  = "localhost:5672"
ADDRESS  = "examples"

try:
    Recv(HOST, ADDRESS).run()
except KeyboardInterrupt: pass


