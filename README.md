# rp2040CardSoft
rp2040 + ST7789 240x320 display module

# Сборка прошивки (Win10)
## Установка MinGW
- Загрузить zip-архив с [сайта](https://winlibs.com). Для загрузки выбрать последнюю версию с UCRT runtime и без поддержки LLVM
- Загруженный архив распаковать в `C:\`, таким образом должна появиться директория `C:\mingw\`, в которой будет находиться папка `bin`
- Добавить `C:\mingw64\bin` в `PATH` (`WIN + R` -> `sysdm.cpl` -> `Enter` -> `Дополнительно` / `Advanced` -> `Переменные среды` / `Environment Variables`)
## Установка ARM GNU Toolchain
- С [сайта](https://developer.arm.com/Tools%20and%20Software/GNU%20Toolchain) (VPN required) загрузить `Arm GNU Toolchain`, в названии файла должно содержаться `arm-none-eabi`
- Следовать инструкциям инсталлятора, не меняя параметров установки
- Добавить `C:\Program Files (x86)\Arm GNU Toolchain arm-none-eabi\ВЕРСИЯ\bin\` в `PATH`, указав установленную версию
- Убедиться в правильности установки можно путем ввода команды `arm-none-eabi-gcc --version` в `cmd`
## Git
- С [сайта](https://git-scm.com/downloads/win) загрузить установщик
- Следовать инструкциям инсталлятора, не меняя параметров установки
- Переменная `PATH` должна обновиться автоматически
- Убедиться в правильности установки можно путем ввода `git –-version` в `cmd`
## OpenOCD
- С [сайта](https://github.com/xpack-dev-tools/openocd-xpack/releases) загрузить zip-архив для win32
- Извлечь его в `C:\`, таким образом должна появиться директория `C:\xpack-openocd-<...>\bin\`
- Добавить вышеуказанную директорию в `PATH`
## Проверка правильности установки
Для проверки выполнить в командной строке:
- `g++ --version`
- `mingw32-make --version`
- `arm-none-eabi-g++ --version`
- `git --version`
- `cmake --version`
- `openocd --version`
## YAHAL
- Клонировать репозиторий `git clone https://git.fh-aachen.de/Terstegge/YAHAL.git`
- Перейти в директорию с примером `cd YAHAL/examples/rp2040-launchpad/blink_simple`
- Создать папку `build` и перейти в неё `mkdir build && cd build`
- Выполнить `cmake -G "MinGW Makefiles" ..`
- Скомпилировать пример, выполнив `mingw32-make`
- При правильно выполненной установке пример будет успешно скомпилирован, процесс завершится
- При возникновении ошибки `unrecognized option --no-warn-rwx-segment` в файле `YAHAL/cmake/toolchains/arm-gcc.cmake` заменить `--no-warn-rwx-segment` на `--no-warn-rwx-segments`, очистить папку `build` и повторить попытку
- При повторном возникновении ошибки, удалить в том же файле флаг `-Wl,--no-warn-rwx-segments` или `-Wl,--no-warn-rwx-segment` из `ARM_GCC_LINK_FLAGS`
## Zadig (USB драйвер)
- Загрузить Zadig с [сайта](https://zadig.akeo.ie)
- Подключить rp2040 (USB)
- Запустить загруженный `.exe`-файл и нажать `Install Driver`

# Сборка прошивки (Linux)
- Убедиться, что установлены `gcc`, `g++`, `make` и `cmake`
- Установить GNU ARM Cross-compiler
