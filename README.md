# Russian Version

## Портфолио проектов

    Данный репозиторий представляет собой коллекцию практических проектов, выполненных в процессе интенсивного освоения программирования. Каждый проект размещён в отдельной ветке и снабжён подробным техническим описанием, раскрывающим архитектуру, используемые технологии и принятые проектные решения.

    В репозитории отражён мой путь от первых шагов в C до уверенной разработки CLI-инструментов, командной работы и создания архитектурно выверенных приложений. Проекты охватывают работу с системным вводом-выводом, парсингом, регулярными выражениями, сериализацией, архитектурными паттернами, командным взаимодействием и оптимизацией кода.

### Структура репозитория

## TodoList: 

    Консольное приложение для управления задачами с приоритетами, статусами и категориями.
    Реализовано в двух версиях:
        • Java-версия — объектно-ориентированная архитектура с паттернами (Singleton, Composite), сериализацией и структурой из 12+ классов.
        • C-версия — ручное управление памятью, структура задач с методами, обработка ввода-вывода, модульный подход.

    Архитектура спроектирована с нуля, оптимизирована под поддержку CLI.

    В Java-версии — Maven-сборка, реализация сериализации, IO, гибкая структура задач.

    В C — разработка всей структуры и логики: хранение задач, парсинг ввода, команды.

    Вёл команду из 3 человек, организовывал рабочий процесс и принимал технические решения.

    Оптимизировал проект: сократил избыточную вложенность, упростил интерфейс и повысил читаемость кода.

## GNU_Utils:

    Реализация утилит grep и cat с автотестами
    Технологии: C11, Bash, POSIX, Makefile, diff, grep, cat

    Разработал консольные утилиты grep и cat, полностью имитирующие поведение оригинальных POSIX-инструментов. Особое внимание уделялось точному соответствию спецификации и корректной работе с флагами, включая комбинированные и повторяющиеся.

    Создал набор автоматических bash-скриптов для тестирования, охватывающий:

    проверку корректности всех основных и дополнительных флагов (-e, -i, -v, -o, -c, -l, -n, -h, -s, -f);

    парные и множественные комбинации флагов;

    корректное поведение при работе с несколькими файлами и несуществующими путями;

    сравнение вывода с эталонными утилитами grep и cat через diff;

    генерацию логов (log.txt) с деталями провальных кейсов;

    вывод итоговой статистики (успешные / провальные тесты).

    Проект выполнялся в Unix-подобной среде с соблюдением принципов структурного программирования и автоматизации тестирования.

## GameOfLife: 

    Совместный проект трёх разработчиков, симулирующий клеточную жизнь согласно правилам Джона Конвея. Динамическая визуализация процесса эволюции клеток с возможностью регулировки скорости и настроек окружающей среды.

## Pong: 

    Классическая реализация игры Pong на языке Си. Поддерживаются режимы игры против компьютера или другого игрока, разнообразные схемы управления.

## RPNCaculator: 

    Расчёт сложных математических выражений методом обратной польской записи (RPN) на языке Си. Помимо вычисления выражений, калькулятор строит графическое представление функций.

## School21: 

    Практика и учебный материал из программы школы программирования "Школа №21". Темы включают синтаксис языка Си, указатели, массивы, сортировку, разработку алгоритмов, работу с Bash и Linux.

## JavaRush: 

    Основы языка Java, изученные на платформе JavaRush. Рассмотрены такие темы, как синтаксис, классы и объекты, наследование, полиморфизм, обработка исключений, потоки данных и другие важнейшие аспекты языка.


### Подробности реализации и технические особенности содержатся непосредственно в каждом проекте.

## English Version

## Project Portfolio

    This repository is a collection of practical projects developed during my intensive programming training. Each project is organized in a separate branch and includes a detailed technical overview that covers architecture, technologies used, and key design decisions.

    The repository reflects my learning path — from writing my first lines of C code to confidently developing CLI tools, collaborating in teams, and building well-structured, maintainable applications. Projects demonstrate experience with system I/O, parsing, regular expressions, serialization, architectural patterns, teamwork, and code optimization.

### Repository Structure
    
## TodoList:

    Task management application implemented in Java and C. Features include task creation, editing, removal, category assignment, priority setting.

## GNU_Utils: 

    Standalone implementation of cat and grep utilities in C language. Efficient file handling, searching, filtering.

## GameOfLife: 

    Collaborative effort between three developers, simulating Conway's Game of Life. Dynamic visualization of cell evolution with adjustable speed and environment parameters.

## Pong: 

    Classic Pong game recreated in C. Both single-player versus computer and multiplayer modes supported, multiple control methods.

## RPNCaculator: 

    Advanced calculator solving complex expressions using Reverse Polish Notation (RPN) in C. Outputs calculated results and generates function graphs.

## School21:

    Practice and training material obtained during "School #21" programming courses. Covers syntax, pointers, arrays, sorting algorithms, algorithm design, Bash and Linux environments.

## JavaRush: 

    Foundations of Java learned through the JavaRush platform. Topics include syntax, classes, objects, inheritance, polymorphism, exception handling, data streaming, etc.


###  Detailed implementation steps and technical insights are provided inside each project.