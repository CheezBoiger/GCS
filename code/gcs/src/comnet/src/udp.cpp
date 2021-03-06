/* User Includes */
#include <udp.h>
#include <error_handle.h>

#ifndef _WIN32
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#endif

using namespace error;

/* 
Unix uses BSD sockets, programmed using Beej's Network programming guide
Since Windows uses something similar, except with Winsock startup and 
a few inconsistencies, the OS #ifdefs are interspersed in the code.
*/
int32_t udp_open(sock_fd_t* fd, udp_address_t* config)
{

	int32_t broadcast_enabled = 1;
	char reuse;
	struct sockaddr_in addr;
	int32_t ret;
#ifdef _WIN32
    struct WSAData* wd = (struct WSAData*)malloc(sizeof(struct WSAData));
    ret = WSAStartup(MAKEWORD(2, 0), wd);
    free(wd);
	if (ret) 
	{
		return 1; 
	}
#endif
	
	memset(&addr,0,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(config->serv);
	addr.sin_port =	htons(config->port);	


	*fd = socket(AF_INET, SOCK_DGRAM, 0);
	setsockopt(*fd, SOL_SOCKET, SO_BROADCAST, (const char*)&broadcast_enabled, sizeof(int32_t));
	setsockopt(*fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
	if(*fd == -1)
	{
      throw error::ConnectionException(OSErrors::error_windows, ConnectErrors::error_open_socket_fail);
	}
	if(bind(*fd, (struct sockaddr *)&addr, sizeof(addr)))
	{
		throw ConnectionException(OSErrors::error_windows, ConnectErrors::error_socket_bind_fail);
	}
	return 0;
}

int32_t udp_read(
	sock_fd_t* fd, 
	uint8_t* buf, 
	int32_t* rx_len, 
	udp_address_t* rx_addr)
{
#ifdef _WIN32
	int32_t addr_len;
#endif
#ifndef _WIN32
	socklen_t addr_len;
#endif
	int32_t retval;
	struct sockaddr_in addr;
	addr_len = sizeof(addr);
	retval = recvfrom(*fd, (char*)buf, 1023, 0, (struct sockaddr*)&addr, &addr_len);
	*rx_len = retval;
	rx_addr->port = ntohs(addr.sin_port);
	strcpy(rx_addr->serv, inet_ntoa(addr.sin_addr));
	return retval;
}

int32_t udp_send(
	sock_fd_t* fd, 
	uint8_t* tx_buf, 
	int32_t tx_len, 
	udp_address_t tx_addr)
{
	struct sockaddr_in addr;
	int32_t retval;
	strlen(tx_addr.serv);
	if(!strcmp(tx_addr.serv, "255.255.255.255"))
	{
		addr.sin_addr.s_addr= htonl(INADDR_BROADCAST);
	}
	else
	{
		addr.sin_addr.s_addr=inet_addr(tx_addr.serv);
	}
	addr.sin_family = AF_INET;
	
	addr.sin_port=htons(tx_addr.port);
	retval = sendto(*fd, (char*)tx_buf, tx_len, 0, (struct sockaddr *)&addr,sizeof(addr));
	return retval;
}

int32_t udp_close(sock_fd_t* fd){
#ifdef _WIN32
	return closesocket(*fd);	
#endif
#ifndef _WIN32
	return close(*fd);
#endif
}

/* Binds every available interface at specified port */
UDP::UDP(uint16_t port)
{
	memset(&info, 0, sizeof(udp_info_t));
	memset(&config, 0, sizeof(udp_address_t));
	memset(&rx_addr, 0, sizeof(udp_address_t));
	memset(&fd, 0, sizeof(sock_fd_t));
	memset(rx_buf, 0, sizeof(1024));
	this->connected = 0;
	this->link_id = 0;
	this->open(port);
}
/* Constructor initializes all data structures, targets interface*/
UDP::UDP(uint16_t port, char addr[16])
{
	memset(&info, 0, sizeof(udp_info_t));
	memset(&config, 0, sizeof(udp_address_t));
	memset(&rx_addr, 0, sizeof(udp_address_t));
	memset(&fd, 0, sizeof(sock_fd_t));
	memset(rx_buf, 0, sizeof(1024));
	this->connected = 0;
	this->link_id = 0;
	this->open(port, addr);
}

/* Ensure port is closed */
UDP::~UDP()
{
	this->close();
}
/* 
Implement the generic open/close/send/recv functions from the inherited 
datalink interface. open is harder to wrap, so ignore those.
*/
int32_t UDP::open(uint16_t port)
{
	config.port = port;
	strcpy(config.serv, "0.0.0.0");
	if(udp_open(&fd, &config) == 0)
	{
		datalink_type = UDP_TYPE;
		connected = 1;
		return 0;
	}
	else
	{
      connected = 0;
      throw ConnectionException(OSErrors::error_no_os, ConnectErrors::error_connection_failed);
	}
}
int32_t UDP::open(uint16_t port, char addr[16])
{
	config.port = port;
	strcpy(config.serv, addr);
	if(udp_open(&fd, &config) == 0)
	{
		datalink_type = UDP_TYPE;
		connected = 1;
		return 0;
	}
	else
	{
      throw ConnectionException(OSErrors::error_no_os, ConnectErrors::error_connection_failed);
		connected = 0;
	}
}
int32_t UDP::close() 
{
	if(connected)
	{
		return(udp_close(&fd));
	}
   throw ConnectionException(ConnectErrors::error_no_connection_error);
}
int32_t UDP::send(uint8_t node_id, uint8_t tx_data[1024], int32_t tx_len) 
{
	if(connected)
	{
		return(udp_send(&fd, tx_data, tx_len, this->info.node_addr[node_id]));
	}
   throw ConnectionException(ConnectErrors::error_no_connection_error);
}
int32_t UDP::recv(uint8_t* rx_data, int32_t* rx_len) 
{
	if(connected)
	{
		return(udp_read(&fd, rx_data, rx_len, &rx_addr));
	}
   throw ConnectionException(ConnectErrors::error_no_connection_error);
		
}
/* Maps a node ID to a specific IP address for internal handling */
int32_t UDP::establish(uint8_t node_id, uint16_t port, char addr[16]) 
{
	if(connected)
	{
		if(this->info.node_connected[node_id])
		{
			throw ConnectionException(ConnectErrors::error_already_connected);
		}
		this->info.node_connected[node_id] = 1;
		this->info.node_addr[node_id].port = port; 
		strcpy(this->info.node_addr[node_id].serv, addr);
		return 0;
	}
   throw ConnectionException(ConnectErrors::error_no_connection_error);
}
/* Similar to previous function, allows use of udp_address_t struct */
int32_t UDP::establish(uint8_t node_id, udp_address_t* rx_addr)
{
	if(connected)
	{
		if(this->info.node_connected[node_id])
		{
         throw ConnectionException(ConnectErrors::error_already_connected);
		}
		this->info.node_connected[node_id] = 1;
		this->info.node_addr[node_id] = *rx_addr;
		return 0;
	}
   throw ConnectionException(ConnectErrors::error_no_connection_error);
}
/* Establishes a node of the last received address */
int32_t UDP::establish(uint8_t node_id)  
{
	if(connected)
	{
		if(this->info.node_connected[node_id])
		{
         throw ConnectionException(ConnectErrors::error_already_connected);
		}
		this->info.node_connected[node_id] = 1;
		this->info.node_addr[node_id] = this->rx_addr;
		return 0;	
	}
	throw ConnectionException(ConnectErrors::error_no_connection_error);
}
