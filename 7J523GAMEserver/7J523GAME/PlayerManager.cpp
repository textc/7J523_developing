#include "stdafx.h"
#include"PlayerManager.h"

vector<char> PlayerManager::recvCards()
{
	notifyCards();
	vector<char> recv_cards;
	int byte=0;
	string newcards;
	//获得新牌
	while(byte<=0)
	{
		byte= recv(socket,revBuf,strlen(revBuf)+1,0);
	}
	//数据处理
	

	//清理
	memset(revBuf,NULL,sizeof(revBuf));
	return recv_cards;
}
void PlayerManager::notifyCards()
{
	char sendbuf[100];
	//数据处理


	//发送
	int byte=0;
	//通知
	byte= send(socket,sendbuf,strlen(sendbuf)+1,0);
	Sleep(200);
}
void PlayerManager::sendCards(vector<char> cards)
{
	//数据处理


	//发牌
	int byte=0;
	byte= send(socket,sendBuf,strlen(sendBuf)+1,0);

	memset(sendBuf,NULL,sizeof(sendBuf));
}
void PlayerManager::informCurTable()
{
	int byte=0;
	vector<char> curtable=table->getCurTable();
	//数据处理


	//告知当前牌面
	byte= send(socket,sendBuf,strlen(sendBuf)+1,0);
}
void PlayerManager::informScore()
{

}