#include "widget.h"

Widget::Widget() {
	_listener = nullptr;
}

Widget::~Widget() {

}

void Widget::setListener(Listener *listener) {
	_listener = listener;
}

Listener::Listener() {

}

Listener::~Listener() {

}
