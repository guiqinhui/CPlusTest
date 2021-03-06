/*
题目描述
	请解析IP地址和对应的掩码，进行分类识别。要求按照A/B/C/D/E类地址归类，不合法的地址和掩码单独归类。
	所有的IP地址划分为 A,B,C,D,E五类
	A类地址1.0.0.0~126.255.255.255;
	B类地址128.0.0.0~191.255.255.255;
	C类地址192.0.0.0~223.255.255.255;
	D类地址224.0.0.0~239.255.255.255；
	E类地址240.0.0.0~255.255.255.255
	私网IP范围是：
	10.0.0.0～10.255.255.255
	172.16.0.0～172.31.255.255
	192.168.0.0～192.168.255.255
	子网掩码为前面是连续的1，然后全是0。（例如：255.255.255.32就是一个非法的掩码）
	本题暂时默认以0开头的IP地址是合法的，比如0.1.1.2，是合法地址
	输入描述:
	多行字符串。每行一个IP地址和掩码，用~隔开。
	输出描述:
	统计A、B、C、D、E、错误IP地址或错误掩码、私有IP的个数，之间以空格隔开。
	示例1
	输入
	10.70.44.68~255.254.255.0
	1.0.0.1~255.0.0.0
	192.168.0.2~255.255.255.0
	19..0.~255.255.255.0
	输出
	1 0 1 0 0 2 1
*/

#include <iostream>
#include <string>
#include <vector>
#include <array>
#define DEBUG_INFO		1
using namespace std;
enum E_IP_MASK_TYPE
{
	IP_A_CLASS = 0,
	IP_B_CLASS,
	IP_C_CLASS,
	IP_D_CLASS,
	IP_E_CLASS,
	IP_ADDR_OR_MASK_ERR,
	IP_PRIVEATE_ADDR,
	ADDR_UNKNOWN,
};
enum E_ADDR_TYPE
{
	ADDR_TYPE_IP=0,
	ADDR_TYPE_MASK,
};
int get_ip_mask(string input,string &ip_addr,string &mask_addr)
{
	int pos;
	pos = input.find("~",0,1);
	if (pos == string::npos)
	{
		return -1;
	}
	ip_addr = input.substr(0, pos);
	mask_addr = input.substr(pos+1);
	return 0;
}

int stringtoint(string input)
{
	int len = input.size();
	int intval = 0;
	for (int i = 0; i < len; i++)
	{
		intval = intval * 10 + input[i] - '0';
	}
	return intval;
}

int ParseAddr(string SrcAddr,int Addr_type)
{
	E_IP_MASK_TYPE eReturn = ADDR_UNKNOWN;
	array<int, 4> DstAddr = {0};
	bool zeroflag=false;
	int comparevalue = 1,num;
	int DotPos = 0, PosStart=0,i=0,j=0;
	for (i=0;i<DstAddr.size(); i++)
	{
		DotPos = SrcAddr.find(".", PosStart, 1);
		if (DotPos == string::npos)
		{
			if (i == (DstAddr.size() - 1))
			{
				DotPos = SrcAddr.size();
			}
			else
			{
				break;
			}
		}
		if (DotPos == PosStart)
		{
			eReturn = IP_ADDR_OR_MASK_ERR;
			return eReturn;
		}
	#if DEBUG_INFO
		cout << "PosStart:" << PosStart << "DotPos: " << DotPos << endl;
	#endif
		DstAddr[i] = stringtoint(SrcAddr.substr(PosStart, DotPos- PosStart));
		PosStart = DotPos + 1;
	}
#if DEBUG_INFO
	for (i = 0; i < DstAddr.size(); i++)
	{
		cout << "Num:" << i << " " << DstAddr[i] << endl;
	}
#endif	
	switch (Addr_type)
	{
	case ADDR_TYPE_IP:
	{
		if ((DstAddr[0] == 10)
			|| ((DstAddr[0] == 172) && (DstAddr[1] <= 31) && (DstAddr[0] >= 16))
			|| ((DstAddr[0] == 192) && (DstAddr[1] == 168)))
		{
			eReturn = IP_PRIVEATE_ADDR;
		}
		else if ((DstAddr[0] <= 126) && (DstAddr[0] >= 1))
		{
			eReturn = IP_A_CLASS;
		}
		else if ((DstAddr[0] <= 191) && (DstAddr[0] >= 128))
		{
			eReturn = IP_B_CLASS;
		}
		else if ((DstAddr[0] <= 223) && (DstAddr[0] >= 192))
		{
			eReturn = IP_C_CLASS;
		}
		else if ((DstAddr[0] <= 239) && (DstAddr[0] >= 224))
		{
			eReturn = IP_D_CLASS;
		}
		else if ((DstAddr[0] <= 255) && (DstAddr[0] >= 240))
		{
			eReturn = IP_E_CLASS;
		}
		

		for (i = 1; i < DstAddr.size(); i++)
		{
			if ((DstAddr[i] > 255) || (DstAddr[1] < 0))
			{
				eReturn = IP_ADDR_OR_MASK_ERR;
				break;
			}
		}
		
	}break;
	case ADDR_TYPE_MASK:
	{//前面全是1，后面全是0
		for (i = 0; i < DstAddr.size(); i++)
		{
			if (!zeroflag)
			{
				if (DstAddr[i]!=255)
				{
					if ((DstAddr[i] != 0)
						&& (DstAddr[i] != 128)
						&& (DstAddr[i] != 192)
						&& (DstAddr[i] != 224)
						&& (DstAddr[i] != 240)
						&& (DstAddr[i] != 248)
						&& (DstAddr[i] != 252)
						&& (DstAddr[i] != 254))
					{
						eReturn = IP_ADDR_OR_MASK_ERR;
					}
					else
					{
						zeroflag = true;
					}
				}
			}
			else
			{
				if (DstAddr[i] != 0)
				{
					eReturn = IP_ADDR_OR_MASK_ERR;
				}
			}
		}
		
	}break;
	default:break;
	}
	return eReturn;
}
int main()
{
	string inputstr;
	int ParseResult=0,i=0;
	vector<string> inputvector;
	array<int, 7> Output = {0};
	string ip_addr, mask_addr;
	while (getline(cin, inputstr))
	{
		inputvector.push_back(inputstr);
	}
	for ( i = 0; i < inputvector.size(); i++)
	{
#if DEBUG_INFO
		cout << "input string:" << i << " " << inputvector[i] << endl;
#endif
		if (get_ip_mask(inputvector[i], ip_addr, mask_addr)==-1)
		{
			continue;
		}
#if DEBUG_INFO
		cout << "ip_addr:" << ip_addr << endl;
		cout << "mask_addr:" << mask_addr << endl;
#endif
		ParseResult = ParseAddr(ip_addr, ADDR_TYPE_IP);
#if DEBUG_INFO
		cout << "Ip ParseResult:" << ParseResult << endl;
#endif
		if (ParseResult < ADDR_UNKNOWN)
		{
			Output.at(ParseResult)++;
		}
		ParseResult = ParseAddr(mask_addr, ADDR_TYPE_MASK);
#if DEBUG_INFO
		cout << "mask ParseResult:" << ParseResult << endl;
#endif
		if(ParseResult < ADDR_UNKNOWN)
		{
			Output.at(ParseResult)++;
		}
#if DEBUG_INFO
		cout << "==================================================" << endl;
#endif
	}
	for (i = 0; i < Output.size(); i++)
	{
		cout << Output.at(i) <<" ";
	}
	while (1)
	{
		if (getchar() == 'c')
		{
			break;
		}
	}
	return 0;
}
