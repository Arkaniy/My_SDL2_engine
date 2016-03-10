#ifndef ENUMS_H
#define ENUMS_H

enum ScreenState { SS_Game, SS_Menu, SS_Credits, SS_Quit, SS_TOTAL };

enum BaseEvent { BE_NewGame, BE_Menu, BE_Credits, BE_Quit, BE_TOTAL };
enum GameEvent { GE_TOTAL };
enum EventType { ET_BaseEvent, ET_GameEvent, ET_TOTAL };

struct WidgetEvent {
	EventType _eventType;
	union {
		BaseEvent _baseEvent;
		GameEvent _gameEvent;
	};

	WidgetEvent() { _eventType = ET_TOTAL; }
	WidgetEvent(BaseEvent baseEvent) { _eventType = ET_BaseEvent; _baseEvent = baseEvent; }
	WidgetEvent(GameEvent gameEvent) { _eventType = ET_GameEvent; _gameEvent = gameEvent; }
};

enum TileType { TT_Passable, TT_Wall, TT_TOTAL};
enum FontCollection { FC_Main, FC_FPS, FC_TOTAL };
enum TilePicture { TP_Window, TP_BackgroundMenu, TP_BackgroundWait, TP_Button, TP_ButtonPressed, TP_Tile, TP_Man, TP_Man1, TP_Wall, TP_TOTAL };
enum TileAnimation { TA_ManRight, TA_ManLeft };

#endif // ENUMS_H
