#include "stdafx.h"
#include"PlayerManager.h"

vector<char> PlayerManager::recvCards()
{
	notifyCards();
	vector<char> recv_cards;
	int byte=0;
	string newcards;
	//�������
	while(byte<=0)
	{
		byte= recv(socket,revBuf,strlen(revBuf)+1,0);
	}
	//���ݴ���
	

	//����
	memset(revBuf,NULL,sizeof(revBuf));
	return recv_cards;
}
void PlayerManager::notifyCards()
{
	char sendbuf[100];
	//���ݴ���


	//����
	int byte=0;
	//֪ͨ
	byte= send(socket,sendbuf,strlen(sendbuf)+1,0);
	Sleep(200);
}
void PlayerManager::sendCards(vector<char> cards)
{
	//���ݴ���


	//����
	int byte=0;
	byte= send(socket,sendBuf,strlen(sendBuf)+1,0);

	memset(sendBuf,NULL,sizeof(sendBuf));
}
void PlayerManager::informCurTable()
{
	int byte=0;
	vector<char> curtable=table->getCurTable();
	//���ݴ���


	//��֪��ǰ����
	byte= send(socket,sendBuf,strlen(sendBuf)+1,0);
}
void PlayerManager::informScore()
{

}