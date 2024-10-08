#include <iostream>
#include <QWidget>
#include <QApplication>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    std::cout << "Open new window" << std::endl;
    // Используем базовый QWidget вместо CustomWidget
    QScopedPointer<QWidget> widget(new QWidget());
    widget->resize(1200, 400);
    widget->show();

    return app.exec();
}
