#ifndef PLAYER_H
#define PLAYER_H

#include <QApplication>

class Role;

struct Player_info {
    QString name;        // < 15 символов (желательно)
    bool alive;            // false - dead, true - alive
    bool conscious;        // false - sleeps, true - can play


    QString speech;        // what player talk in day or night phase

    // ПОЛОЖИТЕЛЬНЫЕ характеристики. влияют на симпатию
    // sympathy += (stat - 5) * коэф;
    int oratory;        // красноречие 1...10, влияет на "переманивание" игроков на этапе голосования
    int friendliness;    // дружелюбность 1...10

    // ОТРИЦАТЕЛЬНЫЕ характеристики. влияют на симпатию
    // sympathy -= (stat - 5) * коэф;
    //
    int toxicity;        // токсичность 1...10
    int selfishness;    // эгоизм 1...10, также влияет на доктора - будет лечить себя
    int cunning;        // хитрость 1...10

    // ОТНОСИТЕЛЬНЫЕ характеристики. влияют на симпатию
    // если есть определенная разница, то sympathy += ....
    int sex;            // пол 0 - male, 1 - female
    int age;            // возраст 18...40, влияет на "переманивание" игроков на этапе голосования

    // НЕЙТРАЛЬНЫЕ характеристики. влияют на дневной/ночной выбор
    // чем выше, тем больше шанс вычислить нужного по роли,
    // симпатия не будет рассматриваться
    // например, мирный 10/10 может угадать мафию днем с 80-90% вероятностью
    int intuition;        // интуиция 1...10
    int attentiveness;    // внимательность 1...10
};


class Player {
public:
    Player();

    Player(Player_info info_);    // заполняется поле info
    ~Player();

    // наследник Mafia/Civilian/Detective/Doctor/Courtesan
    Role *role;

    struct Sympathy {
        Sympathy(Player *player_, int points_) {
            cur_player = player_;
            points = points_;
        }

        Player *cur_player;
        int points;
    };

    QList<Sympathy *> sympathy;

    void make_list_of_sympathy(QList<Player *> list_);

    void set_role_mafia();        // функции распределения ролей
    void set_role_civilian();    // присваивается полю role один из наследников Role
    void set_role_courtesan();    // вызываются в Game::generate_roles()
    void set_role_doctor();        //
    void set_role_detective();    //

    void set_greeting_phrase();                    // установить привественную фразу
    void set_conscious_sleep();                    // -*-*-*-*-* состояние "спит"
    void set_conscious_sleep_string();            // -*-*-*-*-* строку "спит"
    void set_conscious_awake();                    // аналогично
    void set_conscious_awake_string();            //
    void set_alive_dead();                        //
    void set_alive_dead_string();                //
    void set_alive();                            // если начинается новая игра, то всех убитых надо оживить
    void set_choice_string(Player *chosen);        // установить строку с именем выбранного игрока в ходе голосования
    void set_emotion_sad_string();

    void set_emotion_happy_string();

    void increase_sympathy_to(Player *player_);

    void decrease_sympathy_to(Player *player_);

    void increase_counter_doctor();

    void increase_counter_courtesan();

    int get_counter_doctor();

    int get_counter_courtesan();

    void set_counters_null();

    Player_info get_info();

    QString get_name();

    QString get_speech();

    bool is_alive();

    bool is_conscious();

    int get_oratory();

    int get_friendliness();

    int get_toxicity();

    int get_selfishness();

    int get_cunning();

    int get_sex();

    int get_age();

    int get_intuition();

    int get_attentiveness();

private:
    // хранит все статы игрока
    Player_info info;

    // счетчик, считает кол-во раз "когда вылечил доктор"
    // доктор не лечит более двух раз одного и того же
    int counter_doctor;

    // счетчик, считает кол-во раз "когда посетила куртизанка"
    // при посещении куртизанкой одного и того же два раза, тот умирает
    int counter_courtesan;
};

#endif // PLAYER_H
