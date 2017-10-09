#ifndef __P2P_TRANSFER_H__
#define __P2P_TRANSFER_H__

#include <stdint.h>
#include <malloc.h>
#include <arpa/inet.h>

#ifdef __cplusplus
extern "C" {
#endif

//#define P2P_TRANSFER_SERVER_DOMAIN	(t05b022.p2cdn.com)
#if 0
#define P2P_TRANSFER_SERVER_IP		"192.168.111.123"
#else
#define P2P_TRANSFER_SERVER_IP		"47.92.106.133"//"127.0.0.1"//"58.220.12.22"
#endif

#define P2P_TRANSFER_SERVER_PORT	(7051)//(7172)

#define P2P_TRANSFER_SERVER_IP_NUM	(2)

//??????nat_probe.h???????????
enum
{
	NP_UNKNOWN					= 0,	/**< ??????????. */
	NP_PUBLIC_NETWORK,					/**< ????????. */
	NP_FULL_CONE_NAT,					/**< ????NAT. */
	NP_RESTRICTED_CONE_NAT,				/**< ??????NAT. */
	NP_PORT_RESTRICTED_CONE_NAT,		/**< ?????????NAT. */
	NP_SYMMETRIC_NAT,					/**< ?????NAT. */
};

enum
{
	P2P_TRANSFER_UNKNOWN_CMD = 0,
	P2P_TRANSFER_PING,
	P2P_TRANSFER_QUERY_DEVICE_INFO_REQUEST,
	P2P_TRANSFER_QUERY_DEVICE_INFO_RESPONSE,
	P2P_TRANSFER_PUNCH_HOLE,
	P2P_TRANSFER_CLOSE,
};

#define P2P_TRANSFER_MAGIC (0xbeefdead1234)

struct p2p_msg_ping_t
{
	uint64_t	device_sn;           //??id
	int			network_type;       //????????
};

struct p2p_msg_device_info_t
{
	uint64_t			device_sn;
	struct in_addr		ip_addr;
	uint16_t			port;
	int					network_type;
};

struct p2p_msg_head_t
{
	uint64_t        magic;          //????????
	uint64_t        msgid;          //??id,TCP???????????
	uint64_t        src_device_sn;   //???????????sn
	uint64_t        dst_device_sn;   //???????????sn
	uint32_t        cmd_len;		//???????
	int             cmd;
	char            cmd_data[0];    //????
};


#define UNUSED __attribute__((unused))

#define SAFE_CALLOC(type, ptr, size) \
	do \
	{ \
		ptr = (type)calloc(1, size); \
		if (NULL == ptr) \
		{ \
			XL_DEBUG(EN_PRINT_ERROR, "call calloc() failed, size: %d, err: %s", size, strerror(errno)); \
			goto ERR; \
		} \
	} \
	while(0)

#define SAFE_FREE(ptr) \
	do \
	{ \
		if (ptr != NULL) \
		{ \
			free(ptr); \
			ptr = NULL; \
		} \
	} \
	while(0)
#define SAFE_CLOSE(sock) \
	do \
	{ \
		if (sock > 0) \
		{ \
			close(sock); \
			sock = -1; \
		} \
	}while(0)

/**
 * ?????????????????????
 * @param network_type	????????
 * 
 */
const char *get_string_network_type(int network_type);

int set_sock_opt(int sock, int flag);

#ifdef __cplusplus
};
#endif
#endif
