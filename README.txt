For a better understanding of testing process, we provide you with:
- simplified version of grader;
- solution file with examples of Delete implementation;
- executable file "run" with correct grader-solution linking;
- open testset with 2000 tests.
Please pay attention that grader given to you differs from the real one. The real grader reads 2000 tests from testset file one by one and runs Solver.
The format of testset file is following:
- In the first row number of tests (2000) is given. Each test have values N, M, L and list of infos for every vertex.
- For each index info contains: weight, lvlsCount, primaryLvl (and secondaryLvl if lvlsCount = 2), primaryEdges (and secondaryEdges if lvlsCount = 2).
- Each edges list has size of N and fulled with values from 0 to 3.
- Values 2-3 represents unstable edges (2 can be deleted, 3 cannot) while values 0-1 represent stable edges (0 no edge, 1 if edge exists).
We hope that after that clarifications you will not feel huge difficulties with input/output format.
Good luck!
Для лучшего понимания процесса тестирования мы предоставляем вам:
- упрощенная версия грейдера;
- файл решения с примерами реализации удаления;
- исполняемый файл "run" с правильной привязкой к грейдеру-решению;
- открытый набор тестов с 2000 тестами.
Пожалуйста, обратите внимание, что предоставленный вам грейдер отличается от настоящего. Настоящий грейдер считывает 2000 тестов из файла testset один за другим и запускает Solver.
Формат файла testset следующий:
- В первой строке указано количество тестов (2000). Каждый тест содержит значения N, M, L и список информации для каждой вершины.
- Для каждого индекса информация содержит: вес, lvlsCount, primaryLvl (и secondaryLvl, если lvlsCount = 2), primaryEdges (и secondaryEdges, если lvlsCount = 2).
- Каждый список ребер имеет размер N и заполнен значениями от 0 до 3.
- Значения 2-3 представляют нестабильные ребра (2 можно удалить, 3 нельзя), в то время как значения 0-1 представляют стабильные ребра (0 нет ребра, 1, если ребро существует).
Мы надеемся, что после этих разъяснений вы не почувствуете огромных трудностей с форматом ввода/вывода.
Удачи!