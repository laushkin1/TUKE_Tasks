#include "parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct parser *create_parser() {
    struct parser *parser = (struct parser *) malloc(sizeof(struct parser));
    if (parser == NULL) return NULL;

    parser->history = NULL;

    struct command *konec = create_command("KONIEC", "Command ends the game.", "(koniec|exit|quit)", 1);
    struct command *sever = create_command("SEVER", "Moves the player to the room to the north of the current one.", "(sever|s)", 1);
    struct command *juh = create_command("JUH", "Moves the player to the room to the south of the current one.", "(juh|j)", 1);
    struct command *vychod = create_command("VYCHOD", "Moves the player to the room to the east of the current one.", "(vychod|v)", 1);
    struct command *zapad = create_command("ZAPAD", "Moves the player to the room to the west of the current one.", "(zapad|z)", 1);
    struct command *rozhliadni_sa = create_command("ROZHLIADNI SA", "Displays current information about the room where the player is.", "(rozhliadni sa)", 1);
    struct command *prikazy = create_command("PRIKAZY", "Displays all available commands.", "(prikazy|help|pomoc)", 1);
    struct command *verzia = create_command("VERZIA", "Displays the game version number, any accompanying text, and the author's name and contact.", "(verzia)", 1);
    struct command *restart = create_command("RESTART", "Restarts the game from the beginning.", "(restart)", 1);
    struct command *o_hre = create_command("O HRE", "Displays a short text that serves as an introduction to the story.", "(o hre|about)", 1);
    struct command *vezmi = create_command("VEZMI", "Puts an item from the room into the player's backpack.", "(vezmi)", 1);
    struct command *poloz = create_command("POLOZ", "Places an item from the player's backpack into the room.", "(poloz)", 1);
    struct command *inventar = create_command("INVENTAR", "Displays the contents of the player's backpack.", "(inventar|i)", 1);
    struct command *pouzi = create_command("POUZI", "Uses an item from the player's backpack or the room.", "(pouzi)", 1);
    struct command *preskumaj = create_command("PRESKUMAJ", "Describes an item in the room or backpack.", "(preskumaj)", 1);
    struct command *nahraj = create_command("NAHRAJ", "Loads a saved game position from disk.", "(nahraj|load)", 1);
    struct command *uloz = create_command("ULOZ", "Saves the state of the game being played on disk.", "(uloz|save)", 1);

    struct container *konec_container = create_container(NULL, COMMAND, konec);
    struct container *sever_container = create_container(NULL, COMMAND, sever);
    struct container *juh_container = create_container(NULL, COMMAND, juh);
    struct container *vychod_container = create_container(NULL, COMMAND, vychod);
    struct container *zapad_container = create_container(NULL, COMMAND, zapad);
    struct container *rozhliadni_sa_container = create_container(NULL, COMMAND, rozhliadni_sa);
    struct container *prikazy_container = create_container(NULL, COMMAND, prikazy);
    struct container *verzia_container = create_container(NULL, COMMAND, verzia);
    struct container *restart_container = create_container(NULL, COMMAND, restart);
    struct container *o_hre_container = create_container(NULL, COMMAND, o_hre);
    struct container *vezmi_container = create_container(NULL, COMMAND, vezmi);
    struct container *poloz_container = create_container(NULL, COMMAND, poloz);
    struct container *inventar_container = create_container(NULL, COMMAND, inventar);
    struct container *pouzi_container = create_container(NULL, COMMAND, pouzi);
    struct container *preskumaj_container = create_container(NULL, COMMAND, preskumaj);
    struct container *nahraj_container = create_container(NULL, COMMAND, nahraj);
    struct container *uloz_container = create_container(NULL, COMMAND, uloz);

    konec_container->next = sever_container;
    sever_container->next = juh_container;
    juh_container->next = vychod_container;
    vychod_container->next = zapad_container;
    zapad_container->next = rozhliadni_sa_container;
    rozhliadni_sa_container->next = prikazy_container;
    prikazy_container->next = verzia_container;
    verzia_container->next = restart_container;
    restart_container->next = o_hre_container;
    o_hre_container->next = vezmi_container;
    vezmi_container->next = poloz_container;
    poloz_container->next = inventar_container;
    inventar_container->next = pouzi_container;
    pouzi_container->next = preskumaj_container;
    preskumaj_container->next = nahraj_container;
    nahraj_container->next = uloz_container;

    parser->commands = konec_container;

    return parser;
}

struct parser *destroy_parser(struct parser *parser) {
    if (parser == NULL) return NULL;

    struct container *current_command = parser->commands;
    while (current_command != NULL) {
        struct container *temp_command = current_command;
        destroy_containers(temp_command);
        current_command = current_command->next;
    }

    struct container *current_history = parser->history;
    while (current_history != NULL) {
        struct container *temp_history = current_history;
        destroy_containers(temp_history);
        current_history = current_history->next;
    }

    free(parser);
    return NULL;
}

struct command *parse_input(struct parser *parser, char *input) {
    if (parser == NULL || input == NULL) {
        printf("Error: Invalid parser or input.\n");
        return NULL;
    }

    while (isspace(*input)) input++;
    size_t len = strlen(input);
    while (len > 0 && isspace(input[len - 1])) input[--len] = '\0';

    return get_from_container_by_name(parser->commands, input);
}