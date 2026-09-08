#pragma once

#include <cstddef>

#include <QLabel>
#include <QWidget>
#include <QPushButton>

namespace biv {
	class WelcomeWindow : public QWidget {
		Q_OBJECT
		
		signals:
			void button_pressed();
			
		public slots:
			void go_to_keyboard();
		
		private:
			QPushButton* button;

		public:
			WelcomeWindow(QWidget* parent = nullptr);
	};
}
