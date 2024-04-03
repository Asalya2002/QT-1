#include <QCoreApplication>
#include <QDebug>
#include "FileMonitor.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv); // Создаем объект приложения

    QString filePath = "C:\\123.txt";
    FileMonitor fileMonitor(filePath); // Создаем экземпляр класса FileMonitor для мониторинга указанного файла

    QObject::connect(&fileMonitor, &FileMonitor::fileStatusChanged, [](const QString& status) { // Устанавливаем соединение для обработки сигнала fileStatusChanged
        qDebug() << status; // Выводим статус файла в консоль
    });
    // Тестирование Case 1: Проверка начального статуса файла
    fileMonitor.checkFile();

    // Case 2: Имитация изменения файла (увеличение размера файла)
    QFile file(filePath);
    if (file.open(QIODevice::Append)) { // Открываем файл для добавления данных в конец
        file.write("Test data"); // Добавляем данные в файл
        file.close(); // Закрываем файл
    } else {
        qDebug() << "Ошибка при открытии файла для записи";
    }
    return a.exec();
}
