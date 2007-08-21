/**
 * \file Platform Layer for socket functions.
 * */
#ifndef __PLSOCKET_H__
#define __PLSOCKET_H__

/** Abstract handle for socket. */
typedef void* tPLSocket;

/** Function to create a \b connected socket.
 * \param [in]  server 	The log server.
 * \param [in]  port	The log server port.
 * \param [out] sock	The socket handle.
 * \returns -1 on failure and \a sock will be -1 , or else 0 on success and sock will be non zero.
 * */
int PLCreateConnectedSocket(const char* server, int port, tPLSocket *sock);

/** Send data over socket.
 * \param [in] tPLSocket 	The socket handle created via \ref CreateConnectedSocket.
 * \param [in] data			The data to send. 
 * \param [in] dataSize		The size of data.
 * \return On success, the amount of bytes sent, -1 otherwise.
 * */
int PLSockSend(tPLSocket sock,const void* data,const int dataSize);

/** Close the Socket.
 * \param [in,out] sock	The socket handle created via \ref CreateConnectedSocket.
 * */
void PLDestroySocket(tPLSocket * sock);

#endif // __PLSOCKET_H__
