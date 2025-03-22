#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "world.h"

struct container *create_world(int language) {
    if(language == 1){
        return false;
    }
    struct room *field = create_room("Стежка поля", "Ви серед відкриттго поля, здалеку видніються руїни дивних структур, та бойових машин, небо готується до дождю, перед вами перехрестя, попереду амбар. Також по бокам жито яке можна взяти з собою, на узбіччі лежить кусок арматури");
    struct room *chagarnik = create_room("Чагарник", "Ви в чагарнику. Все кругом заросло, ви сумніваєтесь що тут колись були люди, проте ви розгледіли тонкий прохід через кущі");
    struct room *highway = create_room("Шосе", "Ви на трасі. Праворуч від вас видніється військовий блокпост, ви сподіваєтесь на те що він пустує");
    struct room *pre_barn = create_room("Місце перед амбаром", "Двері в амбар приперті граблями, довгий тяжкий предмет міг би тут зарадити.");
    struct room *barn = create_room("Амбар", "на підлозі лежить колишній господар цього амбару, до правої руки прибитий молоток, у лівій лежить ультрафіолетовий ліхтарик, Також ви помічаєте інший вихід з амбару.");
    struct room *mbp = create_room("Військовий блок пост", "На блокпості багато засохших криваих слідів, та деінде частини людського тіла, проте трупів нема. Біля військової палатки лежить ключ-карта");
    struct room *railroad = create_room("Закинута залізнична дорога", "Ви бачите відкритий вхід до амбару, та густий ліс у східному напрямку");
    struct room *camp_free = create_room("Лагер \"Вільні\"", "Ви бачите закинутий локоматив на якому кров'ю написано \"ПРОЦЕСС ВЖЕ НЕ МОЖНА ЗУПИНИТИ, НАЙКРАЩИЙ ВИХІД-ВТЕЧА, СПАЛІТЬ ДОКУМЕНТИ, НЕ ПОВРТОРЮЙТЕ НАШИХ ПОМИЛОК\" під локомативом лежав пристрій для взлому електроніки");
    struct room *former_settlement = create_room("Колишнє поселення тих, хто вижив", "Кругом ви бачите будинки з вибитими вікнами, та дверями, ви чудово розумієте що тут сталось, також ви помічаєте записку де написано \"ЛЮБОЮ ЦІНОЮ ЗАКІНЧІТЬ ЦЕ МИ НЕ В ЗМОЗІ ПРОЛИВАТИ БІЛЬШЕ КРОВІ, ВИПУСТІТЬ ВІРУС\", ви продовжуєте свій шлях.");
    struct room *pre_bunker = create_room("Вхід до бункера", "На дверях багато подряпин які тягнуться від самого верху дверей до землі. Зліва ви бачите Пункт управління");

    field->east = chagarnik;
    chagarnik->west = field;
    field->west = highway;
    highway->east = field;
    field->north = pre_barn;
    pre_barn->south = field;
//    pre_barn->north = barn;
    barn->south = pre_barn;
    highway->north = mbp;
    mbp->south = highway;
    pre_barn->east = railroad;
    railroad->west = pre_barn;
    chagarnik->north = railroad;
    railroad->south = chagarnik;
    railroad->north = camp_free;
    camp_free->south = railroad;
    former_settlement->south = mbp;
    mbp->north = former_settlement;
    pre_bunker->west = former_settlement;
    former_settlement->east = pre_bunker;
    pre_bunker->east = camp_free;
    camp_free->west = pre_bunker;

    struct item *hay = create_item("Сіно", "Маленький стог сіна", MOVABLE);
    struct item *fittings = create_item("Арматура", "Кусок арматури", USABLE | MOVABLE);
    struct item *flashlight = create_item("У-Ф ліхтарик", "Ультрафіолетовий ліхтарик колишнього господара цього амбару", USABLE | MOVABLE);
    struct item *key_card = create_item("Ключ-Карта", "Це ключ карта", USABLE | MOVABLE);
    struct item *hacking_device = create_item("Пристрій для взлому електроніки", "Дуже дивний пристрій, але вам чомусь здається, що завдяки йому ви зможете взламати якусь електроніку", USABLE | MOVABLE);
    // add blueberries to railroad

    add_item_to_room(field, hay);
    add_item_to_room(field, fittings);
    add_item_to_room(barn, flashlight);
    add_item_to_room(mbp, key_card);
    add_item_to_room(camp_free, hacking_device);

    struct container *container1 = create_container(NULL, ROOM, field);
    struct container *container2 = create_container(NULL, ROOM, chagarnik);
    struct container *container3 = create_container(NULL, ROOM, highway);
    struct container *container4 = create_container(NULL, ROOM, pre_barn);
    struct container *container5 = create_container(NULL, ROOM, barn);
    struct container *container6 = create_container(NULL, ROOM, mbp);
    struct container *container7 = create_container(NULL, ROOM, railroad);
    struct container *container8 = create_container(NULL, ROOM, camp_free);
    struct container *container9 = create_container(NULL, ROOM, former_settlement);
    struct container *container10 = create_container(NULL, ROOM, camp_free);

    container1->next = container2;
    container2->next = container3;
    container3->next = container4;
    container4->next = container5;
    container5->next = container6;
    container6->next = container7;
    container7->next = container8;
    container8->next = container9;
    container9->next = container10;
//        container10->next = container11;
//        container11->next = container12;
//        container12->next = container13;
//        container13->next = container14;
//        container14->next = container15;
//        container15->next = container16;

    return container1;
}

struct container *destroy_world(struct container *world) {
    if (world == NULL) return NULL;

    struct container *current_container = world;
    while (current_container != NULL) {
        struct container *next_container = current_container->next;
        destroy_room(current_container->room);
        free(current_container);
        current_container = next_container;
    }

    return NULL;
}

struct container *add_room_to_world(struct container *world, struct room *room) {
    if(world == NULL){
        struct container *container1 = create_container(NULL, ROOM, room);
        return container1;
    }
    if (room == NULL) return NULL;

    if (get_from_container_by_name(world, room->name) != NULL) return NULL;
    struct container *new_container = create_container(NULL, ROOM, room);
    if (new_container == NULL) return NULL;
    while (world->next != NULL) world = world->next;
    world->next = new_container;

    return world;
}

struct room *get_room(struct container *world, char *name) {
    if (world == NULL || name == NULL ||
        strcmp(name, "") == 0 || strlen(name) < 3) return NULL;

    char lowercase_name[strlen(name) + 1];
    for (size_t i = 0, len = strlen(name); i < len; i++)
        lowercase_name[i] = (char) tolower(name[i]);
    lowercase_name[strlen(name)] = '\0';

    while (world != NULL) {
        char lowercase_room_name[strlen(world->room->name) + 1];
        for (size_t i = 0, len = strlen(world->room->name); i < len; i++)
            lowercase_room_name[i] = (char) tolower(world->room->name[i]);
        lowercase_room_name[strlen(world->room->name)] = '\0';

        if (strcmp(lowercase_room_name, lowercase_name) == 0) return world->room;

        world = world->next;
    }

    return NULL;

}