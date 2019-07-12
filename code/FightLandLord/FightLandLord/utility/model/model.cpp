#include "model.h"


Player::Player() :selected(std::make_shared<RuleCardSet>()),
onHand(std::make_shared<RuleCardSet>()),
status(std::make_shared<int>(0)),
m_Num(std::make_shared<int>(0)),
s_Num(std::make_shared<int>(0)),
m_Card(std::make_shared<CARD20>()),
m_Selected(std::make_shared<BOOL20>())
{
}

Player::~Player()
{
}

void Player::modelCommandSlot(std::shared_ptr<Signal> signal) {
	qDebug() << "View Model to Model" << endl;
	if (*status == SELF_DIS_CONNECT && signal->signalType == CONNECT) {
		emit modelCommandSignal(signal);
	}
	if (*status == SELF_CONNECT && signal->signalType == READY) {
		emit modelCommandSignal(signal);
	}
	else if (0)  //this is for selected
	{
		int index = 0;
		m_Selected->bools[index] = 1;
		CARDSET zero;
		zero.add(m_Card->cards[index]);
		(*selected) = (*selected) + zero;
		//for some modify
		emit modelNotificationSignal(signal);
	}
	else if (0)  //this is for cancel selected
	{
		int index = 0;
		m_Selected->bools[index] = 0;
		CARDSET zero;
		zero.add(m_Card->cards[index]);
		(*selected) = (*selected) - zero;
		//for some modify
		emit modelNotificationSignal(signal);
	}
	else if (0)  //this is for try to hand cards
	{
		if (((*onTable) < (*selected)) == 1) {
			//for some modify
			emit modelCommandSignal(signal);
		}
		else {
			//for some modify
			emit modelNotificationSignal(signal);
		}
	}
}

void Player::modelNotificationSlot(std::shared_ptr<Signal> signal) {
	qDebug() << "Socket to Model" << endl;
	if (*status == SELF_DIS_CONNECT && signal->signalType == CONNECT_SUCCESS && signal->playerType == SELF) {
		*status = SELF_CONNECT;
		emit modelNotificationSignal(signal);
	}
	else if (*status == UPPER_DIS_CONNECT && signal->signalType == CONNECT_SUCCESS && signal->playerType == UPPERHOUSE) {
		*status = UPPER_CONNECT;
		emit modelNotificationSignal(signal);
	}
	else if (*status == LOWER_DIS_CONNECT && signal->signalType == CONNECT_SUCCESS && signal->playerType == LOWERHOUSE) {
		*status = LOWER_CONNECT;
		emit modelNotificationSignal(signal);
	}
	else if (*status == SELF_CONNECT && signal->signalType == READY && signal->playerType == SELF) {
		*status = SELF_READY;
		emit modelNotificationSignal(signal);
	}
	else if (*status == UPPER_CONNECT && signal->signalType == READY && signal->playerType == UPPERHOUSE) {
		*status = UPPER_READY;
		emit modelNotificationSignal(signal);
	}
	else if (*status == LOWER_CONNECT && signal->signalType == READY && signal->playerType == LOWERHOUSE) {
		*status = LOWER_READY;
		emit modelNotificationSignal(signal);
	}
	else if (signal->signalType == DEAL_CARD && *status == SELF_READY) {
		QByteArray whole = signal->cardTransfer;
		QByteArray here;
		here.resize(34);
		int start = 40;  //modify here
		for (int i = 0; i < 34; i++) {
			here[i] = whole[start + i];
		}
		(*onHand) = (*onHand) + RuleCardSet(here);
		CARDSET origin;
		for (int i = 0; i < (*m_Num); i++) {
			origin.add(m_Card->cards[i]);
		}
		int index = 0;
		CARDSET tmp = here + origin;
		while (!tmp.setIsEmpty()) {
			m_Card->cards[index] = tmp.setPop();
			index++;
		}
		(*m_Num) = index;

		if (signal->playerType == SELF) *status = SELF_CHOOSE_TURN;
		else *status = SELF_NOT_CHOOSE_TURN;

		signal->playerType == SELF;
		emit modelNotificationSignal(signal);
	}
	else if (signal->signalType == DEAL_CARD && *status == UPPER_READY) {
		QByteArray whole = signal->cardTransfer;
		QByteArray here;
		here.resize(34);
		int start = 6;  //modify here
		for (int i = 0; i < 34; i++) {
			here[i] = whole[start + i];
		}
		(*onHand) = (*onHand) + RuleCardSet(here);
		CARDSET origin;
		for (int i = 0; i < (*m_Num); i++) {
			origin.add(m_Card->cards[i]);
		}
		int index = 0;
		CARDSET tmp = here + origin;
		while (!tmp.setIsEmpty()) {
			m_Card->cards[index] = tmp.setPop();
			index++;
		}
		(*m_Num) = index;

		if (signal->playerType == UPPERHOUSE)  *status = UPPER_CHOOSE_TURN;
		else *status = UPPER_NOT_CHOOSE_TURN;

		signal->playerType == UPPERHOUSE;
		emit modelNotificationSignal(signal);
	}
	else if (signal->signalType == DEAL_CARD && *status == LOWER_READY) {
		QByteArray whole = signal->cardTransfer;
		QByteArray here;
		here.resize(34);
		int start = 74;  //modify here
		for (int i = 0; i < 34; i++) {
			here[i] = whole[start + i];
		}
		(*onHand) = (*onHand) + RuleCardSet(here);
		CARDSET origin;
		for (int i = 0; i < (*m_Num); i++) {
			origin.add(m_Card->cards[i]);
		}
		int index = 0;
		CARDSET tmp = here + origin;
		while (!tmp.setIsEmpty()) {
			m_Card->cards[index] = tmp.setPop();
			index++;
		}
		(*m_Num) = index;

		if (signal->playerType == LOWERHOUSE )* status = LOWER_CHOOSE_TURN;
		else *status = LOWER_NOT_CHOOSE_TURN;

		signal->playerType == LOWERHOUSE;
		emit modelNotificationSignal(signal);
	}
	else if (0) //this is for handing cards
	{
		CARDSET zero;
		(*selected) = zero;
		(*onHand) = (*onHand) - RuleCardSet(signal->cardTransfer);
		CARDSET origin;
		for (int i = 0; i < (*m_Num); i++) {
			origin.add(m_Card->cards[i]);
		}
		int index = 0;
		CARDSET tmp = signal->cardTransfer - origin;
		while (!tmp.setIsEmpty()) {
			m_Card->cards[index] = tmp.setPop();
			index++;
		}
		(*m_Num) = index;
		emit modelNotificationSignal(signal);
	}
}

