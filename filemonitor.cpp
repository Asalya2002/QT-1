#include "filemonitor.h"
#include <QTimer>

FileMonitor::FileMonitor(const QString& filePath, QObject* parent) : QObject(parent), m_filePath(filePath)
{
    m_fileInfo.setFile(filePath); // Устанавливаем информацию о файле для указанного пути
    QTimer* timer = new QTimer(this); // Создаем таймер для периодической проверки файла
    connect(timer, &QTimer::timeout, this, &FileMonitor::checkFile); // Подключаем сигнал таймера к слоту checkFile
    timer->start(100); // Запускаем таймер для периодической проверки файла (обновление каждые 100 миллисекунд)
}

void FileMonitor::checkFile()
{
    QFileInfo newFileInfo(m_filePath); // Получаем информацию о файле для текущего пути
    static qint64 previousSize = -1; // Статическая переменная для хранения предыдущего размера файла

    if (newFileInfo.exists()) { // Проверяем, существует ли файл
        if (newFileInfo.size() != 0 && newFileInfo.size() != m_fileInfo.size()) {
            emit fileStatusChanged("Файл был изменен, размер: " + QString::number(newFileInfo.size())); // Отправляем сигнал об изменении файла
        } else if (newFileInfo.size() != 0 && newFileInfo.size() == previousSize) {
            emit fileStatusChanged("Файл существует, размер: " + QString::number(newFileInfo.size())); // Отправляем сигнал о существующем файле
        }
    } else {
        emit fileStatusChanged("Файл не существует"); // Отправляем сигнал о том, что файла не существует
    }
    m_fileInfo = newFileInfo; // Обновляем информацию о файле
    previousSize = newFileInfo.size(); // Сохраняем текущий размер файла для следующей проверки
    QTimer::singleShot(1000, this, &FileMonitor::checkFile); // Устанавливаем проверку файла через 1 секунду
}
