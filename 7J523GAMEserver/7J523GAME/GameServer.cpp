//-----------------------------------------------------------------------------------
// ��Ȩ��uestc_lqy����
// mail: usetclqy@qq.com
//-----------------------------------------------------------------------------------
// �ļ�����7J523GAME.cpp
// ��д�ˣ�uestc_lqy
// ��дʱ�䣺2017/03/23
// ���빤��: Visual Studio 2012
// ����˵��: socket �����������Ϸ�����
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
//** ������ ** game()
//**  ����  ** players,cardTable
//**  ���  ** ��
//**��������** game
//********************************************************************************************************/
void game(vector<PlayerManager*> players,CardTable &cardTable)
{
	int game_level=0;
	//���֣�Ϊÿλ��ҷ���
	if(game_level==0)
	{
		for(int num=0;num<players.size();num++)
		{
			vector<char> tempcards;
			tempcards=cardTable.generateCards(num);
			players[num]->sendCards(tempcards);
		}
	}
	
	//������Ϸѭ������
	while(cardTable.getState()==NORMAL)
	{
		//���õ�ǰ�غϿɳ�����ұ�
		vector<int> cur;
		for(int i=0;i<players.size();i++)
		{
			cur.push_back(1);
		}
		//�غϿ�ʼ
		game_level++;
		int i=0;
		//��Ȩ����
		int off_count=0;
		//֪ͨ���ƣ����ƣ�֪ͨ����
		while(1)
		{	
			//���δ��Ȩ�������ƣ��յ�0XFF��Ϊ��Ȩ������ı�����ͷ�����ͨ��ÿ�����
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
			//���һλ��ҳ��ƺ���ֻʣһ��δ��Ȩ�������Ӯ�˳�ѭ��
			if(i==(players.size()))
			{
				if(off_count==(players.size()-1))
				{	
					break;
				}
				i=0;
			}
			
		}
		//judege,�޸�״̬
		STATE state=cardTable.tableJudge();
		cardTable.modifyState(state);
		
		//�غϽ�������֪����������
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
//** ������ ** main()
//**  ����  ** ��
//**  ���  ** ��
//**��������** ������ Ϊÿ����Ҵ���һ��socket
//********************************************************************************************************/
int main()
{

	SOCKADDR_IN addrServer;
	int sockServer; 	
 	if (SOCKET_ERROR ==SocketInit())
 	{
 		return -1;
 	}	
	addrServer.sin_addr.S_un.S_addr=htonl(INADDR_ANY);		//htol�������ֽ���long��ת��Ϊ�����ֽ���
	addrServer.sin_family=AF_INET;
	addrServer.sin_port=htons(6666);						//htos�������˿�ת�����ַ���1024���ϵ����ּ���
	
	sockServer=socket(AF_INET,SOCK_STREAM,0);				//�������ӵĿɿ��Է���SOCK_STRAM
	bind(sockServer,(SOCKADDR*)&addrServer,sizeof(SOCKADDR));//��socket�󶨵���Ӧ��ַ�Ͷ˿���
	listen(sockServer,5);									//�ȴ������е���󳤶�Ϊ5
	printf("Welcome,the Host %s is running!Now Wating for someone comes in!\n",inet_ntoa(addrServer.sin_addr));
	int len=sizeof(SOCKADDR);
	SOCKADDR_IN addrClient;
	int i=0;
	CardTable cardTable;
	vector<SOCKET> sockClient;
	vector<PlayerManager*> players;
	while(i<=3)			
	{
		sockClient[i]=accept(sockServer,(SOCKADDR*)&addrClient,&len);//�������ý���ֱ���µ����ӳ���
		players[i]=new PlayerManager(cardTable,sockClient[i]);
		if(sockClient[i] == INVALID_SOCKET)
		{	
			printf("Accept Failed!\n");
			continue; //��������
		}
		i++;
		Sleep(1000);	//һ��Ҫ
	}
	game(players,cardTable);
	
	getchar();
	return 0;
}

