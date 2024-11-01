# Разработка автоматизированной системы учета и ведения семейного бюджета

## Функциональные требования
В курсовой работе по разработке автоматизированной системы учета и ведения семейного бюджета можно выделить следующие основные требования и функциональные возможности:

### 1. **Пользовательское меню**:
   - **Роли и авторизация**:
     - Пользовательская система с разделением ролей:
        - Администратор:
            - Управление пользователями (создание, удаление, редактирование профилей).
            - Возможность просмотра отчетов всех пользователей системы.
        - Обычный пользователь:
            - Ведение личного бюджета (добавление расходов, доходов, планирование бюджета).
            - Просмотр личных отчетов и статистики.
            - Доступ только к своим данным и записям.
        - Члены семьи (опционально):
            -Возможность создания аккаунтов для каждого члена семьи с доступом к общим бюджетным данным, чтобы отслеживать коллективные расходы и доходы.
     - Авторизация пользователей с хранением паролей в зашифрованном виде.
   - **Управление записями**:
     - Возможность просматривать, добавлять, редактировать и удалять записи (например, добавление доходов, расходов и других финансовых данных).
   - **Поиск, сортировка и фильтрация**:
     - Функционал для поиска, сортировки и фильтрации записей, что позволит пользователям легко находить нужную информацию по категориям (например, расходы по дате, типу или сумме).
   - **Отчеты**:
     - Генерация отчетов на основе введенных данных (например, отчеты о месячных расходах или доходах, баланс бюджета).

### 2. **Хранение данных**:
   - Хранение данных в MySQL:
     Структура данных:
        - Таблицы для хранения пользователей, категорий доходов и расходов, транзакций, бюджетных целей и отчетов.
        Связи между таблицами:
            - Связи между пользователями и их транзакциями, между категориями расходов и соответствующими записями.
        - Бэкап данных:
            - Регулярное создание резервных копий базы данных для предотвращения потерь информации.
        - Безопасность данных:
            - Защищенное хранение паролей с использованием современных алгоритмов шифрования (например, bcrypt).
            - Использование ролевой модели управления доступом к данным (администраторы видят больше информации, чем обычные пользователи).
   - **STL контейнеры**:
     - Использование контейнеров STL для временного хранения данных в оперативной памяти.

### 3. **Программные конструкции**:
   - Реализация принципов объектно-ориентированного программирования:
     - Инкапсуляция, наследование, полиморфизм.
   - Использование абстрактных классов для более гибкой архитектуры системы.
   - Реализация методов для обработки ошибок.

### 4. **Функциональные требования для семейного бюджета**:
   - **Добавление и управление категориями расходов и доходов**:
     - Возможность создания пользовательских категорий (например, еда, транспорт, коммунальные услуги) и классификация транзакций по этим категориям.
   - **Поддержка различных валют**:
     - Поддержка работы с разными валютами для возможности учёта бюджета в различных странах или для международных пользователей.
   - **Планирование бюджета**:
     - Возможность устанавливать бюджет на определённый период (месяц, год) и отслеживать его выполнение.
   - **Оповещения и напоминания**:
     - Система уведомлений, которая предупреждает о превышении бюджета по категориям или напоминания о предстоящих платежах.
   - **Графики и диаграммы**:
     - Визуализация финансовых данных с помощью графиков (например, диаграммы расходов по категориям, распределение расходов за месяц).

### 5. **Отчеты и статистика**:
- История изменений:
    - Логирование всех изменений данных, связанных с расходами и доходами, для возможности восстановления или анализа прошлых транзакций.
- Аналитика на основе данных:
    - Встроенная аналитика для отображения тенденций расходов и рекомендаций по улучшению финансового положения.
- Поддержка различных языков:
    - Возможность добавления мультиязычной поддержки интерфейса (например, для русскоязычных и англоязычных пользователей).
- Улучшенная работа с отчетами:
    - Хранение отчетов в базе данных:
    - Автоматическая генерация отчетов и сохранение их в базе данных для последующего использования.
- Фильтры отчетов:
    - Возможность фильтрации по дате, категории расходов, пользователям или другим параметрам.
