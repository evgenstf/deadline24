#pragma once
#include <iostream>
#include <string>
#include <asio.hpp>

namespace deadgram {

namespace {

bool message_is_fail(const std::string& message) {
  if (message[0] == 'F' && message[1] == 'A' && message[2] == 'I' &&
      message[3] == 'L') {
    std::clog << message << std::endl;
    return true;
  }
  return false;
}

}  // namespace

const std::string kHostName = "universum.dl24";
const std::string kLogin = "team31";
const std::string kPassword = "wyifvropua";

class Deadgram {
public:
  Deadgram(const std::string& port, bool enable_logging = true):
        connection_(kHostName, port), port_(port), enable_logging_(enable_logging) {
    log("connecting to " + kHostName + ":" + port + " login: " + kLogin);
    asio::ip::tcp::no_delay opt(true);
    connection_.rdbuf()->set_option(opt);
    
    if (!has_connection()) {
      log("fail in connection", true);
      exit(1);
    }
    login();
    log("connection enabled", true);
  }

  const std::string& port() const { return port_; }

  bool has_connection() {
    return connection_.good();
  }

  void send_message(const std::string& message, bool need_ok = true) {
    assert(has_connection());
    log("send message: " + message);
    connection_ << message;
    connection_ << "\n";
  }

  std::string get_message(bool can_be_ok = false) {
    assert(has_connection());
    std::string message;
    getline(connection_, message);
    while ((message == "OK" || message_is_fail(message))  && !can_be_ok) {
      getline(connection_, message);
    }
    log("received message: " + message);
    return message;
  }

private:
  void login() {
    log("try to login", true);
    get_message();
    send_message(kLogin, false);
    log("sended login", true);
    get_message();
    send_message(kPassword, false);
    log("sended password", true);
  }

  void log(const std::string& message, bool force = false) const {
    if (force || enable_logging_) {
      std::clog << "   deadgram: " << message << '\n'; 
    }
  }

  asio::ip::tcp::iostream connection_;
  std::string port_;
  bool enable_logging_;
};

}  // namespace deadgram
