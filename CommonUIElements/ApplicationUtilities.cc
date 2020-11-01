//
// Created by jwscoggins on 10/31/20.
//

#include "ApplicationUtilities.h"
#include <QApplication>
#include <QDir>
#include <filesystem>

const std::filesystem::path&
getApplicationDirectory() noexcept {
    static bool initialized = false;
    static std::filesystem::path dir;
    if (!initialized) {
       initialized = true;
       auto thePath = QApplication::applicationDirPath();
       dir = thePath.toStdString();
    }
    return dir;
}
const std::filesystem::path&
getResourcesDirectory() noexcept {
    static std::filesystem::path applicationDir;
    static bool initialized = false;
    if (!initialized) {
        initialized = true;
        applicationDir = getApplicationDirectory() / "resources";
    }
    return applicationDir;
}

const std::filesystem::path&
getPortraitsDirectory() noexcept {
    static bool init = false;
    static std::filesystem::path dir;
    if (!init) {
        init = true;
        dir = getApplicationDirectory() / "portraits";
    }
    return dir;
}

const std::filesystem::path&
getTacticalsDirectory() noexcept {
    static bool init = false;
    static std::filesystem::path dir;
    if (!init) {
        init = true;
        dir = getApplicationDirectory() / "directory";
    }
    return dir;
}
const std::filesystem::path&
getBinaryResourcesDir() noexcept {
    static bool init = false;
    static std::filesystem::path dir;
    if (!init) {
        init = true;
        dir = getApplicationDirectory() / "binary";
    }
    return dir;
}
