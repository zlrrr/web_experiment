#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<pcap.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"wpcap.lib")
#pragma comment(lib,"packet.lib")

///* 4�ֽڵ�IP��ַ */
//typedef struct ip_address {
//	u_char byte1;
//	u_char byte2;
//	u_char byte3;
//	u_char byte4;
//}ip_address;

///* IPv4 �ײ� */
//typedef struct ip_header {
//	u_char  ver_ihl;        // �汾 (4 bits) + �ײ����� (4 bits)
//	u_char  tos;            // ��������(Type of service) 
//	u_short tlen;           // �ܳ�(Total length) 
//	u_short identification; // ��ʶ(Identification)
//	u_short flags_fo;       // ��־λ(Flags) (3 bits) + ��ƫ����(Fragment offset) (13 bits)
//	u_char  ttl;            // ���ʱ��(Time to live)
//	u_char  proto;          // Э��(Protocol)
//	u_short crc;            // �ײ�У���(Header checksum)
//	ip_address  saddr;      // Դ��ַ(Source address)
//	ip_address  daddr;      // Ŀ�ĵ�ַ(Destination address)
//	u_int   op_pad;         // ѡ�������(Option + Padding)
//}ip_header;

/* UDP �ײ�*/
typedef struct udp_header {
	u_short sport;          // Դ�˿�(Source port)
	u_short dport;          // Ŀ�Ķ˿�(Destination port)
	u_short len;            // UDP���ݰ�����(Datagram length)
	u_short crc;            // У���(Checksum)
}udp_header;

/* IP�ײ� */
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

//��̫֡ͷ��
typedef struct ether_header {
	unsigned char ether_dhost[6];
	unsigned char ether_thost[6];
	unsigned short ether_type;
}ETHHEADER, *PETHHEADER;

FILE *fp;
pcap_if_t *alldevs, *dev;	//�豸
char errbuf[PCAP_BUF_SIZE];
pcap_t *adhandle;	//�豸���
u_int netmask;	//��������
struct bpf_program fcode;	//������
char packet_filter[] = "ip and udp"; //����������


int PrintAdapter();
void CloseAdapter();
void ether_packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);
void ip_packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);