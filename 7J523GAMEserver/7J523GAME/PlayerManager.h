#ifndef _PLAYERMANAGER_H
#define _PLAYERMANAGER_H
#include"Socket.h"
#include"CardTable.h"
class PlayerManager
{
public:
	PlayerManager(CardTable& table,SOCKET socket):table(&table),socket(socket){};
	//��ȡ������Ϣ
	vector<char> recvCards();
	//����
	void sendCards(vector<char> cards);
	//֪ͨ����
	void notifyCards();
	//֪ͨ��ǰ����
	void informCurTable();
	//֪ͨ��ʷ����
	void informTable();
	//֪ͨ����
	void informScore();
	~PlayerManager()
	{
		delete table;
		closesocket(socket);
	}
private:
	//����ͨ�ŵ�socket
	SOCKET socket;
	//������
	char revBuf[MaxSize];
	char sendBuf[MaxSize];
	CardTable * table;
};
#endif