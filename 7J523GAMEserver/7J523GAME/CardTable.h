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
//Ϊ���Ϊi���������
vector<char> generateCards(int i);
//�޸�����
void modifyTable(vector<char> newcards);
//��õ�ǰ����
vector<char> getCurTable(){return cur_table;};
//�������״̬
STATE getState(){return state;};
//���Ʒ�������
int cardsToScores(vector<char> tempcards);
//����ÿ�غ�������Ϣ
STATE tableJudge();
//�޸�״̬
void modifyState(STATE state){this->state=state;};
//ÿ�ַ���
vector<int> scores;
//ÿ��Ӯ�ұ��
vector<int> win_number;
private:
//��ǰ����
vector<char> cur_table;
//��ʷ����
vector<char> his_table;
//ʣ����
vector<char> left_cards;
//ÿ�������������
vector<int> player_card_num;
//����״̬
STATE state;
};
#endif