//-----------------------------------------------------------------------------------
// 版权归uestc_lqy所有
// mail: usetclqy@qq.com
//-----------------------------------------------------------------------------------
// 文件名：7J523GAME.cpp
// 编写人：uestc_lqy
// 编写时间：2017/03/23
// 编译工具: Visual Studio 2012
// 程序说明: socket 七王五二三游戏服务端
//		    CardTable->PlayerManager->client
//			CardTable<-PlayerManager<-client
//------------------------------------------------------------------------------------
#include "stdafx.h"
#include "Socket.h"
#include<windows.h>
#include<vector>
#include"PlayerManager.h"
#include"CardTable.h"
using namespace std;
//********************************************************************************************************/
//** 函数名 ** game()
//**  输入  ** players,cardTable
//**  输出  ** 无
//**函数描述** game
//********************************************************************************************************/
void game(vector<PlayerManager*> players,CardTable &cardTable)
{
	int game_level=0;
	//开局，为每位玩家发牌
	if(game_level==0)
	{
		for(int num=0;num<players.size();num++)
		{
			vector<char> tempcards;
			tempcards=cardTable.generateCards(num);
			players[num]->sendCards(tempcards);
		}
	}
	
	//进入游戏循环流程
	while(cardTable.getState()==NORMAL)
	{
		//设置当前回合可出牌玩家表
		vector<int> cur;
		for(int i=0;i<players.size();i++)
		{
			cur.push_back(1);
		}
		//回合开始
		game_level++;
		int i=0;
		//弃权人数
		int off_count=0;
		//通知出牌，收牌，通知牌面
		while(1)
		{	
			//如果未弃权，则收牌，收到0XFF则为弃权，否则改变牌面和分数，通告每个玩家
			if(cur[i]==1)
			{	
				vector<char> tempcards;
				tempcards=players[i]->recvCards();
				if(tempcards[0]==255)
				{
					cur[i]=0;
					off_count++;
				}
				else
				{
					cardTable.win_number[game_level]=i;
					cardTable.modifyTable(tempcards);
					cardTable.scores[game_level]+=cardTable.cardsToScores(tempcards);
					for(int i=0;i<players.size();i++)
					{
						players[i]->informCurTable();
					}
				}
			
			}
			i++;
			//最后一位玩家出牌后，若只剩一个未弃权玩家则判赢退出循环
			if(i==(players.size()))
			{
				if(off_count==(players.size()-1))
				{	
					break;
				}
				i=0;
			}
			
		}
		//judege,修改状态
		STATE state=cardTable.tableJudge();
		cardTable.modifyState(state);
		
		//回合结束，告知分数，发牌
		if(state!=FINISH)
		{
			for(int num=0;num<players.size();num++)
			{			
				players[num]->informScore();
				vector<char> tempcards;
				tempcards=cardTable.generateCards(num);
				players[num]->sendCards(tempcards);

			}
		}
		

	}
}
//********************************************************************************************************/
//** 函数名 ** main()
//**  输入  ** 无
//**  输出  ** 无
//**函数描述** 主函数 为每个玩家创建一个socket
//********************************************************************************************************/
int main()
{

	SOCKADDR_IN addrServer;
	int sockServer; 	
 	if (SOCKET_ERROR ==SocketInit())
 	{
 		return -1;
 	}	
	addrServer.sin_addr.S_un.S_addr=htonl(INADDR_ANY);		//htol将主机字节序long型转换为网络字节序
	addrServer.sin_family=AF_INET;
	addrServer.sin_port=htons(6666);						//htos用来将端口转换成字符，1024以上的数字即可
	
	sockServer=socket(AF_INET,SOCK_STREAM,0);				//面向连接的可靠性服务SOCK_STRAM
	bind(sockServer,(SOCKADDR*)&addrServer,sizeof(SOCKADDR));//将socket绑定到相应地址和端口上
	listen(sockServer,5);									//等待队列中的最大长度为5
	printf("Welcome,the Host %s is running!Now Wating for someone comes in!\n",inet_ntoa(addrServer.sin_addr));
	int len=sizeof(SOCKADDR);
	SOCKADDR_IN addrClient;
	int i=0;
	CardTable cardTable;
	vector<SOCKET> sockClient;
	vector<PlayerManager*> players;
	while(i<=3)			
	{
		sockClient[i]=accept(sockServer,(SOCKADDR*)&addrClient,&len);//阻塞调用进程直至新的连接出现
		players[i]=new PlayerManager(cardTable,sockClient[i]);
		if(sockClient[i] == INVALID_SOCKET)
		{	
			printf("Accept Failed!\n");
			continue; //继续监听
		}
		i++;
		Sleep(1000);	//一定要
	}
	game(players,cardTable);
	
	getchar();
	return 0;
}

