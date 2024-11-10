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
- С [сайта](https://git-scm.com/downloads/win) загрузить установщик Git
- Следовать инструкциям инсталлятора, не меняя параметров установки
- Переменная `PATH` должна обновиться автоматически
- Убедиться в правильности установки можно путем ввода `git –version` в `cmd`

# Сборка прошивки (Linux)
- Убедиться, что установлены `gcc`, `g++`, `make` и `cmake`
- Установить GNU ARM Cross-compiler
