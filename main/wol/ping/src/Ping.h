//
// Created by fabian on 23.06.19.
//
#include <string>

#ifndef C_PROJECT_PING_H
#define C_PROJECT_PING_H

/**
 * Sends ICMP package to a given IP address and checks whether there is a response.
 *
 * @param addr (IP address of target)
 * @param timeout (in milliseconds)
 * @return true if target response to the ICMP package else false
 */
bool sendPing(const char *addr, int timeout);

#endif //C_PROJECT_PING_H
