#include "character_factory.h"

CharacterFactory::CharacterFactory()
{

}

CharacterFactory::~CharacterFactory()
{

}

Character*
CharacterFactory::make_character(int character_code, unsigned player_id, double x_pos, double y_pos)
{
    switch(character_code) {
        case INFILTRATOR:
            return new Infiltrator(player_id, x_pos, y_pos);
            break;

        case MAGE:
            return new Mage(player_id, x_pos, y_pos);
            break;

        case SOLDIER:
            return new Soldier(player_id, x_pos, y_pos);
            break;

        case KNIGHT:
            return new Knight(player_id, x_pos, y_pos);
            break;

        default:
            printf("Valor inválido na CharacterFactory\n");
            return nullptr;
            break;
    }
}