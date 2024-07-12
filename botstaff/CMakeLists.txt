add_library(func
src/handlers/Handlers.cpp
src/handlers/user_handlers/UserHandlers.cpp
src/handlers/teacher_handlers/TeacherHandlers.cpp
src/handlers/teacher_handlers/CreateLessonHandlers.cpp
src/handlers/user_handlers/UserRegistration.cpp
src/Commands.cpp
src/database/PSQL.cpp
src/keyboards/Keyboards.cpp
src/keyboards/teacher_keyboards/TeacherKeyboards.cpp
src/keyboards/user_keyboards/UserKeyboards.cpp
src/Utils.cpp
src/database/CRUD.cpp
)


target_include_directories(func PUBLIC include) 
