#ifndef FILEMONITOR_H
#define FILEMONITOR_H

#include <QObject>
#include <QFileInfo>

class FileMonitor : public QObject
{
    Q_OBJECT
public:
    explicit FileMonitor(const QString& filePath, QObject* parent = nullptr); // Конструктор класса, принимающий путь к файлу и необязательный родительский объект

signals:
    void fileStatusChanged(const QString& status); // Сигнал, отправляемый при изменении статуса файла

public slots:
    void checkFile(); // Слот для проверки статуса файла

private:
    QString m_filePath; // Путь к файлу
    QFileInfo m_fileInfo; // Информация о файле
};

#endif // FILEMONITOR_H


