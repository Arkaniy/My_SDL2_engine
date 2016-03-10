//#include "game_ui.h"
//#include "config.h"

//Game_UI::Game_UI() {
//	_textButtons.push_back(TextButton());
//	_textButtons.push_back(TextButton());

//	for (TextButton& button : _textButtons) {
//		button.setListener(this);
//		button.setPictureActive(TP_Button);
//		button.setPicturePressed(TP_ButtonPressed);
//	}

//	_textButtons[0].setX(15);
//	_textButtons[0].setY(Config::WindowH - _textButtons[0].getH() - 15);
////	_buttons[0].setX(Config::WindowW / 2 - _buttons[0].getW() / 2);
////	_buttons[0].setY(15);
//	_textButtons[0].setWidgetEvent(BE_Menu);
//	_textButtons[0].setText("Menu");

//	_textButtons[1].setX(_textButtons[0].getW() + 30);
//	_textButtons[1].setY(Config::WindowH - _textButtons[1].getH() - 15);
//	_textButtons[1].setWidgetEvent(BE_Quit);
//	_textButtons[1].setText("Quit");
//}

//void Game_UI::draw() const {
//	for (const TextButton& button : _textButtons) {
//		button.draw();
//	}
//}

//bool Game_UI::handleEvent(SDL_Event &event) {
//	bool handled = false;
//	if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
//		for (TextButton& button : _textButtons) {
//			if (button.handleEvent(event)) {
//				handled = true;
//				break;
//			}
//		}
//	}
//	return handled;
//}

//void Game_UI::handleWidgetEvent(WidgetEvent event) {
//	switch (event._gameEvent) {
//	default:
//		//_listener->handleWidgetEvent(event);
//		break;
//	}
//}
