# rp2040CardSoft
rp2040 + ST7789 240x320 display module

# Сборка прошивки (Win10)
- Для получения бинарного файла универсальной прошивки одного устройства необходимо подготовить среду сборки и произвести компиляцию исходного кода, находящегося в этом репозитории. Подготовку среды достаточно выполнить один раз на одном персональном компьютере, процесс описан в [этом](/#подготовка-среды) разделе
- Общий процесс компиляции исходного кода проекта описан в [этом](#компиляция-прошивки) разделе. Переходить к этим действиям следует только после выполнения подготовки среды
- Если в исходный код были внесены изменения, при этом среда для компиляции на используемом ПК была подготовлена ранее, а компиляция проекта уже производилась, то полный порядок действий для выполнения повторной компиляции указан в [этом](#обновление) разделе
## Подготовка среды
### Установка MinGW
- Загрузить zip-архив с [сайта](https://winlibs.com). Для загрузки выбрать последнюю версию с UCRT runtime и без поддержки LLVM
- Загруженный архив распаковать в `C:\`, таким образом должна появиться директория `C:\mingw\`, в которой будет находиться папка `bin`
- Добавить `C:\mingw64\bin` в `PATH` (`WIN + R` -> `sysdm.cpl` -> `Enter` -> `Дополнительно` / `Advanced` -> `Переменные среды` / `Environment Variables`)
### Установка ARM GNU Toolchain
- С [сайта](https://developer.arm.com/Tools%20and%20Software/GNU%20Toolchain) (VPN required) загрузить `Arm GNU Toolchain`, в названии файла должно содержаться `arm-none-eabi`
- Следовать инструкциям инсталлятора, не меняя параметров установки
- Добавить `C:\Program Files (x86)\Arm GNU Toolchain arm-none-eabi\ВЕРСИЯ\bin\` в `PATH`, указав установленную версию
- Убедиться в правильности установки можно путем ввода команды `arm-none-eabi-gcc --version` в `cmd`
### Git
- С [сайта](https://git-scm.com/downloads/win) загрузить установщик
- Следовать инструкциям инсталлятора, не меняя параметров установки
- Переменная `PATH` должна обновиться автоматически
- Убедиться в правильности установки можно путем ввода `git –-version` в `cmd`
### OpenOCD
- С [сайта](https://github.com/xpack-dev-tools/openocd-xpack/releases) загрузить zip-архив для win32
- Извлечь его в `C:\`, таким образом должна появиться директория `C:\xpack-openocd-<...>\bin\`
- Добавить вышеуказанную директорию в `PATH`
### Проверка правильности установки
Для проверки выполнить в командной строке:
- `g++ --version`
- `mingw32-make --version`
- `arm-none-eabi-g++ --version`
- `git --version`
- `cmake --version`
- `openocd --version`
### YAHAL
- Клонировать репозиторий `git clone https://git.fh-aachen.de/Terstegge/YAHAL.git`
- Создать переменную среды `YAHAL_DIR`, указывающую на папку репозитория
- Перейти в директорию с примером `cd YAHAL/examples/rp2040-launchpad/blink_simple`
- Создать папку `build` и перейти в неё `mkdir build && cd build`
- Выполнить `cmake -G "MinGW Makefiles" ..`
- Скомпилировать пример, выполнив `mingw32-make`
- При правильно выполненной установке пример будет успешно скомпилирован, процесс завершится выводом компоновщика информации об использованных регионах памяти, а также строчкой `[100%] Built target blink_simple`, в папке `build` появится файл `blink_simple.bin`
- При возникновении ошибки `unrecognized option --no-warn-rwx-segment` в файле `YAHAL/cmake/toolchains/arm-gcc.cmake` заменить `--no-warn-rwx-segment` на `--no-warn-rwx-segments`, очистить папку `build` и повторить попытку
- При повторном возникновении ошибки, удалить в том же файле флаг `-Wl,--no-warn-rwx-segments` или `-Wl,--no-warn-rwx-segment` из `ARM_GCC_LINK_FLAGS`
### Zadig (USB драйвер)
- Загрузить Zadig с [сайта](https://zadig.akeo.ie)
- Подключить rp2040 (USB)
- Запустить загруженный `.exe`-файл и нажать `Install Driver`
- Дождаться сообщения об успешной установке
### Загрузка по USB
- Подключить к ПК, удерживая в момент подключения нажатой кнопку `BOOT`
- Открыть проводник, найти `.uf`-файл прошивки
- Убедиться, что среди устройств и дисков появился USB-накопитель `RPI-RP2`
- Скопировать `.uf`-файл на USB-накопитель `RPI-RP2`
- После завершения процесса rp2040 автоматически отключится и перезагрузится
## Компиляция прошивки
- Клонировать репозиторий с прошивкой
- Перейти в папку репозитория
- Создать папку `build` и перейти в нее
- Выполнить `cmake -G "MinGW Makefiles" ..` и дождаться завершения работы cmake
- Выполнить `mingw32-make`
- Убедиться в отсутствии ошибок
- В папке `build` появятся файлы `.bin`, `.hex`, `.elf`, `.uf2`
## Обновление
- Если необходимо обновить исходный код в локальном репозитории до последней версии с GitHub, выполнить `git pull`
- Создать папку `build` или очистить её содержимое в случае, если она была создана ранее и содержит в себе файлы
- Выполнить `cmake -G "MinGW Makefiles" ..` и дождаться завершения работы cmake
- Выполнить `mingw32-make`
- Убедиться в отсутствии ошибок
- В папке `build` появятся файлы `.bin`, `.hex`, `.elf`, `.uf2`

# Сборка прошивки (Linux)
- Убедиться, что установлены `gcc`, `g++`, `make` и `cmake`
- Установить GNU ARM Cross-compiler

# Описание проекта
### Общее описание
Проект представляет из себя исходный код игры (Flappy Bird), предназначенный для запуска на плате [ieye](https://github.com/Neyasyti-Aero/CardNFTHardware). Код написан на C++ (стандарт C++20) с использованием библиотеки [YAHAL](https://git.fh-aachen.de/Terstegge/YAHAL)

В основе аппаратного решения:
- микроконтроллер `rp2040` с двумя ядрами Arm Cortex M0+ с тактовой частотой до 133 МГц, 264 КБ SRAM-памяти, поддержкой до 16 МБ внешней флеш-памяти
- модуль экрана `GY-TFT028F276` 2.8'' 240(RGB)x320 SPI [ST7789V3](https://files.waveshare.com/upload/c/c1/ST7789V3_V0.1.pdf)
### Детальное описание
#### Файлы проекта
- `CMakeLists.txt` - скрипт сборки проекта
- `CharacterDrawer.cpp`, `CharacterDrawer.h` - класс отрисовки символов (текста), шрифт
- `Difficulty.cpp`, `Difficulty.h` - класс уровней сложности
- `GetColors.cpp`, `GetColors.h` - класс, содержащий фон в виде массива байтов, а также методы, связанные с его отрисовкой
- `ScoreEntry.cpp`, `ScoreEntry.h` - лидерборд
- `flappy_back.cpp` - содержит функцию main
- `YAHAL_import.cmake` - скрипт, задача которого - найти путь к установленному YAHAL
- `Game.cpp`, `Game.h` - логика игры, движения, коллизии, визуализация и прочее
#### Project specific
Вся логика игры описана в файлах `Game.cpp` и `Game.h`. Класс `Game` содержит 2 публичных метода:
- `Game()` - конструктор
- `run()` - главный метод программы, содержащий бесконечный цикл
Класс `Game` имеет следующие приватные свойства:
- `_lcd_cs` - объект `gpio_rp2040_pin`, пин CS экрана
- `_spi` - объект `spi_rp2040`, аппаратный SPI rp2040, используемый для подключения экрана
- `_lcd_rst` - объект `gpio_rp2040_pin`, пин RESET экрана
- `_lcd_dc` - объект `gpio_rp2040_pin`, пин выбора Data/Command экрана
- `_lcd` - объект `st7735s_drv`, дескриптор экрана
- `_s1` - объект `gpio_rp2040_pin`, пин первой кнопки
- `_s2` - объект `gpio_rp2040_pin`, пин второй кнопки
- `_timer` - объект `timer_rp2040`, таймер игры
- `_accel_x` - объект `adc_rp2040_channel`, используется для ускорения птицы
- `_getColors` - объект `GetColors`, для отрисовки фона
- `_name` - массив байтов, имя игрока, максимум 3 символа
- `_diff` - объект `Difficulty`, уровень сложности
- `_sb` - объект `Scoreboard`, таблица лидеров
- `_mode` - `uint32_t`, режим?
- `_cd` - объект `CharacterDrawer`, для отрисовки текста
Класс `Game` имеет следующие приватные методы:

