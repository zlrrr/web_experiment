#include "catcher.h"

void main() {
	int count = 0, inumber, all_number, i;
	//printf("start...\n");
	all_number = PrintAdapter();
	printf("Please enter the interface number:\n");
	scanf("%d", &inumber);
	if (inumber < 1 || inumber > all_number) {
		printf("out of range.\n");
		pcap_freealldevs(alldevs);
		return;
	}

	for (dev = alldevs, i = 0; i < inumber - 1; dev = dev->next, i++);
	if ((adhandle = pcap_open(dev->name,		//设备名
			65535,			//数据包大小
			PCAP_OPENFLAG_PROMISCUOUS,	//混杂模式
			1000,			//读取超时时间
			NULL,			//远程机器验证
			errbuf			//错误缓冲
		)) == NULL) {
			fprintf(stderr, "the adpter %s is not support by Winpcap\n",dev->name);
			pcap_freealldevs(alldevs);
			return;
	}

	printf("listening on %s..\n", dev->description);
	
	//检查数据链路层
	if (pcap_datalink(adhandle) != DLT_EN10MB) {
		//当数据链路不为10MB以太网,弹出错误提示
		fprintf(stderr, "\nThis program works only on Ethernet networks.\n");
		pcap_freealldevs(alldevs);
		return;
	}

	if (dev->addresses != NULL) {
		/* 获得接口第一个地址的掩码 */
		netmask = ((struct sockaddr_in*)(dev->addresses->netmask))->sin_addr.S_un.S_addr;
	}
	else
	{
		/* 如果接口没有地址，则假设一个C类的掩码 */
		netmask = 0xffffff;
	}

	//编译过滤器
	if (pcap_compile(adhandle, &fcode, packet_filter, 1, netmask) < 0) {
		fprintf(stderr, "\nUnable to compile the packet filter. Check the syntax.\n");
		pcap_freealldevs(alldevs);
		return;
	}

	//设置过滤器
	if (pcap_setfilter(adhandle, &fcode) < 0) {
		fprintf(stderr, "\nError setting the filter.\n");
		return;
	}

	//释放设备列表
	pcap_freealldevs(alldevs);

	//开始捕捉，捕获到数据包时，自动调用packet_handler
	pcap_loop(adhandle, 0, ether_packet_handler, NULL);
	
	//	count++;
	//}
	CloseAdapter();
	system("pause");
}


int PrintAdapter()		//初始化网络适配器
{
	int i = 0;
	if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &alldevs, errbuf) == -1) {
		//获取本地机器设备列表
		fprintf(stderr, "error happens when pcap_findalldevs: %s\n", errbuf);
		exit(1);
	}
	for (dev = alldevs; dev != NULL; dev = dev->next) {		//打开选取的网络适配器
		printf("%d.%s", ++i, dev->name);
		if (dev->description) {
			printf("(%s)\n", dev->description);
		}
		else {
			printf("(no description)\n");
		}
		if (i == 0) {
			printf("No interface found.\n");
			return 0;
		}
	}
	return i;
}


void CloseAdapter()		//关闭网络适配器
{
	pcap_freealldevs(alldevs);
}

void ether_packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data)
	//解析以太帧头的回调函数
{
	struct tm *ltime;
	char timestr[16];

	//u_int ip_len;
	//u_short sport, dport;
	time_t local_tv_sec;
	static int packet_no = 1;
	struct ether_header *ethernet_protocol;
	u_short ethernet_type;
	u_char *mac_string;

	//打印初始信息
	printf("========================================\n");

	//转换时间戳为可以识别的格式
	local_tv_sec = header->ts.tv_sec;
	ltime = localtime(&local_tv_sec);
	strftime(timestr, sizeof timestr, "%H:%M:%S", ltime);
	printf("time: %s,%.6d  len: %d\n", timestr, header->ts.tv_usec, header->len);

	printf("Packet number: %d\n", packet_no);
	printf("Packet length: %d\n", header->len);
	printf("------------Ethernet analyse------------\n");

	//识别协议类型
	ethernet_protocol = (struct ether_header *)pkt_data;
	ethernet_type = ntohs(ethernet_protocol->ether_type);
	printf("Ethernet Type: %04x\n",ethernet_type);
	switch (ethernet_type)
	{
	case 0x0800:
		printf("Upper Protocol is IP Protocol\n");
		break;
	case 0x0806:
		printf("Upper Protocol is ARP Protocol\n");
		break;
	case 0x8035:
		printf("Upper Protocol is RARP Protocol\n");
		break;
	default:
		break;
	}

	//打印源MAC地址与目的MAC地址
	printf("Source MAC Address:");
	mac_string = ethernet_protocol->ether_thost;
	printf("%02x.%02x.%02x.%02x.%02x.%02x\n", *mac_string, *(mac_string + 1),
		*(mac_string + 2), *(mac_string + 3), *(mac_string + 4), *(mac_string + 5));
	printf("Destination MAC Address:");
	mac_string = ethernet_protocol->ether_dhost;
	printf("%02x.%02x.%02x.%02x.%02x.%02x\n", *mac_string, *(mac_string + 1),
		*(mac_string + 2), *(mac_string + 3), *(mac_string + 4), *(mac_string + 5));

	if (ethernet_type == 0x0800) {
		ip_packet_handler(param,header,pkt_data);
	}
	printf("--------------------------------------\n");
	packet_no++;
}

void ip_packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data) {
	ip_header *ip_packet;	//ip协议的首部地址
	//udp_header *uh;	
	u_int header_length = 0;
	u_int offset;
	u_char tos;
	u_int16_t checksum;
	
	//获得ip数据包头部
	ip_packet = (struct ip_header *)(pkt_data + 14);
	offset = ntohs(ip_packet->ip_offset);

	printf("------------IP analyse------------\n");
	printf("IP Version: %d\n", ip_packet->ip_version);
	printf("Header Length: %d\n", header_length);
	printf("Type of Service: %d\n", ip_packet->ip_tos);
	printf("Total Length: %d\n", ntohs(ip_packet->ip_length));
	printf("Identification: %d\n", ntohs(ip_packet->ip_id));
	printf("Fragment Offset: %d\n", (offset & 0x1fff) * 8);
	printf("TIme to Live: %d\n", ip_packet->ip_ttl);
	printf("Protocol Type: %d\n", ip_packet->ip_protocol);
	switch (ip_packet->ip_protocol)
	{
	case 1:
		printf("Upper Protocol is ICMP Protocol\n");
		break;
	case 2:
		printf("Upper Protocol is IGMP Protocol\n");
		break;
	case 6:
		printf("Upper Protocol is TCP Protocol\n");
		break;
	case 17:
		printf("Upper Protocol is UDP Protocol\n");
		break;
	default:
		break;
	}
	printf("CheckSum: %d\n", ntohs(ip_packet->ip_checksum));
	printf("Source IP Address:%s\n", inet_ntoa(ip_packet->ip_source_address));
	printf("Destination IP Address:%s\n", inet_ntoa(ip_packet->ip_source_address));
}