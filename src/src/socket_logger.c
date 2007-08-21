#include "socket_logger_impl.h"

#ifndef _WIN32
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#else
#include <winsock2.h>
#endif


#ifdef _WIN32
	#define  vsnprintf(buf,buf_size,fmt,ap) _vsnprintf(buf,buf_size,fmt,ap);
#endif


/** The maximum size of the log. */
#define BUF_MAX 1024

/** Helper function to print the logs to a buffer and send to a socket or
 * other consumer */
static int sSendToSock(LogWriter *_this,const LogLevel logLevel,
#ifdef VARIADIC_MACROS
		const char* moduleName,
		const char* file,const char* funcName, const int lineNum, 
#endif
		const char* fmt,va_list ap);

int sSockFuncLogEntry(LogWriter *_this,const char* funcName);

int sSockFuncLogExit(LogWriter* _this,const char* funcName,const int lineNumber);

int sSockLoggerDeInit(LogWriter* _this);

/* helper function to get the log prefix */
static const char* sGetLogPrefix(const LogLevel logLevel);

typedef struct SockLogWriter
{
	LogWriter	base;
	int			sock;
}SockLogWriter;

static SockLogWriter sSockLogWriter = 
{
	.base.log 			= sSendToSock,
	.base.logFuncEntry 	= sSockFuncLogEntry,
	.base.logFuncExit	= sSockFuncLogExit,
	.base.loggerDeInit	= sSockLoggerDeInit,
	.sock				= 0
};


/** Helper function to connect to a log server, 
  \param [in] server The server to connect to, ex : 192.168.10.20
  \param [in] port	 The Port of the server.
  */
static int ConnectToLogServer(char* server,int port)
{
	struct sockaddr_in their_addr; // connector's address information 
	int sock = -1;

	if ((sock = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		return -1;
	}

	their_addr.sin_family = AF_INET;    // host byte order 
	their_addr.sin_port = htons( port );  // short, network byte order 
	their_addr.sin_addr.s_addr = inet_addr( server );
	memset(&(their_addr.sin_zero), '\0', 8);  // zero the rest of the struct 

	if (connect(sock, (struct sockaddr *)&their_addr,
		sizeof(struct sockaddr)) == -1) 
	{
		close(sock);
		perror("connect");
		return -1;
	}

	return sock;
}
int InitSocketLogger(LogWriter** logWriter,tSockLoggerInitParams *initParams)
{
	if(!logWriter || !initParams || !initParams->server)
	{
		fprintf(stderr,"Invalid args to function InitSocketLogger\n");
		return -1;
	}
	*logWriter = 0;

	if (sSockLogWriter.sock)
	{
		sSockLoggerDeInit((LogWriter*)&sSockLogWriter);
	}
	sSockLogWriter.sock = ConnectToLogServer(initParams->server,initParams->port);
	if( -1 == sSockLogWriter.sock )
	{
		fprintf(stderr,"could not connect to log server %s:%d",initParams->server,initParams->port);
		return -1;
	}
	*logWriter = (LogWriter*)&sSockLogWriter;
	return 0; // success!
}

/** Helper function to print the logs to a buffer and send to a socket or
 * other consumer */
static int sSendToSock(LogWriter *_this,const LogLevel logLevel,
#ifdef VARIADIC_MACROS
		const char* moduleName,
		const char* file,const char* funcName, const int lineNum, 
#endif
		const char* fmt,va_list ap)
{
	SockLogWriter *slw = (SockLogWriter*) _this;
	if(!_this || (-1 == slw->sock))
	{
		fprintf(stderr,"invalid args for sSendToSock");
		return -1;
	}
	else
	{
		char buf[BUF_MAX];
		int bytes = 0;
#ifdef VARIADIC_MACROS
		bytes = snprintf(buf,BUF_MAX-1,"\n%s:%s:%s:%s:%d:",sGetLogPrefix(logLevel),
				moduleName,file,funcName,lineNum);
#else
		bytes = snprintf(buf,BUF_MAX-1,"\n%s",sGetLogPrefix(logLevel));
#endif
		// to be on safer side, check if required size is available.
		if(bytes < (BUF_MAX -1) )
			bytes += vsnprintf(buf+bytes,BUF_MAX-1-bytes,fmt,ap);
		buf[BUF_MAX-1] = 0;
		if((-1 == bytes ) || (bytes>BUF_MAX-1))
		{
			fprintf(stderr,"WARNING : socket log truncated, increase BUF_MAX\n");
			bytes = BUF_MAX-1;
		}
		return send(slw->sock,buf,bytes,0);
	}
}

int sSockFuncLogEntry(LogWriter *_this,const char* funcName)
{

	SockLogWriter *slw = (SockLogWriter*) _this;
	if(!_this || (-1 == slw->sock))
	{
		fprintf(stderr,"invalid args for sSockFuncLogEntry");
		return -1;
	}
	else
	{
		char buf[BUF_MAX];
		int bytes;
#ifdef WIN32
		bytes = _snprintf(buf,BUF_MAX-1,"\n{ %s ", funcName);
#else
		bytes = snprintf(buf,BUF_MAX-1,"\n{ %s", funcName);
#endif
		buf[BUF_MAX-1] = 0;
		if((-1 == bytes ) || (bytes>BUF_MAX-1))
			bytes = BUF_MAX-1;
		return send(slw->sock,buf,bytes,0);
	}
	
}

int sSockFuncLogExit(LogWriter* _this,const char* funcName,const int lineNumber)
{

	SockLogWriter *slw = (SockLogWriter*) _this;
	if(!_this || (-1 == slw->sock))
	{
		fprintf(stderr,"invalid args for sSockFuncLogExit");
		return -1;
	}
	else
	{
		char buf[BUF_MAX];
		int bytes;
#ifdef WIN32
		bytes = _snprintf(buf,BUF_MAX-1,"\n%s : %d }", funcName,lineNumber);
#else
		bytes = snprintf(buf,BUF_MAX-1,"\n%s : %d }", funcName,lineNumber);
#endif
		buf[BUF_MAX-1] = 0;
		if((-1 == bytes ) || (bytes>BUF_MAX-1))
			bytes = BUF_MAX-1;
		return send(slw->sock,buf,bytes,0);
	}
}

int sSockLoggerDeInit(LogWriter* _this)
{
	SockLogWriter *slw = (SockLogWriter*) _this;
	if(slw && (-1 != slw->sock) )
	{
#ifdef _WIN32
#else
		close(slw->sock);
#endif
	}
	return 0;
}

/* helper function to get the log prefix */
static const char* sGetLogPrefix(const LogLevel logLevel)
{
	switch (logLevel)
	{
		case Trace:	return "[T]";
		case Debug: return "[D]";
		case Info:	return "[I]";
		case Warn:	return "[W]";
		case Error:	return "[E]";
		case Fatal:	return "[F]";
		default:	return "";
	}
}
