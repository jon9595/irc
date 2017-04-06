#ifndef _irc_client_H__
#define _irc_client_H__

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

///
/// Returns a socket file descriptor
/// \param host The host to connect to
/// \param port The port to connect to
/// \param res An empty addrinfo struct to be filled out by gettaddrinfo()
/// \returns A file descriptor to the connected socket from host, -1 for failure
///
int client_create_connection(const char *host, const char *port, struct addrinfo *res);

///
/// Destroys the socket connection to the server
/// \param fd The open socket's file descriptor
/// \param res The struct filled out by create_connection
/// \returns -1 for failure, 0 for success
///
int client_destroy_connection(int fd, struct addrinfo *res);
#endif
