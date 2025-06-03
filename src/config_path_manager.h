#ifndef CONFIG_PATH_MANAGER_H
#define CONFIG_PATH_MANAGER_H

#include <QString>
#include <QDir>
#include <QStandardPaths>
#include <QCoreApplication>
#include <QDebug>

class ConfigPathManager
{
public:
    static QString getConfigFilePath(const QString& filename)
    {
        // Try multiple locations in order of preference
        QStringList searchPaths = {
            // 1. User's config directory (preferred for user settings)
            QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/" + QCoreApplication::applicationName(),
            
            // 2. User's data directory
            QStandardPaths::writableLocation(QStandardPaths::AppDataLocation),
            
            // 3. System-wide config directory
            "/usr/share/" + QCoreApplication::applicationName(),
            
            // 4. Local installation directory
            "/usr/local/share/" + QCoreApplication::applicationName(),
            
            // 5. Application directory (for development)
            QCoreApplication::applicationDirPath(),
            
            // 6. Current working directory (fallback)
            QDir::currentPath()
        };
        
        // First, try to find existing file
        for (const QString& path : searchPaths) {
            QString fullPath = QDir(path).absoluteFilePath(filename);
            if (QFile::exists(fullPath)) {
                qDebug() << "Found config file at:" << fullPath;
                return fullPath;
            }
        }
        
        // If file doesn't exist, return writable location for creation
        QString userConfigDir = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/" + QCoreApplication::applicationName();
        QDir().mkpath(userConfigDir); // Create directory if it doesn't exist
        
        QString defaultPath = QDir(userConfigDir).absoluteFilePath(filename);
        qDebug() << "Config file not found, will create at:" << defaultPath;
        
        return defaultPath;
    }
    
    static QString getDataFilePath(const QString& filename)
    {
        // For read-only data files (templates, defaults, etc.)
        QStringList searchPaths = {
            // 1. System installation directory
            "/usr/share/" + QCoreApplication::applicationName(),
            "/usr/local/share/" + QCoreApplication::applicationName(),
            
            // 2. Application directory (development)
            QCoreApplication::applicationDirPath(),
            
            // 3. Current directory (fallback)
            QDir::currentPath()
        };
        
        for (const QString& path : searchPaths) {
            QString fullPath = QDir(path).absoluteFilePath(filename);
            if (QFile::exists(fullPath)) {
                qDebug() << "Found data file at:" << fullPath;
                return fullPath;
            }
        }
        
        qWarning() << "Data file not found:" << filename;
        return QString(); // Return empty string if not found
    }
    
    static void copyDefaultConfig(const QString& sourceFile, const QString& targetFile)
    {
        // Copy default config from installation to user directory
        if (!QFile::exists(targetFile) && QFile::exists(sourceFile)) {
            if (QFile::copy(sourceFile, targetFile)) {
                qDebug() << "Copied default config from" << sourceFile << "to" << targetFile;
            } else {
                qWarning() << "Failed to copy default config";
            }
        }
    }
};

#endif // CONFIG_PATH_MANAGER_H
