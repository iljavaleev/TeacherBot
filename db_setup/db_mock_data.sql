
-- INSERT INTO bot_user VALUES (893916191, null, 'admin', 'УЛЬЯНА АЛЕКСАНДРОВНА', 'ОМЕЛЬЧЕНКО', '+7(922)054-83-77', 'abra@kadab1.ru', null, 'no comments', 'teacher', TRUE);

-- INSERT INTO bot_user VALUES (89391619, null, 'ut1name', 'pahant', 'вы', '89220000231', 'aabra@kadab1.ru', null, 'no comments', 'teacher', TRUE);
INSERT INTO bot_user VALUES (141312113, null, 'ut2name', 'Искандер', 'Фармльдегидович', '892200001231', 'babra@kadab1.ru', null, 'no comments', 'teacher', TRUE);

-- INSERT INTO bot_user VALUES (123451, 893916191, 'u1name', 'pahan', 'вы', '89221121231', 'abra@kadab1.ru', '7в', 'no comments', 'pupil', TRUE);
-- INSERT INTO bot_user VALUES (123452, 893916191, 'u2name', 'гусь', 'мвум', '89221121232', 'abra@kadab2.ru', '7в', 'no comments', 'pupil', TRUE);
-- INSERT INTO bot_user VALUES (123453, 141312112, 'u3name', 'труп', 'ааыа', '89221121233', 'abra@kadab3.ru', '7в', 'no comments', 'pupil', TRUE);
-- INSERT INTO bot_user VALUES (123454, 141312112, 'u4name', 'лось', 'аау', '89221121234', 'abra@kadab4.ru', '7в', 'no comments', 'pupil', FALSE);

-- INSERT INTO bot_user VALUES (123455, 141312113, 'u25name', 'лqwысый', 'аавуа', '892211213235', 'abra1@kadab5.ru', '7в', 'no comments', 'pupil', TRUE);
-- INSERT INTO bot_user VALUES (123456, 141312113, 'u235name', 'лqewwысый', 'аавуа', '8922122121235', 'abra2@kadab5.ru', '7в', 'no comments', 'pupil', FALSE);
-- INSERT INTO bot_user VALUES (123457, 141312113, 'u245name', 'лысыsrй', 'аавуа', '892211111235', 'abra3@kadab5.ru', '7в', 'no comments', 'pupil', TRUE);


-- INSERT INTO user_lesson VALUES (DEFAULT, '2004-10-19 10:23:54', 141312113, 123455, 'русский', null, 'он дебил', false);
-- INSERT INTO user_lesson VALUES (DEFAULT, '2004-10-19 10:23:54', 141312113, 123456, 'русский1', null, 'он дебил1', true);
-- INSERT INTO user_lesson VALUES (DEFAULT, '2004-10-19 10:23:54', 141312113, 123457, 'русский2', null, 'он дебил2', true);
-- SELECT MAX(chat_id) FROM bot_user;   
-- SELECT nextval(pg_get_serial_sequence(chat_id, bot_user));
-- 893916191 УЛЬЯНА АЛЕКСАНДРОВНА ОМЕЛЬЧЕНКО +7(922)054-83-77 omelchenkoua@mail.ru teachert
-- SELECT * FROM bot_user;
-- SELECT * FROM  user_lesson;

--DELETE FROM bot_user WHERE chat_id=141312113;
-- INSERT INTO bot_user VALUES (141312113, null, 'ut2name', 'pahant', 'вы', '892200001231', 'babra@kadab1.ru', null, 'no comments', 'teacher', TRUE);
-- SELECT l.id, TO_CHAR(l.date, 'dd/mm/yyyy'), l.comment_for_teacher, u.first_name, u.last_name FROM user_lesson as l  JOIN bot_user as u ON l.pupil=u.chat_id WHERE l.teacher=141312113 ORDER BY date DESC LIMIT 10
-- SELECT * FROM bot_user WHERE user_role='teacher' AND is_active=false ORDER BY last_name;
-- SELECT chat_id, first_name, last_name FROM bot_user WHERE UPPER(LEFT(last_name, 1) COLLATE "ru_RU")='В' AND is_active=false;

-- SELECT UPPER(LEFT(last_name, 1) COLLATE "C") FROM bot_user WHERE is_active=true;

-- SELECT u.first_name, u.last_name FROM bot_user as u JOIN (SELECT teacher as id FROM user_lesson WHERE pupil=141312113) as a ON u.chat_id = a.id;


-- Admin data

-- INSERT INTO bot_user VALUES (12, null, 'uname@1', 'ВЕНЕРА', 'ЮНИРОВНА', '8922000001', 'mail@mail.ru', null, 'no comments', 'teacher', TRUE);
-- INSERT INTO bot_user VALUES (13, null, 'uname@2', 'СВЕТЛАНА', 'ИВАНОВНА', '8922000002', 'mail@mail1.ru', null, 'no comments', 'teacher', FALSE);
-- INSERT INTO bot_user VALUES (11, null, 'uname@3', 'ТАТЬЯНА', 'ПАВЛОВНА', '8922000003', 'mail@mail2.ru', null, 'no comments', 'teacher', FALSE);

INSERT INTO bot_user VALUES (121, 141312113, 'uname@1', 'Абдул', 'Рахим', '8922----', 'yandex@mail.ru', '7f', 'no comments', 'pupil', TRUE);
INSERT INTO bot_user VALUES (131, 141312113, 'uname@2', 'Гамарджоба', 'Игнат', '8999----', 'rambler@mail1.ru', '8c', 'no comments', 'pupil', FALSE);
INSERT INTO bot_user VALUES (141, 141312113, 'uname@2', 'Афтаген', 'Батыр', '8789----', 'proton@mail1.ru', '9a', 'no comments', 'pupil', FALSE);


INSERT INTO bot_user VALUES (121332, null, 'uname@1', 'Абдул', 'Рахим', '8931----', 'yandex1@mail.ru', null, 'no comments', 'teacher', TRUE);
INSERT INTO bot_user VALUES (131442, null, 'uname@2', 'Гамарджоба', 'Игнат', '8932----', 'rambler1@mail1.ru', null, 'no comments', 'teacher', FALSE);

-- DELETE FROM bot_user WHERE chat_id=121332;
-- DELETE FROM bot_user WHERE chat_id=131442;
-- DELETE FROM bot_user WHERE chat_id=141;

INSERT INTO user_lesson VALUES (DEFAULT, '2014-11-19', 141312113, 121, '12', 'русский', 'рахмат', 'он Абдул ', false);
INSERT INTO user_lesson VALUES (DEFAULT, '2024-10-19', 141312113, 131, '13.00', 'русский1', 'шалом православные', 'он Гамарджоба', true);
INSERT INTO user_lesson VALUES (DEFAULT, '2023-10-19', 141312113, 141, '18', 'русский2', 'плохой баланс', 'он Афтаген', true);
