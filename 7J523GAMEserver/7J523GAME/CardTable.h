#ifndef _CARDTABLE_H
#define _CARDTABLE_H
#include<String>
#include<vector>
using namespace std;
enum STATE{NORMAL,FINISH,ERROER};
class CardTable
{
public:
CardTable():state(NORMAL){};
//为编号为i玩家生成牌
vector<char> generateCards(int i);
//修改牌面
void modifyTable(vector<char> newcards);
//获得当前牌面
vector<char> getCurTable(){return cur_table;};
//获得牌桌状态
STATE getState(){return state;};
//卡牌分数计算
int cardsToScores(vector<char> tempcards);
//处理每回合桌面信息
STATE tableJudge();
//修改状态
void modifyState(STATE state){this->state=state;};
//每轮分数
vector<int> scores;
//每轮赢家编号
vector<int> win_number;
private:
//当前牌面
vector<char> cur_table;
//历史牌面
vector<char> his_table;
//剩余牌
vector<char> left_cards;
//每个玩家手牌数量
vector<int> player_card_num;
//牌桌状态
STATE state;
};
#endif