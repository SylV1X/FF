#include "welcome_window.hpp"

#include <QVBoxLayout>

using biv::WelcomeWindow;

WelcomeWindow::WelcomeWindow(QWidget* parent) : QWidget(parent) {
	const int welcome_message_width = 400;
	const int welcome_message_height = 300;
	resize(welcome_message_width, welcome_message_height);
	setWindowTitle("Добро пожаловать!");
	
	QLabel* welcome_text = new QLabel("Клавиатура", this);
	welcome_text->setFont(QFont("Roboto", 20));

	button = new QPushButton("Перейти", this);
	button->setMinimumHeight(40);
	
	QVBoxLayout* main_layout = new QVBoxLayout(this);
	main_layout->addWidget(welcome_text);
	main_layout->addWidget(button);
	
	connect(button, &QPushButton::clicked, this, &WelcomeWindow::go_to_keyboard);
}

void WelcomeWindow::go_to_keyboard() {
	this->hide(); 
	
	emit button_pressed();
}