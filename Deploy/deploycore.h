/*
 * Copyright (C) 2018-2022 QuasarApp.
 * Distributed under the lgplv3 software license, see the accompanying
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
 */

#ifndef DEPLOYUTILS_H
#define DEPLOYUTILS_H

#include <QStringList>
#include <QDebug>
#include <QFileInfo>
#include "deploy_global.h"
#include "defines.h"
#include "quasarapp.h"

enum MSVCVersion: int {
    MSVC_Unknown = 0x0,
    MSVC_x64 = 0x01,
    MSVC_x32 = 0x02,
    MSVC_13 = 0x10,
    MSVC_15 = 0x20,
    MSVC_17 = 0x40,
    MSVC_19 = 0x80,
};

/**
 * @brief The QtMajorVersion enum
 */
enum QtMajorVersion: int {
    NoQt = 0x0,
    Qt4 = 0x01,
    Qt5 = 0x02,
    Qt6 = 0x04
};

struct DEPLOYSHARED_EXPORT QtModuleEntry {
    quint64 module;
    const char *option;
    const char *libraryName;
    const char *translation;
};


enum Platform {
    UnknownPlatform = 0x0000,
    // Windows
    Win32           = 0x0001,
    Win64           = 0x0002,
    Win_ARM_32      = 0x0004,
    win_ARM_64      = 0x0008,
    Win             = Win32 | Win64,

    // Unix
    Unix_x86_32     = 0x0010,
    Unix_x86_64     = 0x0020,
    Unix_x86        = Unix_x86_32 | Unix_x86_64,
    Unix_ARM_32     = 0x0040,
    Unix_ARM_64     = 0x0080,
    Unix_ARM        = Unix_x86_32 | Unix_x86_64,
    Unix            = Unix_x86 | Unix_ARM,

    // Other

    // Web
    WebGl           = 0x0100,
    WebRemote       = 0x0200,

    GeneralFile     = 0x0400
};

/**
 * @brief The LibPriority enum This is library priority.
 * The lower the priority of the topics, the library is the most suitable for distribution.
 */
enum LibPriority : int {
    // ================= General Libraryes
    /// This is qt libraryes.
    QtLib = 0x0,
    /// This is user libraryes.
    ExtraLib,
    /// This is qt 3dParty and user libraryes. (distribution-safe libraries)
    AllowedLib,

    // ================= System Libraryes
    /// This is rest of all libraryes (frm system and another).
    SystemLib,
    /// This is libraryes from another proggram distributions.
    AlienLib,
    /// This is General Files.
    NotFile = 0xF,
};

enum class WinAPI : quint8 {
    NoWinAPI    = 0x00,
    Other       = 0x01,
    Core        = 0x02,
    Devices     = 0x04,
    Eventing    = 0x08,
    Crt         = 0x10,
    Security    = 0x20,
    Base        = 0x40
};

uint qHash (WinAPI i);

enum class RunMode: int {
    Info,
    Deploy,
    Clear,
    Init,
    Template
};

class Extracter;
class DeployConfig;

class DEPLOYSHARED_EXPORT DeployCore
{

private:
    static QString getMSVCName(MSVCVersion msvc);
    static QString getMSVCVersion(MSVCVersion msvc);

public:
    enum QtModule : quint64
    {
        NONE                      = 0x0000000000000000,
        QtBluetoothModule         = 0x0000000000000001,
        QtConcurrentModule        = 0x0000000000000002,
        QtCoreModule              = 0x0000000000000004,
        QtDeclarativeModule       = 0x0000000000000008,
        QtDesignerComponents      = 0x0000000000000010,
        QtDesignerModule          = 0x0000000000000020,
        QtGuiModule               = 0x0000000000000040,
        QtHelpModule              = 0x0000000000000080,
        QtMultimediaModule        = 0x0000000000000100,
        QtMultimediaWidgetsModule = 0x0000000000000200,
        QtMultimediaQuickModule   = 0x0000000000000400,
        QtNetworkModule           = 0x0000000000000800,
        QtNfcModule               = 0x0000000000001000,
        QtOpenGLModule            = 0x0000000000002000,
        QtPositioningModule       = 0x0000000000004000,
        QtPrintSupportModule      = 0x0000000000008000,
        QtQmlModule               = 0x0000000000010000,
        QtQuickModule             = 0x0000000000020000,
        QtQuickParticlesModule    = 0x0000000000040000,
        QtScriptModule            = 0x0000000000080000,
        QtScriptToolsModule       = 0x0000000000100000,
        QtSensorsModule           = 0x0000000000200000,
        QtSerialPortModule        = 0x0000000000400000,
        QtSqlModule               = 0x0000000000800000,
        QtSvgModule               = 0x0000000001000000,
        QtTestModule              = 0x0000000002000000,
        QtWidgetsModule           = 0x0000000004000000,
        QtWinExtrasModule         = 0x0000000008000000,
        QtXmlModule               = 0x0000000010000000,
        QtXmlPatternsModule       = 0x0000000020000000,
        QtWebKitModule            = 0x0000000040000000,
        QtWebKitWidgetsModule     = 0x0000000080000000,
        QtQuickWidgetsModule      = 0x0000000100000000,
        QtWebSocketsModule        = 0x0000000200000000,
        QtEnginioModule           = 0x0000000400000000,
        QtWebEngineCoreModule     = 0x0000000800000000,
        QtWebEngineModule         = 0x0000001000000000,
        QtWebEngineWidgetsModule  = 0x0000002000000000,
        QtQmlToolingModule        = 0x0000004000000000,
        Qt3DCoreModule            = 0x0000008000000000,
        Qt3DRendererModule        = 0x0000010000000000,
        Qt3DQuickModule           = 0x0000020000000000,
        Qt3DQuickRendererModule   = 0x0000040000000000,
        Qt3DInputModule           = 0x0000080000000000,
        QtLocationModule          = 0x0000100000000000,
        QtWebChannelModule        = 0x0000200000000000,
        QtTextToSpeechModule      = 0x0000400000000000,
        QtSerialBusModule         = 0x0000800000000000,
        QtGamePadModule           = 0x0001000000000000,
        Qt3DAnimationModule       = 0x0002000000000000,
        QtWebViewModule           = 0x0004000000000000,
        Qt3DExtrasModule          = 0x0008000000000000,
        QtVirtualKeyboard         = 0x0010000000000000,
        // Qt6
        QtOpenGLWidgetsModule     = 0x0010000000000000,
        QtSvgWidgetsModule        = 0x0020000000000000,
        QtShaderToolsModule       = 0x0040000000000000
    };

    DeployCore() = delete;


    static QtModuleEntry qtModuleEntries[];

    static const DeployConfig * _config;

    static MSVCVersion getMSVC(const QString & _qtBin);
    static QString getVCredist(const QString & _qtBin);

    /**
     * @brief isQtLib This method check full path of the library. If the @a lib contains only name then this method retun QtMajorVersion::NoQt enum. For validate @a lib by name only use the DeployCore::isQtLibName method.
     * @param lib This is library full path..
     * @return major version of the Qt.
     */
    static QtMajorVersion isQtLib(const QString &lib);

    /**
     * @brief isQtLib This method check name of the library.
     * @param lib This is library full path..
     * @return major version of the Qt.
     */
    static QtMajorVersion isQtLibName(const QString &lib);

    static bool isExtraLib(const QString &lib);
    static QChar getSeparator(int lvl);
    static bool isAlienLib(const QString &lib);

    /**
     * @brief isAllowedLib This method checks the library if the library is allowed or not, allowet libraryes is added with extraLibs method.
     * @param lib This is library fuul path
     * @return true if lirary is allowed
     */
    static bool isAllowedLib(const QString &lib);

    /**
     * @brief QtThreethepartyLibs This method return list of 3rdparty libraryes of qt for selected platform.
     * @param platform This is OS name.
     * @return list of 3rdparty libs.
     * @note This method is hardcode.
     * @note See Task https://github.com/QuasarApp/CQtDeployer/issues/422 of the CQtDeployer project.
     */
    static QStringList Qt3rdpartyLibs(Platform platform);

    /**
     * @brief platformToString This method convert platform value to string value.
     * @param platform This is input platform value.
     * @return String name of the @a platform
     */
    static QString platformToString(Platform platform);

    /**
     * @brief getPlatformFromString This method return platform enum value form string.
     * @param platformName This is string platform value.
     * @return platform enum value form string.
     */
    static Platform getPlatformFromString(const QString &platformName);

    static char getEnvSeparator();

    static LibPriority getLibPriority(const QString &lib);

    /**
     * @brief containsModule This method compare lib name and module of qt.
     * @param moduleLibrary this is name of module library
     * @param lib This is library name
     * @return true if library has some module that as muduleIndex
     */
    static bool containsModule(const QString &moduleLibrary, const QString &lib);
    static DeployCore::QtModule getQtModule(const QString& path);
    static void addQtModule(DeployCore::QtModule& module, const QString& path);

    /**
     * @brief isConsole This method return true if the librarye depends of the gui libraryes.
     * @return true if the librarye is gui application.
     */
    static bool isGui(DeployCore::QtModule module);
    static RunMode getMode();
    static void help();
    static QuasarAppUtils::OptionsDataList avilableOptions();

    static QStringList extractTranslation(const QSet<QString> &libs);
    static QString getAppVersion();
    static QString getAppVersionName();

    static QString getQtVersion();
    static void printVersion();
    static int find(const QString &str, const QStringList &list);
    static bool isLib(const QFileInfo &file);
    static bool isExecutable(const QFileInfo &file);
    static bool isContainsArraySeparators(const QString& val,
                                          int lastLvl = 2);
    static QString findProcess(const QString& env, const QString& proc);

    static QStringList debugExtensions();
    static bool isDebugFile(const QString& file);

    static bool isSnap();
    static QString snapRootFS();
    static QString transportPathToSnapRoot(const QString &path);
    static bool checkSystemBakupSnapInterface();

    /**
     * @brief getLibCoreName This method remove platfomr specificly prefixes and sufixes of the librarry.
     *  Example : getLibCoreName(libTest.so) return Test
     * @param info This is information about checked library.
     * @return return core name of the library.
     */
    static QString getLibCoreName(const QFileInfo& info);

    /**
     * @brief systemLibsFolderName This method return name of the systems librares.
     * @return Name of folder with system libraryes.
     * @note see https://github.com/QuasarApp/CQtDeployer/issues/396
     */
    static QString systemLibsFolderName();

    /**
     * @brief printInternalError This function print message of the internal error.
     * @param function This is function name.
     * @param file This is file name of code.
     * @param line This is line number of the code.
     */
    static void printInternalError(const char *function, const char* file, int line);

    /**
     * @brief findItem This method search input file in prefixes and return absolute path to the found file. If file is not exists the return empty string.
     * @param file This is file path. If the file path si absalute path then return @a file value.
     * @return file info of the found file.
     */
    static QFileInfo findItem(const QString &file);

    /**
     * @brief getCaseSensitivity This method return case sensitivity for a @a checkedFile. Usually return Qt::CaseSensiativy exept windows binaryes files like a dll and exe.
     * @param checkedFile This is checked file. By default empty value.
     * @return Qt CaseSensitivity value
     */
    static Qt::CaseSensitivity getCaseSensitivity(const QString& checkedFile = "");
};

#define internalError() DeployCore::printInternalError(__FUNCTION__, __FILE__, __LINE__)
#endif // DEPLOYUTILS_H
