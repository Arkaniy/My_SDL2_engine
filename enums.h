#ifndef ENUMS_H
#define ENUMS_H

enum ScreenState { SS_Game, SS_Menu, SS_Credits, SS_Quit, SS_TOTAL };

enum BaseEvent { BE_NewGame, BE_Menu, BE_Credits, BE_Quit, BE_TOTAL };
enum GameEvent { GE_TOTAL };
struct WidgetEvent {
	WidgetEvent() {}
	WidgetEvent(BaseEvent baseEvent) { _baseEvent = baseEvent; }
	WidgetEvent(GameEvent gameEvent) { _gameEvent = gameEvent; }

	BaseEvent _baseEvent = BE_TOTAL;
	GameEvent _gameEvent = GE_TOTAL;
};

enum TileType { TT_Passable, TT_Wall, TT_TOTAL};
enum TilePicture { TP_BackgroundMenu, TP_BackgroundWait, TP_Button, TP_ButtonPressed, TP_Tile, TP_Man, TP_Man1, TP_Wall, TP_TOTAL };
enum TileAnimation { TA_ManRight, TA_ManLeft };

#endif // ENUMS_H
