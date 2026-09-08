#pragma once

#include <cstddef>

#include <QPushButton>
#include <QString>
#include <QWidget>

namespace biv {
	class KeyBoardButton : public QPushButton {
		Q_OBJECT  
		signals:
			void button_clicked_by_mouse(const QString& text);
			
		private slots:
			void mouse_click();
		
		public:
			KeyBoardButton(const QString& text = "", QWidget* parent = nullptr);
	};
}
