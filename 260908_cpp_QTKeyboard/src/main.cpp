#include <QApplication>

#include "welcome_window.hpp"
#include "keyboard_window.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    
    biv::WelcomeWindow welcome_window;
    biv::KeyBoardWindow keyboard_window;
	
    QObject::connect(&welcome_window, &biv::WelcomeWindow::on_welcome_finished,
                     &keyboard_window, &biv::KeyBoardWindow::show_window);
					 
	welcome_window.show();
    
    return app.exec();
}