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

    Проект: Game of Life (Игра Жизнь)
    Технологии: C, ncurses (ANSI-терминал), системное программирование, Makefile
    Формат: Командная разработка (3 разработчика)

    Разработана симуляция клеточной жизни по правилам Джона Конвея в виде динамического терминального приложения.
    Основные особенности:

    Визуализация в терминале с использованием цветных символов Unicode и ANSI-escape последовательностей;

    Циклический мир (тор): края поля замыкаются, имитируя бесконечную поверхность;

    Гибкое управление пользователем: изменение скорости (+/-), выход из симуляции по нажатию клавиши q;

    Автоматическая остановка игры при полном исчезновении клеток;

    Поддержка чтения стартовой конфигурации из файла, что позволяет моделировать различные шаблоны;

    Чёткое разделение логики: генерация, отрисовка, управление, ввод с клавиатуры и подсчёт соседей;

    Использование системных вызовов (ioctl, usleep, stty) для управления вводом и циклом отрисовки.

    Проект позволил глубже освоить системное программирование на C, управление терминалом без GUI, и эффективно работать в команде с контролем версий и Makefile-сборкой.

## Pong: 

    Pong (Понг в терминале)
    Технологии: C, ANSI-терминал, системное программирование, Makefile
    Формат: Индивидуальный или командный проект (1–2 разработчика)

    Реализация классической аркадной игры Pong в терминале на языке C.
    Ключевые особенности:

    Графика на основе символов с использованием Unicode и ANSI-цветов для ракеток, мяча и границ поля;

    Динамическое управление клавишами: один игрок управляет клавишами w/s, второй — o/l (или альтернативная раскладка);

    Реалистичная физика отражения мяча, учёт угла удара и границ экрана;

    Система очков и перезапуска, отображение счёта в реальном времени;

    Чистая архитектура: функции для инициализации, отрисовки, обработки столкновений и пользовательского ввода;

    Использование системных вызовов и низкоуровневых механизмов ввода (ioctl, usleep, stty) для обеспечения плавного игрового цикла без задержек;

    Собственная реализация отрисовки экрана и управления фреймрейтом.

    Проект позволил отточить навыки системного программирования, работы с вводом/выводом в терминале и реализации простой физики без сторонних библиотек.

## RPNCaculator: 

    RPN Calculator (Калькулятор ОПЗ)
    Технологии: C, стек, Makefile, модульное тестирование
    Формат: Индивидуальный проект

    Реализация калькулятора на языке C, поддерживающего вычисления в формате обратной польской записи (Reverse Polish Notation).
    Ключевые особенности:

    Поддержка арифметических операций: +, -, *, /, %, унарный минус;

    Обработка вещественных и целых чисел;

    Использование стека как основной структуры данных для хранения промежуточных результатов;

    Парсинг строки выражения с валидацией и сообщениями об ошибках;

    Модульная структура кода: раздельная реализация для стека, парсера, арифметики и интерфейса;

    Покрытие кода тестами, в том числе на пограничные случаи: деление на ноль, некорректный ввод, пустой стек.

    Проект дал практический опыт реализации стековой машины и углубил понимание принципов постфиксной записи, обработки ошибок и управления памятью в C.

## School21: 

    Навыки и опыт разработки на языке C

    В рамках серии проектов и учебных заданий я освоил глубокое понимание языка C и практические навыки разработки системных модулей с использованием структурных типов данных и динамического управления памятью. В частности:

    Разработка и реализация пользовательских структур (struct) и объединений (union) для удобного и эффективного хранения разнотипных данных.

    Создание и работа с динамическими структурами данных: односвязными списками и стеком, включая функции инициализации, добавления, поиска, удаления элементов, а также освобождения памяти.

    Разработка алгоритмов сортировки и поиска, оптимизация операций с массивами и списками.

    Написание модульных тестов для автоматизированной проверки корректности функций, использование кодов возврата для оценки успешности операций.

    Управление процессом сборки проектов с помощью Makefile, обеспечение повторяемой и удобной сборки с запуском тестов.

    Использование инструментов для контроля качества кода и выявления ошибок: gcc (компиляция и диагностика), valgrind (анализ утечек памяти), cppcheck (статический анализ качества кода).

    Строгое следование принципам структурного программирования, грамотное управление ресурсами и памятью для предотвращения ошибок и сбоев в работе программ.

    Этот опыт позволил мне освоить ключевые аспекты программирования на С, применяемые в системном и прикладном программировании.   

## JavaRush: 

    В рамках обучения на платформе JavaRush выполнено более 50 практических проектов и задач, охватывающих широкий спектр основ и продвинутых тем Java:

    Основы языка: работа с типами данных, ввод/вывод с клавиатуры, управление потоками исполнения (циклы, условные операторы).

    Среда разработки: опыт работы с IntelliJ IDEA, отладка кода (debug).

    Коллекции и дженерики: создание и использование коллекций, обобщённые типы.

    Объектно-ориентированное программирование (ООП): принципы ООП (наследование, инкапсуляция, полиморфизм, абстракция), интерфейсы, перегрузка методов и конструкторов, внутренние классы.

    Работа со строками: особенности mutable и immutable строк, использование StringBuilder, StringBuffer, форматирование и парсинг.

    Исключения и обработка ошибок: реализация try-catch блоков, создание собственных исключений.

    Потоки ввода-вывода: использование InputStream, OutputStream, Reader, Writer, работа с файлами.

    Параллельное программирование: создание и управление потоками (Thread, Runnable), синхронизация, volatile, deadlock, wait/notify.

    Продвинутые темы: сериализация объектов, использование ThreadPool, ExecutorService, Callable.

    Практические задачи: разработка мини-игр, работа с датой и временем, задачи с лямбда-функциями и функциональным программированием.

    Инструменты и библиотеки: опыт работы с Jsoup для парсинга HTML.

    Данные проекты обеспечили глубокое понимание архитектуры Java-приложений и практические навыки написания чистого, эффективного и безопасного кода.


### Подробности реализации и технические особенности содержатся непосредственно в каждом проекте.

## English Version

## Project Portfolio

    This repository is a collection of practical projects developed during my intensive programming training. Each project is organized in a separate branch and includes a detailed technical overview that covers architecture, technologies used, and key design decisions.

    The repository reflects my learning path — from writing my first lines of C code to confidently developing CLI tools, collaborating in teams, and building well-structured, maintainable applications. Projects demonstrate experience with system I/O, parsing, regular expressions, serialization, architectural patterns, teamwork, and code optimization.

### Repository Structure
    
## TodoList:

    A terminal-based task manager with support for priorities, statuses, and categories.
    Implemented in two versions:
        • Java version — OOP-based design using patterns (Singleton, Composite), serialization, and 12  + structured classes.
        • C version — manual memory management, modular task structure, I/O handling, command parsing.

    Designed and implemented full architecture from scratch.

    Java version uses Maven, supports file persistence and flexible CLI interface.

    C version includes task storage, user input parsing, and clean modular layout.

    Led a team of 3, managing development flow and key technical decisions.

    Refactored to reduce complexity, improve code clarity, and streamline UI logic.

## GNU_Utils: 

    Implementation of grep and cat utilities with automated testing
    Tech stack: C11, Bash, POSIX, Makefile, diff, grep, cat

    Implemented full-featured versions of the grep and cat utilities in C, closely replicating the behavior of the standard POSIX tools. Paid special attention to accurate flag parsing and edge-case handling.

    Built a suite of automated Bash test scripts covering:

    verification of all major flags (-e, -i, -v, -o, -c, -l, -n, -h, -s, -f);

    testing combinations and repetitions of flags;

    multi-file processing and fallback behavior with nonexistent files;

    output comparison with standard grep and cat via diff;

    logging failed cases to log.txt and summarizing test results.

    The project was developed in a Unix-like environment following structured programming principles and thorough test automation.

## GameOfLife: 

    Game of Life
    Tech stack: C, ANSI terminal graphics, low-level system programming, Makefile
    Format: Team collaboration (3 developers)

    Implemented a Conway's Game of Life simulation as a real-time terminal-based application.
    Key features:

    Terminal visualization using Unicode and ANSI color escape codes for live and dead cells;

    Toroidal grid: the field wraps around to simulate an infinite plane;

    Keyboard interaction for speed adjustment (+/-) and graceful exit (q);

    Automatic termination when no live cells remain;

    Support for initial configuration loaded from a file (zeroes and ones input);

    Modular architecture with clean separation between core logic, rendering, and input handling;

    System calls like ioctl, usleep, and stty used for non-blocking input and terminal control.

    This project strengthened my skills in C system programming, low-level I/O, memory-safe logic, and teamwork in a Unix-based development environment.

## Pong: 

    Pong (Terminal Arcade Game)
    Tech stack: C, ANSI terminal graphics, low-level I/O, Makefile
    Format: Individual or team project (1–2 developers)

    A terminal-based remake of the classic arcade game Pong, built entirely in C.
    Key features:

    ASCII/Unicode rendering using ANSI colors for paddles, ball, and borders;

    Real-time keyboard control: w/s for one player, o/l for the second;

    Simple physics engine simulating bounce angles and wall collisions;

    Score tracking and auto-reset after each goal, with live display;

    Modular structure for initialization, rendering, collision detection, and input;

    Smooth animation loop via low-level system calls (ioctl, usleep, stty) to handle frame timing and non-blocking input.

    This project enhanced my understanding of event-driven loops, terminal graphics, and real-time input handling in C under Unix-based systems.

## RPNCaculator: 

    RPN Calculator (Reverse Polish Notation)
    Tech stack: C, stack-based evaluation, Makefile, modular design
    Format: Individual project

    A command-line calculator that parses and evaluates mathematical expressions in Reverse Polish Notation (RPN).
    Key features:

    Support for core arithmetic operations: +, -, *, /, %, unary minus;

    Handles both integers and floating-point numbers;

    Implements a custom stack structure to store intermediate results;

    Includes robust expression parser with error checking and informative feedback;

    Fully modular codebase: separate modules for parsing, arithmetic logic, stack operations, and main control flow;

    Comprehensive test coverage, including edge cases such as division by zero, malformed input, or underflow.

    This project strengthened my skills in parsing, memory management, and stack-based algorithm design in C.

## School21:

    Skills and Experience in C Programming

    Through a series of projects and learning tasks, I gained deep understanding and practical skills in C programming, focusing on system module development using structured data types and dynamic memory management. Specifically:

    Designing and implementing custom structures (struct) and unions (union) for efficient and flexible storage of heterogeneous data.

    Creating and managing dynamic data structures such as singly linked lists and stacks, including functions for initialization, insertion, search, deletion, and memory deallocation.

    Developing sorting and searching algorithms, optimizing operations on arrays and linked lists.

    Writing unit tests to automate verification of function correctness, using return codes for operation success evaluation.

    Managing project builds using Makefile, ensuring reproducible and convenient compilation with automated test runs.

    Utilizing tools for code quality and error detection: gcc (compilation and diagnostics), valgrind (memory leak analysis), cppcheck (static code analysis).

    Strict adherence to structured programming principles, careful resource and memory management to prevent errors and crashes.

    This experience helped me master core aspects of C programming, applicable in both system-level and application development.

## JavaRush: 

    Completed over 50 practical projects and exercises on the JavaRush platform, covering a wide range of fundamental and advanced Java topics:

    Java Basics: working with data types, keyboard input/output, control flow (loops, conditional statements).

    Development Environment: experience with IntelliJ IDEA and debugging techniques.

    Collections and Generics: creating and using collections, generic types.

    Object-Oriented Programming (OOP): core OOP principles (inheritance, encapsulation, polymorphism, abstraction), interfaces, method and constructor overloading, inner classes.

    String Handling: mutable vs immutable strings, usage of StringBuilder, StringBuffer, formatting, and parsing.

    Exception Handling: implementing try-catch blocks, creating custom exceptions.

    Input/Output Streams: working with InputStream, OutputStream, Reader, Writer, file operations.

    Multithreading: creating and managing threads (Thread, Runnable), synchronization, volatile keyword, deadlocks, wait/notify mechanisms.

    Advanced Topics: object serialization, thread pools, ExecutorService, Callable interface.

    Practical Tasks: development of mini-games, working with date and time APIs, lambda expressions and functional programming tasks.

    Tools and Libraries: experience with Jsoup for HTML parsing.

    These projects provided a deep understanding of Java application architecture and practical skills in writing clean, efficient, and safe code.


###  Detailed implementation steps and technical insights are provided inside each project.