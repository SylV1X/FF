#pragma once

#include <cstddef>

#include <QLabel>
#include <QWidget>
#include <QPushButton>

namespace biv {
	class WelcomeWindow : public QWidget {
		Q_OBJECT
		
		signals:
			void on_welcome_finished();
			
		public slots:
			void handle_go_pressed();
		
		private:
			QPushButton* button;

		public:
			WelcomeWindow(QWidget* parent = nullptr);
	};
}
