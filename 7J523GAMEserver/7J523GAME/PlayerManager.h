#ifndef _PLAYERMANAGER_H
#define _PLAYERMANAGER_H
#include"Socket.h"
#include"CardTable.h"
class PlayerManager
{
public:
	PlayerManager(CardTable& table,SOCKET socket):table(&table),socket(socket){};
	//获取出牌信息
	vector<char> recvCards();
	//发牌
	void sendCards(vector<char> cards);
	//通知出牌
	void notifyCards();
	//通知当前牌面
	void informCurTable();
	//通知历史牌面
	void informTable();
	//通知分数
	void informScore();
	~PlayerManager()
	{
		delete table;
		closesocket(socket);
	}
private:
	//用于通信的socket
	SOCKET socket;
	//缓冲区
	char revBuf[MaxSize];
	char sendBuf[MaxSize];
	CardTable * table;
};
#endif