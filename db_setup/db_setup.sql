-- psql -U postgres -tc "SELECT 1 FROM pg_database WHERE datname = 'cppbot'" | grep -q 1 || psql -U postgres -c "CREATE DATABASE cppbot"
-- psql -U postgres -d cppbot -a -f db_setup.sql    
DROP TABLE IF EXISTS bot_user cascade;
DROP TABLE IF EXISTS user_lesson;


CREATE TABLE bot_user(
    chat_id bigint PRIMARY KEY,
    teacher bigint,
    tgusername varchar(128),
    first_name varchar(255),
    last_name varchar(255),
    phone varchar(128) UNIQUE,
    email varchar(255) UNIQUE,
    class varchar(32),
    comment text,
    user_role varchar(32),
    is_active boolean DEFAULT FALSE,
    FOREIGN KEY (teacher) REFERENCES bot_user (chat_id) ON DELETE CASCADE 
);


CREATE TABLE user_lesson(
    id SERIAL PRIMARY KEY,
    date date,
    teacher bigint,
    pupil bigint,
    time varchar(32) NOT NULL,
    objectives varchar(255) NOT NULL,
    comment_for_pupil text,
    comment_for_teacher text,
    is_paid boolean DEFAULT FALSE,
    FOREIGN KEY (pupil) REFERENCES bot_user (chat_id) ON DELETE CASCADE,
    FOREIGN KEY (teacher) REFERENCES bot_user (chat_id) ON DELETE CASCADE
);
