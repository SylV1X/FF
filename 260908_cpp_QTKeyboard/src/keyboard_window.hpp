#pragma once

#include <cstddef>

#include <QKeyEvent>
#include <QLineEdit>
#include <QWidget>

#include "keyboard.hpp"

namespace biv {
	class KeyBoardWindow : public QWidget {
		Q_OBJECT
		
		public slots:
			void show_window();
		
		private:
			QLineEdit* display;
			KeyBoard* keyboard;
			
		public:
			KeyBoardWindow(QWidget* parent = nullptr);
			
		protected:
			void keyPressEvent(QKeyEvent* event) override;
		
		private:
			void handle_special_key(const int key);
	};
}
