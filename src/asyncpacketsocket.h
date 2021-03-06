/*
 * libjingle
 * Copyright 2004--2005, Google Inc.
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright notice, 
 *     this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *  3. The name of the author may not be used to endorse or promote products 
 *     derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef TXMPP_ASYNCPACKETSOCKET_H_
#define TXMPP_ASYNCPACKETSOCKET_H_

#ifndef NO_CONFIG_H
#include "config.h"
#endif

// TODO: Remove dependency on AsyncSocket. AsyncPacketSocket
// should be a pure interface.
#include "asyncsocket.h"

namespace txmpp {

// Provides the ability to receive packets asynchronously.  Sends are not
// buffered since it is acceptable to drop packets under high load.
class AsyncPacketSocket : public txmpp::has_slots<> {
 public:
  explicit AsyncPacketSocket(AsyncSocket* socket);
  virtual ~AsyncPacketSocket();

  // TODO: Remove these two methods.
  virtual int Bind(const SocketAddress& addr);
  virtual int Connect(const SocketAddress& addr);

  // Relevant socket methods:
  virtual SocketAddress GetLocalAddress() const;
  virtual SocketAddress GetRemoteAddress() const;
  virtual int Send(const void *pv, size_t cb);
  virtual int SendTo(const void *pv, size_t cb, const SocketAddress& addr);
  virtual int Close();

  virtual Socket::ConnState GetState() const;
  virtual int GetOption(Socket::Option opt, int* value);
  virtual int SetOption(Socket::Option opt, int value);
  virtual int GetError() const;
  virtual void SetError(int error);

  // Emitted each time a packet is read. Used only for UDP and
  // connected TCP sockets.
  signal4<AsyncPacketSocket*, const char*, size_t,
                   const SocketAddress&> SignalReadPacket;

  // Used only for connected TCP sockets.
  signal1<AsyncPacketSocket*> SignalConnect;
  signal2<AsyncPacketSocket*, int> SignalClose;

  // Used only for listening TCP sockets.
  signal2<AsyncPacketSocket*, AsyncPacketSocket*> SignalNewConnection;

 protected:
  AsyncSocket* socket_;
  DISALLOW_EVIL_CONSTRUCTORS(AsyncPacketSocket);
};

}  // namespace txmpp

#endif  // TXMPP_ASYNCPACKETSOCKET_H_
