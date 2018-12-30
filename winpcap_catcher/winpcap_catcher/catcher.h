#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<pcap.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"wpcap.lib")
#pragma comment(lib,"packet.lib")

///* 4字节的IP地址 */
//typedef struct ip_address {
//	u_char byte1;
//	u_char byte2;
//	u_char byte3;
//	u_char byte4;
//}ip_address;

///* IPv4 首部 */
//typedef struct ip_header {
//	u_char  ver_ihl;        // 版本 (4 bits) + 首部长度 (4 bits)
//	u_char  tos;            // 服务类型(Type of service) 
//	u_short tlen;           // 总长(Total length) 
//	u_short identification; // 标识(Identification)
//	u_short flags_fo;       // 标志位(Flags) (3 bits) + 段偏移量(Fragment offset) (13 bits)
//	u_char  ttl;            // 存活时间(Time to live)
//	u_char  proto;          // 协议(Protocol)
//	u_short crc;            // 首部校验和(Header checksum)
//	ip_address  saddr;      // 源地址(Source address)
//	ip_address  daddr;      // 目的地址(Destination address)
//	u_int   op_pad;         // 选项与填充(Option + Padding)
//}ip_header;

/* UDP 首部*/
typedef struct udp_header {
	u_short sport;          // 源端口(Source port)
	u_short dport;          // 目的端口(Destination port)
	u_short len;            // UDP数据包长度(Datagram length)
	u_short crc;            // 校验和(Checksum)
}udp_header;

/* IP首部 */
struct ip_header {
#if defined(WORDS_BIENDIAN)
	u_int8_t ip_version : 4,
	ip_header_length : 4;
#else
	u_int8_t ip_header_length : 4,
		ip_version : 4;
#endif
	u_int8_t ip_tos;
	u_int16_t ip_length;
	u_int16_t ip_id;
	u_int16_t ip_offset;
	u_int8_t ip_ttl;
	u_int8_t ip_protocol;
	u_int16_t ip_checksum;
	struct in_addr ip_source_address;
	struct in_addr ip_destination_address;
};

//以太帧头部
typedef struct ether_header {
	unsigned char ether_dhost[6];
	unsigned char ether_thost[6];
	unsigned short ether_type;
}ETHHEADER, *PETHHEADER;

FILE *fp;
pcap_if_t *alldevs, *dev;	//设备
char errbuf[PCAP_BUF_SIZE];
pcap_t *adhandle;	//设备句柄
u_int netmask;	//子网掩码
struct bpf_program fcode;	//过滤器
char packet_filter[] = "ip and udp"; //过滤器内容


int PrintAdapter();
void CloseAdapter();
void ether_packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);
void ip_packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);