#ifndef _IPHLPAPI_H
#define _IPHLPAPI_H
#include <iprtrmib.h>
#include <ipexport.h>
#include <iptypes.h>
#ifdef __cplusplus
extern "C" {
#endif
DWORD WINAPI CreateIpForwardEntry(PMIB_IPFORWARDROW);
DWORD WINAPI CreateIpNetEntry(PMIB_IPNETROW);
DWORD WINAPI DeleteIpForwardEntry(PMIB_IPFORWARDROW);
DWORD WINAPI DeleteIpNetEntry(PMIB_IPNETROW);
DWORD WINAPI GetAdaptersInfo(PIP_ADAPTER_INFO,PULONG);
DWORD WINAPI GetBestInterface(IPAddr,PDWORD);
DWORD WINAPI GetBestRoute(DWORD,DWORD,PMIB_IPFORWARDROW);
DWORD WINAPI GetFriendlyIfIndex(DWORD);
DWORD WINAPI GetIcmpStatistics(PMIB_ICMP);
DWORD WINAPI GetIfEntry(PMIB_IFROW);
DWORD WINAPI GetIfTable(PMIB_IFTABLE,PULONG,BOOL);
DWORD WINAPI GetInterfaceInfo(PIP_INTERFACE_INFO,PULONG);
DWORD WINAPI GetIpAddrTable(PMIB_IPADDRTABLE,PULONG,BOOL);
DWORD WINAPI GetIpForwardTable(PMIB_IPFORWARDTABLE,PULONG,BOOL);
DWORD WINAPI GetIpNetTable(PMIB_IPNETTABLE,PULONG,BOOL);
DWORD WINAPI GetIpStatistics(PMIB_IPSTATS);
DWORD WINAPI GetNetworkParams(PFIXED_INFO,PULONG);
DWORD WINAPI GetNumberOfInterfaces(PDWORD);
BOOL WINAPI GetRTTAndHopCount(IPAddr,PULONG,ULONG,PULONG);
DWORD WINAPI GetTcpStatistics(PMIB_TCPSTATS);
DWORD WINAPI GetTcpTable(PMIB_TCPTABLE,PDWORD,BOOL);
DWORD WINAPI GetUdpStatistics(PMIB_UDPSTATS);
DWORD WINAPI GetUdpTable(PMIB_UDPTABLE,PDWORD,BOOL);
DWORD WINAPI IpReleaseAddress(PIP_ADAPTER_INDEX_MAP);
DWORD WINAPI IpRenewAddress(PIP_ADAPTER_INDEX_MAP);
DWORD WINAPI SetIfEntry(PMIB_IFROW);
DWORD WINAPI SetIpForwardEntry(PMIB_IPFORWARDROW);
DWORD WINAPI SetIpNetEntry(PMIB_IPNETROW);
DWORD WINAPI SetIpStatistics(PMIB_IPSTATS);
DWORD WINAPI SetIpTTL(UINT);
DWORD WINAPI SetTcpEntry(PMIB_TCPROW);
#ifdef __cplusplus
}
#endif
#endif /* _IPHLPAPI_H */
