#include <vector>
#include <string>
#include <chrono>
#include <utility>
#include <tgbot/tgbot.h>
#include <unordered_set>
#include "botstaff/database/CRUD.hpp"
#include <vector>
#include <chrono>

using namespace TgBot;

int dayNumber(int year, int month, int day);
int num_days(int month, int year);
std::vector<int> get_curent_ymd();


bool is_admin(long);
bool is_teacher(const botUser&);
bool is_teacher(long chat_id);
std::unordered_set<int> get_lesson_days(int, int, long, const std::string&);

void create_first_row(InlineKeyboardMarkup::Ptr&);
void create_last_row(InlineKeyboardMarkup::Ptr&, int, int, const std::string& role, bool);


std::wstring utf8_to_wstring(const std::string& str);
std::string wstring_to_utf8(const std::wstring& str);
std::string string_to_upper(const std::string& s);

botUser get_user(long chat_id);
std::string get_pupil_info(const botUser& u);
std::string get_pupil_info(const Message::Ptr& message);
std::string get_teacher_info(const botUser& u);
std::string get_comment_text(int);


std::vector<std::vector<std::string>> get_lessons_by_day(long, std::string, int, int, int);
std::string get_user_lesson_info(long chat_id, int user_lesson_id, std::string role);

void activate_this_user(long chat_id);
void delete_this_user(long chat_id);
void delete_lesson(int lesson_id);

std::vector<std::string> split(const std::string&, char);
std::chrono::year_month_day split_date(const std::string&, char);
std::string lesson_delete_request_message(long, long*);

std::vector<std::string> get_last_10_comments(long);

