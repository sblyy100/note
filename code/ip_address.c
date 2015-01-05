#include<arpa/inet.h>

/* 返回1：串有效，返回0：串出错 */
int inet_aton(const char *strptr, struct in_addr *addrptr);

/* 若成功，返回32位二进制的网络字节序地址；若出错，返回INADDR_NONE */
in_addr_t inet_addr(const char *strptr);

/* 返回指向点分十进制数串的指针 */
char* inet_ntoa(struct in_addr inaddr);

/* 若函数成功，则返回1；若输入不是有效的格式，则函数返回0；若处理失败，函数返回-1 */
int inet_pton(int family, const char *strptr, void *addrptr);

/* 若函数处理成功，返回指向结果的指针；若函数处理失败，返回NULL */
const char* inet_ntop(int family, const void *addrptr, char *strptr, size_t len);

#include <netinet/in.h>

typedef uint32_t in_addr_t;
struct in_addr
{
	in_addr_t s_addr;
};


struct in6_addr
  {
    union
      {
	uint8_t	__u6_addr8[16];
#if defined __USE_MISC || defined __USE_GNU
	uint16_t __u6_addr16[8];
	uint32_t __u6_addr32[4];
#endif
      } __in6_u;


//打印网络地址宏-kernel
#define NIPQUAD(addr) \
	((unsigned char *)&addr)[0], \
	((unsigned char *)&addr)[1], \
	((unsigned char *)&addr)[2], \
	((unsigned char *)&addr)[3]
#define NIPQUAD_FMT "%u.%u.%u.%u"


/* Address to accept any incoming messages.  */
#define	INADDR_ANY		((in_addr_t) 0x00000000)
/* Address to send to all hosts.  */
#define	INADDR_BROADCAST	((in_addr_t) 0xffffffff)
/* Address indicating an error return.  */
#define	INADDR_NONE		((in_addr_t) 0xffffffff)
#ifndef INADDR_LOOPBACK
# define INADDR_LOOPBACK	((in_addr_t) 0x7f000001) /* Inet 127.0.0.1.  */
#endif
/* Defines for Multicast INADDR.  */
#define INADDR_UNSPEC_GROUP	((in_addr_t) 0xe0000000) /* 224.0.0.0 */
#define INADDR_ALLHOSTS_GROUP	((in_addr_t) 0xe0000001) /* 224.0.0.1 */
#define INADDR_ALLRTRS_GROUP    ((in_addr_t) 0xe0000002) /* 224.0.0.2 */
#define INADDR_MAX_LOCAL_GROUP  ((in_addr_t) 0xe00000ff) /* 224.0.0.255 */

extern const struct in6_addr in6addr_any;        /* :: */
extern const struct in6_addr in6addr_loopback;   /* ::1 */
#define IN6ADDR_ANY_INIT { { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 } } }
#define IN6ADDR_LOOPBACK_INIT { { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 } } }

#define INET_ADDRSTRLEN 16
#define INET6_ADDRSTRLEN 46
