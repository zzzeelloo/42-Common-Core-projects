[← Back to 42 Common Core](../README.md)

# ft_irc

[![42](https://img.shields.io/badge/42-Project-blue)](https://42.fr)
[![C++98](https://img.shields.io/badge/Language-C%2B%2B98-blue.svg)](https://en.cppreference.com/)

An IRC server written in C++98. It handles many clients at once on a single thread, with non-blocking sockets and `poll()`, and it works with a standard IRC client such as irssi, WeeChat or HexChat.

## Features

- TCP server, IPv4, non-blocking I/O, one `poll()` loop for every file descriptor
- Password authentication and client registration: `PASS`, `NICK`, `USER`, `CAP`
- Channels: `JOIN`, `PART`, `TOPIC`, `WHO`
- Messages: `PRIVMSG` and `NOTICE` to users and channels
- Operator commands: `KICK`, `INVITE`, `MODE`
- Channel modes: `i` (invite only), `t` (topic restricted to operators), `k` (key), `o` (operator), `l` (user limit)
- Keep-alive and disconnects: `PING`, `QUIT`
- Numeric replies in the RFC 1459 / 2812 format

## Architecture

| Folder | Role |
|---|---|
| `src/core/server/` | Socket setup, `poll()` loop, command dispatch and replies |
| `src/core/user/` | Client state: registration, nickname, receive buffer |
| `src/core/channel/` | Channel members, operators, topic and modes |
| `src/core/request/` | Parsing a raw IRC line into a command and its parameters |
| `src/core/responseCodes/` | IRC numeric reply codes |

## Build and run

```bash
make
./ircserv <port> <password>
```

Connect with any IRC client, or quickly with netcat:

```bash
nc -C localhost 6667
PASS mypassword
NICK alice
USER alice 0 * :Alice
JOIN #42
PRIVMSG #42 :hello
```

## Team

Group project at 42 Lyon with **mbah**.
