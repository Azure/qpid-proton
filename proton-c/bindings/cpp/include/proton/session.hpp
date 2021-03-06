#ifndef PROTON_CPP_SESSION_H
#define PROTON_CPP_SESSION_H

/*
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 */
#include "proton/export.hpp"
#include "proton/endpoint.hpp"
#include "proton/link.hpp"

#include "proton/types.h"
#include "proton/link.h"
#include <string>

struct pn_connection_t;

namespace proton {

class container;
class handler;
class transport;

/** A session is a collection of links */
class session : public counted_facade<pn_session_t, session, endpoint>
{
  public:
    /** Initiate local open, not complete till messaging_handler::on_session_opened()
     * or proton_handler::on_session_remote_open()
     */
    PN_CPP_EXTERN void open();

    /** Initiate local close, not complete till messaging_handler::on_session_closed()
     * or proton_handler::on_session_remote_close()
     */
    PN_CPP_EXTERN void close();

    /// Get connection
    PN_CPP_EXTERN class connection &connection();

    /** An un-opened receiver link, you can set link properties before calling open().
     *
     *@param name must be unique within a container, if empty a unique name is
     * generated beginning with connection().container().link_prefix()
     */
    PN_CPP_EXTERN receiver& create_receiver_link(const std::string& name=std::string());

    /** An un-opened sender link, you can set link properties before calling open().
     *
     *@param name must be unique within a container, if empty a unique name is
     * generated beginning with connection().container().link_prefix()
     */
    PN_CPP_EXTERN sender& create_sender_link(const std::string& name=std::string());

    /** Create and open a sender with target=addr and optional handler h */
    PN_CPP_EXTERN sender& create_sender(const std::string &addr, handler *h=0);

    /** Create and open a receiver with target=addr and optional handler h */
    PN_CPP_EXTERN receiver& create_receiver(const std::string &addr, bool dynamic=false, handler *h=0);

    /** Get the endpoint state */
    PN_CPP_EXTERN endpoint::state state();
};

}

#endif  /*!PROTON_CPP_SESSION_H*/
