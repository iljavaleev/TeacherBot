add_library(func
src/handlers/handlers.cpp
src/handlers/user_handlers/userHandlers.cpp
src/handlers/teacher_handlers/teacherHandlers.cpp
src/handlers/teacher_handlers/createLessonHandlers.cpp
src/handlers/user_handlers/userRegistration.cpp
src/commands.cpp
src/database/psql.cpp
src/keyboards/keyboards.cpp
src/keyboards/teacher_keyboards/teacherKeyboards.cpp
src/keyboards/user_keyboards/userKeyboards.cpp
src/utils.cpp
src/database/CRUD.cpp
)


target_include_directories(func PUBLIC include) 
