#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_window.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QTransform>
#include <QPushButton>

#include "../utility/common/common.h"

#define PLAYER_NUM        3
#define COLOR_NUM         4
#define POKER_NUM         18

#define BTN_NUM           9
#define ENTER_BTN         0
#define QUIT_BTN          1
#define READY_BTN         2
#define CHOOSE_LL_BTN     3
#define SKIP_LL_BTN       4
#define PLAY_CARD_BTN     5
#define SKIP_CARD_BTN     6
#define LOSE_BTN          7
#define WIN_BTN           8

#define STATE_NUM         3
#define READY_STATE       0
#define SKIP_LL_STATE     1
#define SKIP_CARD_STATE   2

#define HEAD_NUM          2
#define FARMER_HEAD       0
#define LANDLORD_HEAD     1

#define BTN_WIDTH         0.16
#define BTN_HEIGHT        0.08
#define STATE_WIDTH       0.16
#define STATE_HEIGHT      0.08
#define CARD_WIDTH        0.10
#define CARD_HEIGHT       0.15
#define HEAD_WIDTH        0.1
#define HEAD_HEIGHT       0.1

#define SLOT_LEFT         0.2
#define SLOT_TOP          0.75
#define SLOT_WIDTH        0.6
#define SLOT_HEIGHT       0.25

#define ON_HAND_TOP       0.3
#define ON_HAND_INT       0.05 
#define ON_HAND_RISE      0.2

#define BTN_TOP           0.64
#define BTN_INT           0.05

#define SELF_STATE_TOP    0.64
#define SELF_PLAY_TOP     0.45
#define SELF_PLAY_INT     0.03

#define UPPER_STATE_LEFT  0.2
#define UPPER_STATE_TOP   0.25
#define UPPER_HEAD_LEFT   0.02
#define UPPER_HEAD_TOP    0.25
#define UPPER_PLAY_LEFT   0.15
#define UPPER_PLAY_TOP    0.225
#define UPPER_PLAY_INT    0.02

#define LOWER_STATE_RIGHT 0.8
#define LOWER_STATE_TOP   0.25
#define LOWER_HEAD_RIGHT  0.98
#define LOWER_HEAD_TOP    0.25
#define LOWER_PLAY_RIGHT  0.8
#define LOWER_PLAY_TOP    0.225
#define LOWER_PLAY_INT    0.02

class customScene : public QGraphicsScene
{
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
};

class Window : public QMainWindow
{
	Q_OBJECT

public:
	Window(QWidget *parent = Q_NULLPTR);

	void setOnHandNum(std::shared_ptr<int> m_onHandNum) { onHandNum = m_onHandNum; }
	void setOnHandCard(std::shared_ptr<CARD20> m_onHandCard) { onHandCard = m_onHandCard; }
	void setOnHandSelected(std::shared_ptr<BOOL20> m_onHandSelected) { onHandSelected = m_onHandSelected; }
	void setLowerNum(std::shared_ptr<int> m_lowerNum) { lowerNum = m_lowerNum; }
	void setLowerCard(std::shared_ptr<CARD20> m_lowerCard) { lowerCard = m_lowerCard; }
	void setUpperNum(std::shared_ptr<int> m_upperNum) { upperNum = m_upperNum; }
	void setUpperCard(std::shared_ptr<CARD20> m_upperCard) { upperCard = m_upperCard; }
	void setOnTableNum(std::shared_ptr<int> m_onTableNum) { onTableNum = m_onTableNum; }
	void setOnTableCard(std::shared_ptr<CARD20> m_onTableCard) { onTableCard = m_onTableCard; }
	void setLandLordNum(std::shared_ptr<int> m_landLordNum) { landLordNum = m_landLordNum; }
	void setLandLordCard(std::shared_ptr<CARD20> m_landLordCard) { landLordCard = m_landLordCard; }

protected:
	virtual void resizeEvent(QResizeEvent* size);

private:
	Ui::FightLandLordClass ui;
	
	std::shared_ptr<int> onHandNum;
	std::shared_ptr<CARD20> onHandCard;
	std::shared_ptr<BOOL20> onHandSelected;
	std::shared_ptr<int> lowerNum;
	std::shared_ptr<CARD20> lowerCard;
	std::shared_ptr<int> upperNum;
	std::shared_ptr<CARD20> upperCard;
	std::shared_ptr<int> onTableNum;
	std::shared_ptr<CARD20> onTableCard;
	std::shared_ptr<int> landLordNum;
	std::shared_ptr<CARD20> landLordCard;

	customScene scene;
	QGraphicsPixmapItem cardItem[COLOR_NUM][POKER_NUM];
	QGraphicsPixmapItem stateItem[STATE_NUM][PLAYER_NUM];
	QGraphicsPixmapItem headItem[HEAD_NUM][PLAYER_NUM];
	QPushButton button[BTN_NUM];

	QGraphicsRectItem cardSlot;

	void initAll(void);

	void drawState(void);
	void drawSelfCard(void);

	void drawSelfPlayCard(void);
	void drawUpperPlayCard(void);
	void drawLowerPlayCard(void);

	void drawBackGround(void);

	void clearScreen(void);


	void initItem(QGraphicsPixmapItem &item, QString path, qreal rw, qreal rh);
	void initButton(QPushButton &button, QString path, qreal rw, qreal rh);

	void addItemToScene(QGraphicsPixmapItem &item, qreal rx, qreal ry);
	void addParentItemToScene(QGraphicsRectItem &parent, qreal rx, qreal ry, qreal rw, qreal rh);
	void addItemToParentItem(QGraphicsPixmapItem &item, QGraphicsRectItem &parent, qreal rx, qreal ry);
	
	void addButtonToScene(QPushButton &button, qreal rx, qreal ry);

signals:
	void windowCommandSignal(std::shared_ptr<Signal> signal);

public slots:
	void connectBtnClick(void);
	void disconnectBtnClick(void);
	void readyBtnClick(void);
	void chooseLandLordBtnClick(void);
	void skipLandLordBtnClick(void);
	void playCardBtnClick(void);
	void skipCardBtnClick(void);
	void 

	void windowNotificationSlot(std::shared_ptr<Signal> signal);

};
