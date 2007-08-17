#ifndef __SOCKET_LOGGER_H__
#define __SOCKET_LOGGER_H__

/** Socket Logger Initialization parameters. */
typedef struct tSockLoggerInitParams
{
	/** The log server, can be a IP address or a generic host name. */
	char* 	server;
	/** The port of the log server. */
	int		port;
}tSockLoggerInitParams;

#endif // __SOCKET_LOGGER_H__
