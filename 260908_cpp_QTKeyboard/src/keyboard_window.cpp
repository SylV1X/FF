#include "keyboard_window.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>

using biv::KeyBoardWindow;

KeyBoardWindow::KeyBoardWindow(QWidget* parent) : QWidget(parent) {
	const int keyboard_width = 1160;
	const int keyboard_height = 710;
	resize(keyboard_width, keyboard_height);
    setWindowTitle("Грустная Клавиатура");
	
	QPixmap pixmap("img/grustnii-smail.png");
	QLabel* image = new QLabel(this);
	image->setFixedSize(200, 200);
	image->setPixmap(pixmap);
	image->setScaledContents(true);
	
	QHBoxLayout* smail_layout = new QHBoxLayout();
	smail_layout->addWidget(image);

    display = new QLineEdit();
	display->setMinimumHeight(80);
	display->setFont(QFont("Roboto", 40));
    display->setReadOnly(true);
	display->setText("Помоги мне заработать лучше...");
	setFocusPolicy(Qt::StrongFocus);
    setFocus();

	keyboard = new KeyBoard(keyboard_width);

    QVBoxLayout* main_layout = new QVBoxLayout(this);
	main_layout->addLayout(smail_layout);
    main_layout->addWidget(display);
    main_layout->addWidget(keyboard);
}

void KeyBoardWindow::keyPressEvent(QKeyEvent* event) {
    const int key = event->nativeVirtualKey();
    
    if (keyboard->is_key_allowed(key)) {
        if (keyboard->is_special_key(key)) {
            handle_special_key(key);
        } else {
            display->setText(display->text() + keyboard->get_key_text(key));
        }
        keyboard->animate_button(key);
    }
}

void KeyBoardWindow::show_window() {
	this->show();
}

void KeyBoardWindow::handle_special_key(const int code) {
	switch(code) {
		case 8: {
			QString text = display->text();
			if (!text.isEmpty()) {
				text.chop(1);
				display->setText(text);
			}
			break;
		}
		case 32: {
			display->setText(display->text() + " ");
			break;
		}
		case 13: {
			display->clear();
			break;
		}
	}
}